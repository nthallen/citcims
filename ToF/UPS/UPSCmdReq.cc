/*
 * UPSCmdReq.cc
 * UPS_cmd_req object
 */
#include <string.h>
#include <stdlib.h>
#include "UPS.h"
#include "nortlib.h"

UPS_cmd_req::UPS_cmd_req() {
  active = false;
  persistent = false;
}

/**
 * @return true if command is not valid. Caller should return object to
 * the free queue.
 */
bool UPS_cmd_req::init(const char *cmdquery, UPS_parser parser_in, unsigned reply_min) {
  active = false;
  persistent = false;
  req_sz = snprintf((char *)req_buf, max_cmd_bytes, "%s\r", cmdquery);
  if (req_sz >= max_cmd_bytes) {
    nl_error(2, "cmdquery '%s' exceeds max_cmd_bytes", cmdquery);
    return true;
  }
  parser = parser_in;
  rep_min = reply_min;
  return false;
}

/**
 * Invokes ascii_escape on the request buffer
 */
const char *UPS_cmd_req::ascii_escape() {
  return ::ascii_escape((const char *)req_buf, req_sz);
}

/**
 * Writes the request to the specified file descriptor.
 * @return -1 if write returns anything but req_sz. 0 otherwise.
 */
int UPS_cmd_req::write(int fd) {
  if (nl_debug_level <= MSG_DBG(1)) {
    nl_error(MSG_DBG(1), "Sending: '%s'", ascii_escape());
  }
  int nb = ::write(fd, req_buf, req_sz);
  return (nb != (int)req_sz) ? -1 : 0;
}
