/* UPS_cmd.cc
 */
#include "UPS.h"
#include "nortlib.h"

UPS_cmd::UPS_cmd(UPS_ser *UPSin)
  : Ser_Sel( tm_dev_name("cmd/UPS"), O_RDONLY|O_NONBLOCK, 50 ) {
  UPS = UPSin;
}

UPS_cmd::~UPS_cmd() {}

/**
 * Process commands from command server:
 * X\n
 * "" same as quit command
 * For W commands, convert to a proper Horiba query, save and set_gflag(1).
 * The only flag we are sensitive to is the command read.
    Q0: QPI Protocol ID Inquiry
    Q1: QMD Model inquiry
    Q2: QID UPS ID inquiry
    Q3: QVFW Main CPU Firmware version inquiry
    Q4: QBYV bypass voltage range inquiry
    Q5: QBYF bypass frequency range inquiry
    Q6: QRI UPS Rating Information
    Q7: QFLAG Setting flag status inquiry
    Q8: QHE 
    Q9: QFS Fault status 

Commands to issue:
  Response to all commands is either "(ACK<cr>" or "(NACK<cr>"
    T<n>: Test for specified time
    S<n>: Shutdown in <n> minutes
    S<n>R<m>: Shutdown and restore
    CS: Cancel Shutdown
    CT: Cancel Test
    KN: SKON1: Turn on socket 1: SKON<n>: n=1[,2] (socket 2 not supported)
    KF: SKOFF1: Turn off socket 1: SKOFF<n>: n=1[,2]
 */
int UPS_cmd::ProcessData(int flag) {
  int arg1, arg2;
  nc = cp = 0;
  if (fillbuf()) return 1;
  if (nc == 0 || buf[0] == 'X') return 1;
  switch (buf[cp++]) {
    case 'Q':
      if (!not_int(arg1)) {
        switch (arg1) {
          case 0: UPS->enqueue_query("QPI", 5); break;
          case 1: UPS->enqueue_query("QMD", 47); break;
          case 2: UPS->enqueue_query("QID", 16); break;
          case 3: UPS->enqueue_query("QVFW", 19); break;
          case 4: UPS->enqueue_query("QBYV", 10); break;
          case 5: UPS->enqueue_query("QBYF", 11); break;
          case 6: UPS->enqueue_query("QRI", 22); break;
          case 7: UPS->enqueue_query("QFLAG", 19); break;
          case 8: UPS->enqueue_query("QHE", 9); break;
          case 9: UPS->enqueue_query("QFS", 3); break;
          default:
            nl_error(2, "Invalid query code: %d", arg1);
        }
        return 0;
      }
      break; // Fall through to error
    case 'T':
      if (cp+1 < nc && buf[cp] == '.') {
	if (!isdigit(buf[++cp])) break;
	++cp;
      } else {
	if (not_int(arg1)) break;
      }
      buf[cp] = '\0';
      UPS->enqueue_command((const char *)buf);
      return 0;
    case 'S':
      if (not_int(arg1)) break;
      if (cp < nc && buf[cp] == 'R') {
        ++cp;
        if (not_int(arg2)) break;
      }
      buf[cp] = '\0';
      UPS->enqueue_command((const char *)buf);
      return 0;
    case 'C':
      if (cp < nc) {
        switch (buf[cp]) {
          case 'S':
          case 'T':
            buf[++cp] = '\0';
            UPS->enqueue_command((const char *)buf);
            return 0;
          default:
            break;
        }
      }
      break;
    case 'K':
      if (cp < nc) {
        switch (buf[cp]) {
          case 'N':
            UPS->enqueue_command("SKON1");
            return 0;
          case 'F':
            UPS->enqueue_command("SKOFF1");
            return 0;
          default:
            break;
        }
      }
      break;
    default:
      break;
  }
  nl_error(2,"Invalid command: '%s'", ascii_escape((const char *)buf));
  return 0;
}
