/*
 * CmdReq.cc
 * command_request object
 */
#include <string.h>
#include <stdlib.h>
#include "TwisTorr.h"
#include "nortlib.h"

command_request::command_request() {
  device = 0;
  window = 0;
  read = false;
  fl_ptr = 0;
  bit_ptr = 0;
  bit_mask = 0;
  active = false;
  persistent = false;
  TO_msecs = 250;
  CmdRestrictions = CR_none;
}

/**
 * @return true if command is not valid. Caller should return object to
 * the free queue.
 */
bool command_request::init(uint8_t drive, uint16_t window, bool read,
        const uint8_t *data) {
  fl_ptr = 0;
  bit_ptr = 0;
  active = false;
  TO_msecs = 250;
  CmdRestrictions = CR_none;
  persistent = false;
  switch (window) {
    case 0: cmd_type = 'L'; break; // Start/Stop
    case 1: cmd_type = 'L'; break; // Low Speed
    case 8: cmd_type = 'L'; break; // Serial=1,Remote=0
    case 100:
      cmd_type = 'A';
      CmdRestrictions = CR_write_in_stop;
      break; // Soft Start NO=0, YES=1, Auto=2 (only in stop)
    case 101: cmd_type = 'N'; break; // Set Point type, 0-4
    case 102: cmd_type = 'N'; break; // Set Point Threshold
    case 103: cmd_type = 'N'; break; // Set Point Delay
    case 104: cmd_type = 'L'; break; // Set Pointsignal activation type
    case 105: cmd_type = 'N'; break; // Set Point hysteresis
    case 106: cmd_type = 'L'; break; // Water Cooling
    case 107:
      cmd_type = 'L';
      CmdRestrictions = CR_write_in_stop;
      break; // Active Stop (only in stop)
    case 108: cmd_type = 'N'; break; // Baud Rate
    case 109: cmd_type = 'L'; break; // Pump life/cycle time/cycle number reset
    case 110: cmd_type = 'L'; break; // Interlock type
    case 111: cmd_type = 'L'; break; // Analog output type
    case 117: cmd_type = 'N'; break; // Low speed freq setting
    case 120: cmd_type = 'N'; break; // Rotational frequency setting
    case 121: cmd_type = 'N'; break; // Maximum Rotational frequency
    case 122: cmd_type = 'L'; break; // Set vent valve on/off
    case 125: cmd_type = 'L'; break; // Set vent valve operation
    case 126: cmd_type = 'N'; break; // Vent valve opening delay
    case 167: cmd_type = 'L'; break; // Stop speed reading
    case 200: cmd_type = 'N'; break; // Pump current in mA dc
    case 201: cmd_type = 'N'; break; // Pump voltage in Vdc
    case 202: cmd_type = 'N'; break; // Pump power in W
    case 203: cmd_type = 'N'; break; // Driving freq in Hz
    case 204: cmd_type = 'N'; break; // Pump temperature in C
    case 205: cmd_type = 'N'; break; // Pump status
    case 206: cmd_type = 'N'; break; // Error Code
    case 210:
      cmd_type = 'N';
      CmdRestrictions = CR_read_in_start;
      break; // Actual rotation speed in Hz
    case 300: cmd_type = 'N'; break; // Cycle time in minutes
    case 301: cmd_type = 'N'; break; // Cycle number
    case 302: cmd_type = 'N'; break; // Pump life in hours
    case 400: cmd_type = 'A'; break; // Firmware CRC
    case 402: cmd_type = 'A'; break; // CRC Parameter
    case 404: cmd_type = 'A'; break; // CRC Parameter structure
    case 470: cmd_type = 'A'; break; // Date stamp
    case 503: cmd_type = 'N'; break; // RS485 address
    case 504: cmd_type = 'L'; break; // Serial type select
    case 708: cmd_type = 'A'; break; // Date setting
    case 709: cmd_type = 'A'; break; // Time setting
    default:
      nl_error(2, "Invalid window: %d", window);
      return true;
  }
  // nl_error(MSG_DBG(2), "command_request::init #1");
  int nb_data = 0;
  if (!read) {
    int nc;
    switch (cmd_type) {
      case 'L':
        nc = strlen((const char *)data); 
        if (nc != 1) {
          nl_error(2, "Invalid data length %d for logical command %d", nc, window);
          return true;
        }
        switch (data[0]) {
          case '0':
          case '1':
            req_buf[6] = data[0];
            nb_data = 1;
            break;
          default:
            nl_error(2, "Invalid data for logical window %d", window);
            return true;
        }
        break;
      case 'N':
        if (strlen((const char *)data) != 6) {
          nl_error(2, "Invalid data length for numeric command %d", window);
          return true;
        }
        strcpy((char *)&req_buf[6], (const char *)data);
        nb_data = 6;
        break;
      case 'A':
        nc = strlen((const char *)data);
        if (nc > 14) {
          nl_error(2, "Alpha data for command %d too long (%d)", window, nc);
          return true;
        }
        strcpy((char *)&req_buf[6], (const char *)data);
        nb_data = nc;
        break;
      default:
        nl_error(4, "Invalid cmd_type in command_request::init");
    }
  }
  // nl_error(MSG_DBG(2), "command_request::init #2");
  if (drive < 0 || drive >= N_TWISTORR_DRIVES) {
    nl_error(2, "Drive number %d out of range", drive);
    return true;
  }
  // nl_error(MSG_DBG(2), "command_request::init #3");
  this->drive = drive;
  this->device = TwisTorr::TT_DevNo[drive];
  this->window = window;
  this->read = read;
  req_buf[0] = 0x02;
  req_buf[1] = 0x80 + device;
  // nl_error(MSG_DBG(2), "command_request::init #4");
  sprintf((char *)&req_buf[2], "%03d", window);
  // nl_error(MSG_DBG(2), "command_request::init #5");
  req_buf[5] = read ? '0' : '1';
  // Data is already in req_buf[6+]
  int nb = 6+nb_data;
  // nl_error(MSG_DBG(2), "command_request::init #5a nb=%d", nb);
  req_buf[nb++] = 0x03;
  uint8_t crc = 0;
  // nl_error(MSG_DBG(2), "command_request::init #6");
  for (int i = 1; i < nb; ++i) {
    crc ^= req_buf[i];
  }
  // nl_error(MSG_DBG(2), "command_request::init #7 nb=%d crc=%02X", nb, crc);
  for (int i = 0; i <= 1; ++i) {
    uint8_t c = crc & 0xF;
    crc >>= 4;
    if (c < 10) {
      c += '0';
    } else {
      c += 'A' - 10;
    }
    req_buf[nb+1-i] = c;
  }
  // nl_error(MSG_DBG(2), "command_request::init #8");
  nb += 2;
  req_buf[nb] = '\0';
  // nl_error(MSG_DBG(2), "command_request::init #9");
  req_sz = nb;
  rep_sz = 6; // This can be improved
  if (CmdRestrictions != CR_none) {
    nl_error(MSG_DBG(2), "CR::init drive:%d window:%d restricted: %d",
      drive, window, CmdRestrictions);
  }
  return false;
}

// TT_rep_ok, TT_rep_incomplete, TT_rep_error
TT_rep_status_t command_request::process_reply(uint8_t *rep, unsigned nb) {
  error_msg = 0;
  if (nb < 6) return TT_rep_incomplete;
  if (rep[0] != 0x02) {
    error_msg = "No STX";
    return TT_rep_error;
  }
  if (rep[1] != req_buf[1]) {
    error_msg = "reply addresses mismatch";
    return TT_rep_error;
  }
  unsigned i;
  for (i = 2; i < nb && rep[i] != 0x03; ++i);
  if (i+3 > nb) return TT_rep_incomplete;
  unsigned nd = i+1; // nd is number of characters not counting crc
  uint8_t crc = 0;
  for (i = 1; i < nd; ++i) {
    crc ^= rep[i];
  }
  uint8_t crc_recd = 0;
  for (i = 0; i < 2; ++i) {
    uint8_t nibble;
    uint8_t c = rep[nd+i];
    if (isdigit(c)) {
      nibble = c-'0';
    } else if (isxdigit(c)) {
      if (isupper(c)) {
        nibble = c + 10 - 'A';
      } else {
        nibble = c + 10 - 'a';
      }
    } else {
      error_msg = "invalid crc char";
      return TT_rep_error;
    }
    crc_recd = (crc_recd << 4) | nibble;
  }
  if (crc != crc_recd) {
    error_msg = "invalid crc";
    return TT_rep_error;
  }
  // OK, now we have a properly formatted reply.
  // The logic here breaks down in a read operation can produce a one-byte
  // response other than '0' or '1'. It looks like that might be the case
  // for '100' Soft Start, which is type 'A' and can return '2' for Auto.
  if (nd == 4) {
    switch (rep[2]) {
      case 0x06: // ACK
        return TT_rep_ok;
      case 0x15: // NACK
        error_msg = "No acknowledge"; break;
      case 0x32: // Unknown Window
        if (window != 100 || !read)
          error_msg = "Unknown window";
        break;
      case 0x33: // Data Type Error
        error_msg = "Data Type Error"; break;
      case 0x34: // Out of range
        error_msg = "Out of range"; break;
      case 0x35: // Win Disabled
        return TT_rep_win_disabled;
        // error_msg = "Win Disabled"; break;
      case 0x30: // '0' of a logical read
      case 0x31: // '1' of a logical read
        break;
      default:
        error_msg = "Invalid 1-byte response";
        break;
    }
  }
  if (!error_msg && !read)
    error_msg = "Unexpected response to write operation";
  if (error_msg) return TT_rep_error;
  // Now compare the field length to request type
  switch (cmd_type) {
    case 'L':
      if (nd != 8) { // <stx>+<dvc>+###+0+#+<eot>
        error_msg = "Invalid response length for logical";
      } else if (bit_ptr) {
        if (rep[6] == '1') {
          *bit_ptr |= bit_mask;
        } else {
          *bit_ptr = (*bit_ptr) & ~bit_mask;
        }
      } else {
        nl_error(0, "Read %d:%d L %c", device, window, rep[6]);
      }
      break;
    case 'N':
      if (nd != 13) { // <stx>+<dvc>+###+0+######+<eot>
        error_msg = "Invalid response length for numeric";
      } else if (fl_ptr) {
        *fl_ptr = strtof((const char *)&rep[6], NULL);
      } else {
        nl_error(0, "Read %d:%d N %.6s", device, window, &rep[6]);
      }
      break;
    case 'A':
      nl_error(0, "Read %d:%d A '%.*s", device, window, nd-6, &rep[6]);
      break;
  }
  if (error_msg) return TT_rep_error;
  return TT_rep_ok;
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

void command_request::set_fl_ptr(float *ptr) {
  if (cmd_type != 'N') {
    nl_error(2, "Invalid cmd_type for fl_ptr: %d:%d:%c",
      device, window, cmd_type);
  } else {
    fl_ptr = ptr;
    bit_ptr = 0;
  }
}

void command_request::set_bit_ptr(uint8_t *ptr, uint8_t mask) {
  if (cmd_type != 'L') {
    nl_error(2, "Invalid cmd_type for bit_ptr: %d:%d:%c",
      device, window, cmd_type);
  } else {
    bit_ptr = ptr;
    bit_mask = mask;
    fl_ptr = 0;
  }
}

void command_request::default_read_action() {
  switch (cmd_type) {
    case 'N':
      if (fl_ptr) {
        *fl_ptr = 0.;
      }
      break;
    default:
      break;
  }
}
