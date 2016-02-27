/*
 * CmdReq.cc
 * command_request object
 */
#include <string.h>
#include <stdlib.h>
#include "nXDS.h"
#include "nortlib.h"

command_request::command_request() {
  device = 0;
  address = 0;
  active = false;
  persistent = false;
  TO_msecs = 250;
  rep_sz = 14; // The minimal #ss:dd*C802 0\r
  CmdRestrictions = CR_none;
}

/**
 * @return true if command is not valid. Caller should return object to
 * the free queue.
 */
bool command_request::init(uint8_t drive, uint8_t req_type,
        uint16_t address, bool read, uint16_t value) {
  active = false;
  TO_msecs = 250;
  persistent = false;
  req_qual = 0;
  switch (address) {
    case 801:
      req_qual = '?';
      rep_sz = 30;
      break;
    case 802: // Start/Stop
      switch (req_type) {
        case 'C': req_qual = '!'; break;
        case 'V':
          req_qual = '?';
          rep_sz = 35;
          TO_msecs = 500;
          // CmdRestrictions = CR_read_in_start;
          break;
      }
      break;
    case 803: // Standby Speed
    case 805: req_qual = '!'; break; // Set Standby Speed
    case 808:
    case 809:
    case 826: req_qual = '?'; break;
    default: break;
  }
  if (!req_qual) {
    nl_error(2, "Invalid or unsupported address: %c%d", req_type,
      address);
    return true;
  }
  if (req_qual == '!' && req_type != 'C') {
    nl_error(2, "req_type must be 'C' for req_qual '!' in %c%d",
      req_type, address);
    return true;
  }
  if (req_type == 'C' && req_qual != '!') {
    nl_error(2, "req_qual must be '!' for req_type 'C' in %c%d",
      req_type, address);
    return true;
  }
  if (read && req_qual != '?') {
    nl_error(2, "req_qual must be '?' for read command %c%d",
      req_type, address);
  }
  // nl_error(MSG_DBG(2), "command_request::init #1");
  if (drive < 0 || drive >= N_NXDS_DRIVES) {
    nl_error(2, "Drive number %d out of range", drive);
    return true;
  }
  this->drive = drive;
  this->device = nXDS::nX_DevNo[drive];
  this->address = address;
  this->read = read;
  this->req_type = req_type;
  this->value = value;
  if (read) {
    req_sz = sprintf((char *)req_buf, "#%02d:%02d%c%c%03d\r", device,
      master_device, req_qual, req_type, address);
  } else {
    req_sz = sprintf((char *)req_buf, "#%02d:%02d%c%c%03d %d\r",
      device, master_device, req_qual, req_type, address, value);
  }
  return false;
}

// nX_rep_ok, nX_rep_incomplete, nX_rep_error
nX_rep_status_t nXDS::process_reply() {
  int src, dest, rep_addr;
  if (nc-cp < 14) return nX_rep_incomplete;
  if (not_str("#") ||
      not_int(dest) ||
      not_str(":") ||
      not_int(src)) {
    return (cp < nc) ? nX_rep_error : nX_rep_incomplete;
  }
  if (src != pending->device) {
    report_err("Response from wrong device");
    return nX_rep_error;
  }
  if (dest != command_request::master_device) {
    report_err("Response not addressed to master device");
    return nX_rep_error;
  }
  if (nc-cp < 2)
    return nX_rep_incomplete;
  uint8_t rep_qual = buf[cp++];
  uint8_t rep_type = buf[cp++];
  if (rep_type != pending->req_type) {
    report_err("Reply type '%c' did not match request type '%c'",
      rep_type, pending->req_type);
    return nX_rep_error;
  }
  if (rep_qual == '*') {
    if (rep_type != 'C') {
      report_err("Expected rep_type 'C' for rep_qual '*'");
      return nX_rep_error;
    }
  } else {
    if (rep_type == 'C') {
      report_err("Expected rep_qual '*' for req_type 'C'");
      return nX_rep_error;
    }
    if (rep_qual != '=') {
      report_err("Expected rep_qual '=' for read request");
      return nX_rep_error;
    }
  }
  if (not_int(rep_addr) || not_str(" ")) {
    return (cp<nc) ? nX_rep_error : nX_rep_incomplete;
  }
  if (rep_addr != pending->address) {
    report_err("Reply address does not match request");
    return nX_rep_error;
  }
  // Now we need to decide how to process the reply based
  // on the address and/or rep_qual
  if (rep_qual == '*') {
    int cmd_rep;
    if (not_int(cmd_rep)) {
      return (cp >= nc) ? nX_rep_incomplete : nX_rep_error;
    }
    if (cmd_rep != 0) {
      nl_error(2, "Command %c%d returned error status %d",
        pending->req_type, pending->address, cmd_rep);
      return nX_rep_error;
    } else if (pending->address == 802) {
      if (pending->value) {
        nX_TM_p->drive[pending->drive].pump_on |= 1;
      } else {
        nX_TM_p->drive[pending->drive].pump_on &= ~1;
      }
    }
  } else {
    int vals[3];
    uint16_t hvals[4];
    switch (rep_addr) {
      case 808: //ddd;ddd Pump and controller temp
        if (not_int(vals[0]) ||
            not_str(";") ||
            not_int(vals[1])) {
          return (cp >= nc) ? nX_rep_incomplete : nX_rep_error;
        }
        // nX_TM_p->drive[pending->drive].pump_temp = vals[0];
        if (vals[1] == -200) {
          if (nX_TM_p->drive[pending->drive].controller_temp != 255)
            nl_error(2, "controller temp reportedly not implemented");
          vals[1] = 255;
        }
        nX_TM_p->drive[pending->drive].controller_temp = vals[1];
        break;
      case 809: //dddd;[-+]ddd;[-+]ddddd Link voltage, motor current/power
        if (not_int(vals[0]) ||
            not_str(";") ||
            not_int(vals[1]) ||
            not_str(";") ||
            not_int(vals[2])) {
          return (cp >= nc) ? nX_rep_incomplete : nX_rep_error;
        }
        nX_TM_p->drive[pending->drive].link_voltage = vals[0];
        nX_TM_p->drive[pending->drive].motor_current = vals[1];
        nX_TM_p->drive[pending->drive].motor_power = vals[2];
        break;
      case 802: //ddd;hhhh;hhhh;hhhh;hhhh Motor freq & status
        if (not_int(vals[0]) ||
            not_str(";") ||
            not_hex(hvals[0]) ||
            not_str(";") ||
            not_hex(hvals[1]) ||
            not_str(";") ||
            not_hex(hvals[2]) ||
            not_str(";") ||
            not_hex(hvals[3])) {
          return (cp >= nc) ? nX_rep_incomplete : nX_rep_error;
        }
        nX_TM_p->drive[pending->drive].motor_freq = vals[0];
        nX_TM_p->drive[pending->drive].status &= ~0xFFFE;
        nX_TM_p->drive[pending->drive].status |= (hvals[0]&0x003F)<<1;
        nX_TM_p->drive[pending->drive].status |= (hvals[1]&0x00C0)<<1;
        nX_TM_p->drive[pending->drive].status |=
          ((hvals[3]&0x003E)<<8) | (hvals[3]&0xC000);
        nX_TM_p->drive[pending->drive].pump_on |= 2;
        nl_error(MSG_DBG(2), "Received '%s'", ascii_escape((const char *)buf));
        nl_error(MSG_DBG(2), "parsed '%d;%04x;%04x;%04x;%04x'",
          vals[0], hvals[0], hvals[1], hvals[2], hvals[3]);
        break;
      case 801: // PumpType;Dxxxxxxx Y;ddd ID: treat as a string
        { int i;
          for (i = 0; cp + i < nc && buf[cp+i] != '\r'; ++i);
          if (cp+i < nc) {
            buf[cp+i] = '\0';
            nl_error(0, "Drive %d ID: %s", pending->drive, &buf[cp]);
          } else {
            return nX_rep_incomplete;
          }
        }
        break;
      case 826: // hhhh Service Status
        if (not_hex(hvals[0])) {
          return (cp >= nc) ? nX_rep_incomplete : nX_rep_error;
        }
        if (hvals[0] & 0x01)
          nl_error(1, "Drive %d Tip seal service due", pending->drive);
        if (hvals[0] & 0x02)
          nl_error(1, "Drive %d Bearing seal service due", pending->drive);
        if (hvals[0] & 0x01)
          nl_error(1, "Drive %d Controller service due", pending->drive);
        break;
      default: nl_error(4, "Unexpected reply addr %d", rep_addr);
    }
  }
  return nX_rep_ok;
}

/**
 * Invokes ascii_escape on the request buffer
 */
const char *command_request::ascii_escape() {
  return ::ascii_escape((const char *)req_buf, req_sz);
}

/**
 * Writes the request to the specified file descriptor.
 * @return -1 if write returns anything but req_sz. 0 otherwise.
 */
int command_request::write(int fd) {
  if (nl_debug_level <= MSG_DBG(1)) {
    nl_error(MSG_DBG(1), "Sending: '%s'", ascii_escape());
  }
  int nb = ::write(fd, req_buf, req_sz);
  return (nb != (int)req_sz) ? -1 : 0;
}
