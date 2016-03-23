#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "UPS.h"
#include "nortlib.h"

UPS_ser::UPS_ser(const char *path, UPS_TM_t *TMptr) :
    Ser_Sel(path, O_RDWR|O_NONBLOCK, reply_max*2) {
  if (path == 0) {
    nl_error(3, "No path specified for UPS device");
  } else {
    nl_error(MSG_DBG(1), "Opened %s for UPS device", path);
  }
  UPS_TMp = TMptr;
  UPS_TMp->QGS_V_in = 0;
  UPS_TMp->QGS_F_in = 0;
  UPS_TMp->QGS_V_out = 0;
  UPS_TMp->QGS_V_out = 0;
  UPS_TMp->QGS_I_out = 0;
  UPS_TMp->QGS_VBusP = 0;
  UPS_TMp->QGS_VBusN = 0;
  UPS_TMp->QGS_VBatP = 0;
  UPS_TMp->QGS_VBatN = 0;
  UPS_TMp->QGS_Tmax = 0;
  UPS_TMp->QGS_Status = 0;
  UPS_TMp->QWS = 0;
  UPS_TMp->QBV_Vbat = 0;
  UPS_TMp->UPS_Response = 0;
  UPS_TMp->QMOD = 0;
  UPS_TMp->QGS_LoadPct = 0;
  UPS_TMp->QBV_Piece = 0;
  UPS_TMp->QBV_Group = 0;
  UPS_TMp->QBV_Capacity = 0;
  UPS_TMp->QBV_Remain_Time = 0;
  
  pending = 0;
  cur_poll = polls.begin();
  setup(2400, 8, 'n', 1, reply_max, 1);
  flush_input();
  flags = Selector::Sel_Read | Selector::gflag(tm_gflag) |
          Selector::gflag(cmd_gflag) | Selector::Sel_Timeout;
  if (tcgetattr(fd, &termios_s)) {
    nl_error(2, "Error from tcgetattr: %s", strerror(errno));
  }
}


UPS_ser::~UPS_ser() {
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
 * We could also adjust the VTIME
 * parameter, but it may be redundant, since we have the overriding
 * Selector timeout working for us.
 */
void UPS_ser::update_termios() {
  int cur_min = pending->rep_min - nc;
  if (cur_min < 1) cur_min = 1;
  if (cur_min != termios_s.c_cc[VMIN]) {
    termios_s.c_cc[VMIN] = cur_min;
    if (tcsetattr(fd, TCSANOW, &termios_s)) {
      nl_error(2, "Error from tcsetattr: %s", strerror(errno));
    }
  }
}

void UPS_ser::set_response_bit(uint8_t mask) {
  UPS_TMp->UPS_Response |= mask;
  UPS_TMp->UPS_Response2 |= mask;
}

void UPS_ser::clear_response_bit(uint8_t mask) {
  UPS_TMp->UPS_Response &= ~mask;
  UPS_TMp->UPS_Response2 &= ~mask;
}

/**
 * @return NULL on error.
 */
UPS_cmd_req *UPS_ser::new_command_req(const char *cmdquery,
        UPS_parser parser_in, unsigned reply_min) {
  UPS_cmd_req *cr;
  if (cmd_free.empty()) {
    nl_error(MSG_DBG(2), "new_command_req() via new");
    cr = new UPS_cmd_req;
    if (cr == 0) {
      nl_error(3, "Out of memory in new_command_req()");
      return 0;
    }
  } else {
    nl_error(MSG_DBG(2), "new_command_req() via cmd_free");
    cr = cmd_free[0];
    cmd_free.pop_front();
  }
  if (cr->init(cmdquery, parser_in, reply_min)) {
    free_command(cr);
    return 0;
  }
  return cr;
}

void UPS_ser::enqueue_command(UPS_cmd_req *creq) {
  creq->active = true;
  cmds.push_back(creq);
  Stor->set_gflag(cmd_gflag);
}

void UPS_ser::enqueue_command(const char *cmdquery) {
  UPS_cmd_req *cr =
    new_command_req(cmdquery, &UPS_ser::parse_cmd, 5);
  if (cr == 0) return;
  enqueue_command(cr);
}

void UPS_ser::enqueue_query(const char *cmdquery, unsigned reply_min) {
  UPS_cmd_req *cr =
    new_command_req(cmdquery, &UPS_ser::parse_query, reply_min);
  if (cr == 0) return;
  enqueue_command(cr);
}

/**
 * Could be eliminated.
 */
void UPS_ser::enqueue_poll(UPS_cmd_req *creq) {
  creq->active = true;
  creq->persistent = true;
  polls.push_back(creq);
}

void UPS_ser::enqueue_poll(const char *cmdquery, UPS_parser parser_in,
        unsigned reply_min) {
  nl_error(MSG_DBG(1), "Enqueuing poll: '%s'", ascii_escape(cmdquery));
  UPS_cmd_req *cr =
    new_command_req(cmdquery, parser_in, reply_min);
  if (cr == 0) {
    nl_error(MSG_DBG(1), "new_command_req() returned NULL");
    return;
  }
  enqueue_poll(cr);
}

void UPS_ser::free_command(UPS_cmd_req *creq) {
  creq->active = false;
  if (!creq->persistent) {
    cmd_free.push_back(creq);
  }
}

void UPS_ser::enqueue_polls() {
  nl_error(MSG_DBG(1), "Enqueuing polls");
  enqueue_poll("QMOD", &UPS_ser::parse_QMOD, 3);
  enqueue_poll("QGS", &UPS_ser::parse_QGS, 76);
  enqueue_poll("QWS", &UPS_ser::parse_QWS, 66);
  enqueue_poll("QBV", &UPS_ser::parse_QBV, 21);
  enqueue_poll("QSK1", &UPS_ser::parse_QSK1, 3);
}

Timeout *UPS_ser::GetTimeout() {
  return pending ? &TO : 0;
}

/**
 * Can be triggered due to:
 *   Input data ready from UPS
 *   Timeout waiting for data from UPS
 *   New command ready to be transmitted (gflag(1))
 *   Time to reissue periodic poll commands (gflag(0))
 */
int UPS_ser::ProcessData(int flag) {
  if (flag & Selector::gflag(0)) {
    if (cur_poll == polls.end()) {
      cur_poll = polls.begin();
    }
    /* else complain? */
  }
  if (flag & (Selector::Sel_Read | Selector::Sel_Timeout)) {
    fillbuf();
    cp = 0;
    if (pending) {
      if ((this->*(pending->parser))(pending)) { // returns true if not done
        if (TO.Expired()) {
          report_err("Timeout from UPS request: %s",
            pending->ascii_escape());
        } else {
          update_termios();
          return 0;
        }
      }
      free_command(pending);
      pending = 0;
      TO.Clear();
      consume(nc);
    } else {
      report_err("Unexpected data from UPS");
      consume(nc);
    }
  }
  while (!pending && !cmds.empty()) {
    UPS_cmd_req *cr = cmds[0];
    cmds.pop_front();
    nl_error(MSG_DBG(0), "Issuing command '%s'", cr->ascii_escape());
    if (submit_req(cr)) break;
  }
  while (!pending && cur_poll != polls.end()) {
    if (submit_req(*cur_poll++)) break;
  }
  if (!pending) {
    nl_error(MSG_DBG(2),"UPS_ser::Process_Data: No commands pending");
  }
  return 0;
}

/**
 * Issues the specified command to the serial device
 * @return true if command was submitted
 */
bool UPS_ser::submit_req(UPS_cmd_req *req) {
  pending = req;
  if (req->write(fd))
    report_err("Write error");
  TO.Set(0, 500);
  update_termios();
  return true;
}
