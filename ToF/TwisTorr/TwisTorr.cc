#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "TwisTorr.h"
#include "nortlib.h"

TwisTorr::TwisTorr(const char *path, TwisTorr_t *TT_TM) :
    Ser_Sel(path, O_RDWR|O_NONBLOCK, TT_bufsize) {
  if (path == 0) {
    nl_error(3, "No path specified for TwisTorr device");
  } else {
    nl_error(MSG_DBG(1), "Opened %s for TwisTorr device", path);
  }
  TT_TM_p = TT_TM;
  pending = 0;
  cur_poll = polls.begin();
  nl_error(MSG_DBG(1), "TwisTorr ready for setup");
  setup(9600, 8, 'n', 1, 6, 1);
  nl_error(MSG_DBG(1), "TwisTorr ready for flush");
  flush_input();
  flags = Selector::Sel_Read | Selector::gflag(0) | Selector::gflag(1) |
          Selector::Sel_Timeout;
  nl_error(MSG_DBG(1), "TwisTorr done flushing, ready to tcgetattr");
  if (tcgetattr(fd, &termios_s)) {
    nl_error(2, "Error from tcgetattr: %s", strerror(errno));
  }
  for (unsigned drv = 0; drv < N_TWISTORR_DRIVES; ++drv) {
    if ((agilent_absent >> drv) & 0x1) {
      backoff_secs[drv] = 60;
      TT_TM_p->drive[drv].flags |= 0x80;
    } else {
      backoff_secs[drv] = 0;
      TT_TM_p->drive[drv].flags &= ~0x80;
    }
  }
}


TwisTorr::~TwisTorr() {
  if (pending && !pending->persistent)
    delete(pending);
  while (polls.size() > 0) {
    delete(polls[0]);
    polls.pop_front();
  }
  while (cmd_free.size() > 0) {
    delete(cmd_free.front());
    cmd_free.pop_front();
  }
  while (cmds.size() > 0) {
    delete(cmds[0]);
    cmds.pop_front();
  }
}

/**
 * Adapted from SunTrack. Adjusts the VMIN termios value
 * based on the specific command. This version is incomplete.
 * It adjusts for the request size so we can skip over the RS485 echo,
 * but it does not anticipate any more than the minimal response
 * of 6 characters. We could add command-specific response size
 * as noted in the comments. We could also adjust the VTIME
 * parameter, but it may be redundant, since we have the overriding
 * Selector timeout working for us.
 */
void TwisTorr::update_termios() {
  // int cur_min = pending->req_sz + pending->min - nc;
  int cur_min = pending->req_sz + 6 - nc;
  if (cur_min < 1) cur_min = 1;
  if (cur_min != termios_s.c_cc[VMIN]
      // || pending->time != termios_s.c_cc[VTIME]
        ) {
    termios_s.c_cc[VMIN] = cur_min;
    // termios_s.c_cc[VTIME] = pending->time;
    if (tcsetattr(fd, TCSANOW, &termios_s)) {
      nl_error(2, "Error from tcsetattr: %s", strerror(errno));
    }
    // nl_error(-2, "TwisTorr VMIN=%d VTIME=%d", cur_min, pending->time);
  }
}

command_request *TwisTorr::new_command_req() {
  command_request *cr;
  if (cmd_free.empty()) {
    nl_error(MSG_DBG(2), "new_command_req() via new");
    cr = new command_request;
  } else {
    nl_error(MSG_DBG(2), "new_command_req() via cmd_free");
    cr = cmd_free[0];
    cmd_free.pop_front();
  }
  return cr;
}

void TwisTorr::enqueue_command(command_request *creq) {
  creq->active = true;
  cmds.push_back(creq);
  Stor->set_gflag(cmd_gflag);
}

void TwisTorr::enqueue_poll(command_request *creq) {
  creq->active = true;
  creq->persistent = true;
  polls.push_back(creq);
}

void TwisTorr::free_command(command_request *creq) {
  creq->active = false;
  if (!creq->persistent) {
    cmd_free.push_back(creq);
  }
}

Timeout *TwisTorr::GetTimeout() {
  return pending ? &TO : 0;
}

/**
 * Can be triggered due to:
 *   Input data ready from TwisTorr
 *   Timeout waiting for data from TwisTorr
 *   New command ready to be transmitted (gflag(1))
 *   Time to reissue periodic poll commands (gflag(0))
 */
int TwisTorr::ProcessData(int flag) {
  if (flag & Selector::gflag(0)) {
    if (cur_poll == polls.end())
      cur_poll = polls.begin();
    /* else complain? */
  }
  if (flag & (Selector::Sel_Read | Selector::Sel_Timeout)) {
    fillbuf();
    if (pending) {
      /* This loop checks for the echo at buf[cp], advancing cp if it
       * does not match
       */
      for (cp = 0; cp + pending->req_sz + pending->rep_sz < nc; ++cp) {
        unsigned i;
        for (i = 0; i < pending->req_sz; ++i) {
          if (buf[cp+i] != pending->req_buf[i])
            break;
        }
        if (i == pending->req_sz) {
          break;
        }
      }
      // Now we either have the request at buf[cp] or we
      // don't have enough characters.
      if (cp + pending->req_sz > nc) {
        if (flag & Selector::Sel_Timeout) {
          report_err("Timeout on echo from TwisTorr request: %s",
            pending->ascii_escape());
        } else {
          consume(cp);
          update_termios();
          return 0;
        }
      } else {
        command_request *enbl_remote;
        switch (pending->process_reply(&buf[cp+pending->req_sz],
                    nc-cp-pending->req_sz)) {
          case TT_rep_ok:
            nl_error(MSG_DBG(1), "Reply received OK");
            report_ok();
            if (backoff_secs[pending->drive]) {
              backoff_secs[pending->drive] = 0;
              TT_TM_p->drive[pending->drive].flags &= ~0x80;
              backoff_TO[pending->drive].Clear();
            }
            break;
          case TT_rep_incomplete:
            if (flag & Selector::Sel_Timeout) {
              uint16_t bs = backoff_secs[pending->drive];
              if (bs) {
                bs = bs > 30 ? 60 : bs*2;
              } else {
                report_err("Timeout from TwisTorr request: %s",
                  pending->ascii_escape());
                bs = 1;
                TT_TM_p->drive[pending->drive].flags |= 0x80;
              }
              backoff_secs[pending->drive] = bs;
              backoff_TO[pending->drive].Set(bs, 0);
            } else {
              // Could Update min for rep_sz - nc
              update_termios();
              return 0;
            }
            break;
          case TT_rep_win_disabled:
            nl_error(2,"Window Disabled on drive %d:%d %s", pending->drive,
              pending->window, pending->read ? "read" : "write");
            enbl_remote = new_command_req();
            if (enbl_remote->init(pending->drive, 8, false,
                  (const uint8_t*)"0")) {
              free_command(enbl_remote);
            } else {
              enqueue_command(enbl_remote);
              enqueue_command(pending);
              pending = 0;
            }
            break;
          case TT_rep_error:
            report_err("%s: req was: %s", pending->error_msg, pending->ascii_escape());
            break;
          default:
            nl_error(4, "Invalid response from process_reply");
        }
        if (nl_debug_level < MSG_DBG(2)) report_ok(); // Temporary error suppression suppression
      }
      if (pending)
        free_command(pending);
      pending = 0;
      TO.Clear();
      consume(nc);
    } else {
      report_err("Unexpected data from TwisTorr");
      consume(nc);
    }
  }
  while (!pending && !cmds.empty()) {
    command_request *cr = cmds[0];
    cmds.pop_front();
    if (submit_req(cr)) break;
  }
  while (!pending && cur_poll != polls.end()) {
    if (submit_req(*cur_poll++)) break;
  }
  return 0;
}

/**
 * @return true if command was submitted
 */
bool TwisTorr::submit_req(command_request *req) {
  if (backoff_secs[req->drive] && !backoff_TO[req->drive].Expired()) {
    free_command(req);
    return false;
  }
  switch (req->CmdRestrictions) {
    case CR_none: break;
    case CR_write_in_stop:
      if ((!req->read) && (TT_TM_p->drive[req->drive].flags & 1)) {
        nl_error(2, "Drive %d Window %d not allowed when started",
          req->drive, req->window);
        free_command(req);
        return false;
      }
      break;
    case CR_read_in_start:
      if (req->read && !(TT_TM_p->drive[req->drive].flags & 1)) {
        req->default_read_action();
        free_command(req);
        return false;
      }
      break;
    default:
      nl_error(4, "Invalid CmdRestrictions: %d\n", req->CmdRestrictions);
  }
  pending = req;
  if (req->write(fd))
    report_err("Write error");
  TO.Set(0, pending->TO_msecs);
  update_termios();
  return true;
}
