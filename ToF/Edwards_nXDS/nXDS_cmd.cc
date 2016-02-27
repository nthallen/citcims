/*
 * nXDS_cmd.cc
 */
#include "nXDS.h"
#include "nortlib.h"
#include "nl_assert.h"

nXDS_cmd::nXDS_cmd(nXDS *nX_in)
    : Ser_Sel(tm_dev_name("cmd/nXDS"), O_RDONLY, 40) {
  nX = nX_in;
}

nXDS_cmd::~nXDS_cmd() {}

/**
 * Command format: \d+:\d+[:\d+]
 */
int nXDS_cmd::ProcessData(int flag) {
  if (flag & Selector::Sel_Read) {
    int drive, addr, value = 0;
    fillbuf();
    if (nc == 0) return 1;
    cp = 0;
    if (not_int(drive) ||
        not_str(":") ||
        not_int(addr) ||
        not_str(":") ||
        not_int(value)) {
      if (cp >= nc)
        report_err("Expected drive:addr:value");
    } else {
      switch (addr) {
        case 802:
        case 803:
        case 805:
          { command_request *cr = nX->new_command_req();
            if (cr->init(drive, 'C', addr, false, value)) {
              nX->free_command(cr);
            } else {
              nX->enqueue_command(cr);
            }
          }
          break;
        default:
          nl_error(1, "Invalid command address: %d", addr);
      }
    }
    consume(nc);
  }
  return 0;
}

void nXDS::enqueue_poll(uint8_t drive, uint8_t qualifier, uint16_t address) {
  nl_assert(drive < N_NXDS_DRIVES);
  command_request *cr;
  cr = new_command_req();
  if (cr->init(drive, qualifier, address, true)) {
    free_command(cr);
  } else {
    enqueue_poll(cr);
  }
}

void nXDS::enqueue_request(uint8_t drive, uint8_t qualifier, uint16_t address,
        bool read, uint16_t value) {
  command_request *cr = new_command_req();
  if (cr->init(drive, qualifier, address, read, value)) {
    free_command(cr);
  } else {
    enqueue_command(cr);
  }
}
