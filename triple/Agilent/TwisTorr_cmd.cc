/*
 * TwisTorr_cmd.cc
 */
#include "Agilent.h"
#include "nortlib.h"

TwisTorr_cmd::TwisTorr_cmd(TwisTorr *TT_in)
    : Ser_Sel(tm_dev_name("cmd/TwisTorr"), O_RDONLY, 40) {
  TT = TT_in;
}

TwisTorr_cmd::~TwisTorr_cmd() {}

int TwisTorr_cmd::ProcessData(int flag) {
  if (flag & Selector::Sel_Read) {
    int device, window;
    fillbuf();
    if (nc == 0) return 1;
    cp = 0;
    switch (buf[0]) {
      case 'R':
        if (not_str("R:") ||
            not_int(device) ||
            not_str(":") ||
            not_int(window)) {
          if (cp >= nc) {
            report_err("Invalid read syntax");
          }
        } else {
          command_request *cr = TT->new_command_req();
          if (cr->init(device, window, true)) {
            TT->free_command(cr);
          } else {
            TT->enqueue_command(cr);
          }
        }
        break;
      case 'W':
        if (not_str("W:") ||
            not_int(device) ||
            not_str(":") ||
            not_int(window) ||
            not_str(":")) {
          if (cp >= nc) {
            report_err("Invalid read syntax");
          }
        } else {
          int i;
          for (i = 0; buf[cp+i] != '\0' && buf[cp+i] != '\r' && buf[cp+i] != '\n'; ++i);
          buf[cp+i] = '\0';
          command_request *cr = TT->new_command_req();
          if (cr->init(device, window, true, &buf[cp])) {
            TT->free_command(cr);
          } else {
            TT->enqueue_command(cr);
          }
        }
        break;
      case 'Q':
        return 1;
      default:
        nl_error(2, "Invalid command syntax: '%s'",
          ascii_esc((const char*)buf));
        break;
    }
    consume(nc);
  }
  return 0;
}

void TwisTorr::enqueue_poll_float(uint8_t device, uint16_t window, float *ptr) {
  command_request *cr;
  cr = new_command_req();
  if (cr->init(device, window, true)) {
    free_command(cr);
  } else {
    cr->set_fl_ptr(ptr);
    enqueue_poll(cr);
  }
}

void TwisTorr::enqueue_poll_bit(uint8_t device, uint16_t window, uint8_t *ptr, uint8_t mask) {
  command_request *cr;
  cr = new_command_req();
  if (cr->init(device, window, true)) {
    free_command(cr);
  } else {
    cr->set_bit_ptr(ptr, mask);
    enqueue_poll(cr);
  }
}
