#include "modbus.h"
#include "oui.h"
#include "nortlib.h"

char *modbus_path;

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { Selector Loop;
    Modbus_t MB_TM;
    modbus MB(modbus_path, &MB_TM);
    TM_Selectee TM("Modbus", &MB_TM, sizeof(MB_TM));
    modbus_cmd Cmd(&MB);
    Loop.add_child(&MB);
    Loop.add_child(&TM);
    Loop.add_child(&Cmd);
    Loop.event_loop();
  }
}

modbus::modbus(const char *path, Modbus_t *MB_TM) :
      Ser_Sel(path, O_RDWR | O_NONBLOCK, 80) {
  pending = 0;
  for (int i = 0; i < 3; ++i) {
    cmd_float_free.push_back(new modbus_cmd_float);
  }
  for (int i = 0; i < 3; ++i) {
    cmd_int_free.push_back(new modbus_cmd_int);
  }
  polls.push_back(new modbus_poll_float(PM6C_1_ID, 360, &MB_TM->PM6C_T1));
  polls.push_back(new modbus_poll_float(PM6C_1_ID, 2172, &MB_TM->PM6C_SP1));
  polls.push_back(new modbus_poll_float(PM6C_1_ID, 440, &MB_TM->PM6C_T2));
  polls.push_back(new modbus_poll_float(PM6C_1_ID, 2252, &MB_TM->PM6C_SP2));
  polls.push_back(new modbus_poll_int(F4_1_ID, 100, &MB_TM->F4_IV1));
  polls.push_back(new modbus_poll_int(F4_1_ID, 104, &MB_TM->F4_IV2));
  polls.push_back(new modbus_poll_int(F4_1_ID, 108, &MB_TM->F4_IV3));
  polls.push_back(new modbus_poll_int(F4_1_ID, 200, &MB_TM->F4_Op));
  polls.push_back(new modbus_poll_int(F4_1_ID, 300, &MB_TM->F4_SP1));
  polls.push_back(new modbus_poll_int(F4_1_ID, 319, &MB_TM->F4_SP2));
  cur_poll = polls.end();
  setup(19200, 8, 'n', 1, 5, 1);
  // 38400, 8, 'n', 1: based on default in the PM6C manual
  // 19200 is the maximum the F4 will go.
  // min = 5 is the smallest expected reply, for an error packet
  // time = 1[/10 of a second]
  // We could adjust min when a partial record is received, but
  // I think we'll try just using the overall timeout in that
  // case unless we find that happening a lot.
  flush_input();
  flags = Selector::Sel_Read | Selector::gflag(0) | Selector::Sel_Timeout;
}

modbus::~modbus() {
  if (pending) delete(pending);
  while (polls.size() > 0) {
    delete(polls[0]);
    polls.pop_front();
  }
  while (cmd_float_free.size() > 0) {
    delete(cmd_float_free[0]);
    cmd_float_free.pop_front();
  }
  while (cmd_int_free.size() > 0) {
    delete(cmd_int_free[0]);
    cmd_int_free.pop_front();
  }
  while (cmds.size() > 0) {
    delete(cmds[0]);
    cmds.pop_front();
  }
}

void modbus::queue_cmd_float(uint8_t device, uint16_t address, float value) {
  if (cmd_float_free.empty()) {
    nl_error(2, "Command queue overflow");
  } else {
    modbus_cmd_float *cmd = cmd_float_free[0];
    cmd_float_free.pop_front();
    cmd->init(device, address, value);
    cmds.push_back(cmd);
    check_cmd();
  }
}

void modbus::queue_cmd_int(uint8_t device, uint16_t address, int16_t value) {
  if (cmd_int_free.empty()) {
    nl_error(2, "Command queue overflow");
  } else {
    modbus_cmd_int *cmd = cmd_int_free[0];
    cmd_int_free.pop_front();
    cmd->init(device, address, value);
    cmds.push_back(cmd);
    check_cmd();
  }
}

void modbus::check_cmd() {
  if (!pending && !cmds.empty()) {
    submit_req(cmds[0]);
    cmds.pop_front();
  }
}

void modbus::submit_req(modbus_req *req) {
  pending = req;
  if (req->write(fd))
    report_err("Write error");
  TO.Set(0, 250);
  // update min for rep_sz
}


/**
 */
int modbus::ProcessData(int flag) {
  if (flag & Selector::gflag(0)) {
    if (cur_poll == polls.end())
      cur_poll = polls.begin();
  }
  if (flag & (Selector::Sel_Read | Selector::Sel_Timeout)) {
    fillbuf();
    if (pending) {
      // This block skips past the echo
      // but it does not advance cp
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
      if (cp + pending->req_sz + pending->rep_sz > nc) {
        if (flag & Selector::Sel_Timeout) {
          report_err("Timeout from Modbus request: %s",
            pending->ascii_escape());
        } else {
          consume(cp);
          return 0;
        }
      } else {
        switch (pending->process_reply(&buf[cp+pending->req_sz], nc-cp-pending->req_sz)) {
          case MB_rep_ok:
            report_ok();
            break;
          case MB_rep_incomplete:
            if (flag & Selector::Sel_Timeout)
              report_err("Timeout from Modbus request: %s",
                pending->ascii_escape());
            else {
              // Could Update min for rep_sz - nc
              return 0;
            }
            break;
          case MB_rep_error:
            report_err("%s: req was: %s", pending->error_msg, pending->ascii_escape());
            break;
          case MB_rep_MB_err:
            report_err("Modbus error code 0x%02d", pending->MB_err_code);
            break;
          default:
            nl_error(4, "Invalid response from process_reply");
        }
      }
      pending->dispose(this);
      TO.Clear();
      consume(nc);
    } else {
      report_err("Unexpected data from modbus");
      consume(nc);
    }
  }
  check_cmd();
  if (!pending && cur_poll != polls.end()) {
    submit_req(*cur_poll++);
  }
  return 0;
}

Timeout *modbus::GetTimeout() {
  return pending ? &TO : 0;
}

modbus_req::modbus_req(unsigned char device, unsigned char function_code,
    unsigned req_size, unsigned short rep_size) {
  req_sz = reqb_sz = req_size;
  rep_sz = rep_size;
  req_buf = (unsigned char *)new_memory(reqb_sz);
  devID = device;
  req_buf[0] = device;
  req_buf[1] = function_code;
  reply_status = MB_rep_ok;
}

modbus_req::~modbus_req() {
  delete(req_buf);
}

/**
 * Default disposal method. Appropriate for modbus_poll_float.
 */
void modbus_req::dispose(modbus *MB) {
  MB->pending = 0;
}

/**
 * @return 0 if reply is complete, 1 if reply is incomplete, -1 on error.
 */
MB_rep_status_t modbus_req::process_reply(unsigned char *rep, unsigned nb) {
  reply_status = MB_rep_ok;
  if (nb < 5) reply_status = MB_rep_incomplete; /* dev, cmd|err, exc. code, CRC */
  else if ((rep[1] & 0x80) && (nb < 5)) reply_status = MB_rep_incomplete;
  else if (!(rep[1] & 0x80) && (nb < rep_sz)) reply_status = MB_rep_incomplete;
  if (reply_status == MB_rep_ok) {
    if (rep[0] != req_buf[0]) {
      reply_status = MB_rep_error;
      error_msg = "Reply address mismatch";
    } else if ((rep[1] & 0x7F) != req_buf[1]) {
      reply_status = MB_rep_error;
      error_msg = "Reply function code mismatch";
    } else if (rep[1] & 0x80) {
      if (crc_ok(rep, 5)) {
        reply_status = MB_rep_MB_err;
        MB_err_code = rep[2];
      } else {
        reply_status = MB_rep_error;
        error_msg = "CRC error on Modbus error message";
      }
    } else if (!crc_ok(rep, rep_sz)) {
      reply_status = MB_rep_error;
      error_msg = nb > rep_sz ? "CRC error + extra chars" : "CRC error";
    } else {
      process_pdu(rep);
      // We're ignoring (and dropping) any extra characters
    }
  }
  return reply_status;
}

/**
 * Writes the request to the specified file descriptor.
 * @return -1 if write returns anything but req_sz. 0 otherwise.
 */
int modbus_req::write(int fd) {
  int nb = ::write(fd, req_buf, req_sz);
  return (nb != (int)req_sz) ? -1 : 0;
}

/**
 * Invokes ascii_escape on the request buffer
 */
const char *modbus_req::ascii_escape() {
  return ::ascii_escape((const char *)req_buf, req_sz);
}

/**
 * Requires no arguments because this is only called on the
 * request, and the buffer and size are stored in the object.
 */
void modbus_req::crc_set() {
  unsigned short crc_calc = crc(req_buf, req_sz-2);
  req_buf[req_sz-2] = crc_calc & 0xFF;
  req_buf[req_sz-1] = (crc_calc>>8) & 0xFF;
}

void modbus_req::float_swap(unsigned char *dest, unsigned char *src) {
  dest[1] = src[0];
  dest[0] = src[1];
  dest[3] = src[2];
  dest[2] = src[3];
}

void modbus_req::word_swap(uint8_t *dest, uint8_t *src) {
  dest[1] = src[0];
  dest[0] = src[1];
}

/**
 * @param rep pointer to buffer
 * @param nb size of buffer including 2-byte crc
 * @return non-zero if the CRC checks out OK
 */
int modbus_req::crc_ok(unsigned char *rep, unsigned nb) {
  unsigned short crc_rep = (rep[nb-1]<<8) + rep[nb-2];
  unsigned short crc_calc = crc(rep, nb-2);
  return crc_rep == crc_calc;
}

/**
 * @param buf pointer to buffer
 * @param nb size of buffer not counting 2-byte crc
 * @return the 16-bit CRC code
 */
unsigned short modbus_req::crc(unsigned char *buf, unsigned nb) {
  return CRC16(buf, nb);
}

modbus_poll_float::modbus_poll_float(unsigned char device,
    uint16_t address, float *dest)
    : modbus_req(device, 0x03, 8, 9) {
  // address += 40000;
  req_buf[2] = (address>>8)&0xFF;
  req_buf[3] = address & 0xFF;
  req_buf[4] = 0;
  req_buf[5] = 2;
  crc_set();
  destination = dest;
}

modbus_poll_float::~modbus_poll_float() {}

void modbus_poll_float::process_pdu(uint8_t *rep) {
  // could check that rep[2] == 4
  float_swap((uint8_t *)destination, &rep[3]);
}

modbus_poll_int::modbus_poll_int(uint8_t device,
    uint16_t address, int16_t *dest) : modbus_req(device, 0x03, 8, 7) {
  req_buf[2] = (address>>8)&0xFF;
  req_buf[3] = address & 0xFF;
  req_buf[4] = 0;
  req_buf[5] = 1;
  crc_set();
  destination = dest;
}

modbus_poll_int::~modbus_poll_int() {}

void modbus_poll_int::process_pdu(unsigned char *rep) {
  word_swap((uint8_t*)destination, &rep[3]);
}

modbus_cmd_float::modbus_cmd_float() : modbus_req(0, 0x10, 13, 8) {
}

modbus_cmd_float::~modbus_cmd_float() {}

/**
 * Disposal method for float commands.
 */
void modbus_cmd_float::dispose(modbus *MB) {
  MB->cmd_float_free.push_back(this);
  MB->pending = 0;
}

void modbus_cmd_float::init(unsigned char device, unsigned short address,
        float arg) {
  // address += 40000;
  req_buf[0] = device;
  req_buf[2] = (address>>8)&0xFF;
  req_buf[3] = address & 0xFF;
  req_buf[4] = 0;
  req_buf[5] = 2;
  req_buf[6] = 4; // byte count
  float_swap(&req_buf[7], (unsigned char *)&arg);
  crc_set();
}

void modbus_cmd_float::process_pdu(unsigned char *rep) {}

modbus_cmd_int::modbus_cmd_int() : modbus_req(0, 0x06, 8, 8) {
}

modbus_cmd_int::~modbus_cmd_int() {}

/**
 * Disposal method for float commands.
 */
void modbus_cmd_int::dispose(modbus *MB) {
  MB->cmd_int_free.push_back(this);
  MB->pending = 0;
}

void modbus_cmd_int::init(uint8_t device, uint16_t address,
        int16_t arg) {
  // address += 40000;
  req_buf[0] = device;
  req_buf[2] = (address>>8)&0xFF;
  req_buf[3] = address & 0xFF;
  word_swap(&req_buf[4], (uint8_t *)&arg);
  crc_set();
}

void modbus_cmd_int::process_pdu(unsigned char *rep) {}

/**
 * Reads from cmd/modbus
 */
modbus_cmd::modbus_cmd(modbus *MB_in)
    : Ser_Sel(tm_dev_name("cmd/modbus"), O_RDONLY, 40) {
  MB = MB_in;
}

modbus_cmd::~modbus_cmd() {}

int modbus_cmd::ProcessData(int flag) {
  if (flag & Selector::Sel_Read) {
    fillbuf();
    if (nc == 0) return 1;
    cp = 0;
    switch (buf[0]) {
      case 'S':
        { int channel;
          float value;
          ++cp;
          if (not_int(channel) ||
              not_str(":") ||
              not_float(value)) {
            if (cp == nc) report_err("Incomplete command");
          } else {
            int dev_id = 0;
            unsigned short chan_addr;
            switch (channel) {
              case 1:
                dev_id = modbus::PM6C_1_ID;
                chan_addr = 2160;
                break;
              case 2:
                dev_id = modbus::PM6C_1_ID;
                chan_addr = 2240;
                break;
              default:
                nl_error(2, "Invalid channel number: %d", channel);
                break;
            }
            if (dev_id)
              MB->queue_cmd_float(dev_id, chan_addr, value);
          }
        }
        break;
      case 'F': // F4 Commands
        { int channel;
          int value;
          ++cp;
          if (not_int(channel) ||
              not_str(":") ||
              not_int(value)) {
            if (cp == nc) report_err("Incomplete command");
          } else {
            int dev_id = 0;
            uint16_t chan_addr;
            switch (channel) {
              case 1:
                dev_id = modbus::F4_1_ID;
                chan_addr = 300;
                break;
              case 2:
                dev_id = modbus::F4_1_ID;
                chan_addr = 319;
                break;
              case 3:
                dev_id = modbus::F4_1_ID;
                chan_addr = 1209;
                break;
              case 4:
                dev_id = modbus::F4_1_ID;
                chan_addr = 1217;
                break;
              default:
                nl_error(2, "Invalid channel number: %d", channel);
                break;
            }
            if (dev_id)
              MB->queue_cmd_int(dev_id, chan_addr, (int16_t)value);
          }
        }
        break;
      case 'Q':
        consume(nc);
        return 1;
      default:
        report_err("Unrecognized command");
        break;
    }
    consume(nc);
  }
  return 0;
}
