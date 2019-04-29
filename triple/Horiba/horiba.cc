#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include "horiba_int.h"
#include "oui.h"
#include "nortlib.h"
#include "nl_assert.h"

const char *horiba_path = "/net/athenaII_a/dev/ser3";
const char *horiba_name = "Horiba";
int horiba_channels = 4;
int opt_echo = 1;

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  nl_error( 0, "Starting V14.1" );
  { Selector S;
    HoribaCmd HC;
    horiba_tm_t TMdata;
    HoribaSer Hrba(horiba_path, &TMdata, &HC);
    TM_Selectee TM(horiba_name, &TMdata, sizeof(TMdata));
    S.add_child(&HC);
    S.add_child(&Hrba);
    S.add_child(&TM);
    S.event_loop();
  }
  nl_error( 0, "Terminating" );
}

HoribaQuery::HoribaQuery() {
  result = 0;
  // scale = 1.0;
  mask = 0;
}

void HoribaQuery::format(unsigned short addr, float *resultp,
        unsigned short smask, unsigned char sunit, const char *cmd, ...) {
  char buf[30];
  int nc, bcc, i;
  va_list arg;

  result = resultp;
  mask = smask;
  unit = sunit;
  query.clear();
  nc = snprintf(&buf[0], 20, "@%02d%c", addr, 2); // STX
  nl_assert(nc < 20);
  query.append(&buf[0], nc);
  va_start(arg, cmd);
  nc = vsnprintf(&buf[0], 20, cmd, arg);
  nl_assert(nc < 20);
  va_end(arg);
  buf[nc++] = 3; // ETX
  bcc = 0;
  for (i = 0; i < nc; ++i)
    bcc += buf[i];
  bcc &= 0x7F;
  buf[nc++] = bcc;
  query.append(&buf[0], nc);
  if (bcc == '@')
    query.append("\003\003\003", 3);
  else if (bcc == '*' || bcc == '.')
    query.append("\003\003\003\003\003\003\003\003\003", 9);
  nl_error(-2, "Query formatted: '%s'", ascii_escape(query));
}

/**
 * Will inherit from Ser_Sel although not a serial interface per se. I
 * just want access to all the parsing and error reporting functions.
 * I won't call setup(), which is the only device-specific function.
 */
HoribaCmd::HoribaCmd() : Ser_Sel() {
  char shortname[40];
  int nc;
  nc = snprintf(shortname, 40, "cmd/%s", horiba_name);
  if (nc >= 40) {
    nl_error(3, "Specified name '%s' is too long", horiba_name);
  }
  init( tm_dev_name(shortname), O_RDONLY|O_NONBLOCK, 50 );
}

HoribaCmd::~HoribaCmd() {
}

/**
 * Process commands from command server:
 * W\d:\d+[\.\d+]\n
 * Q\n
 * "" same as quit command
 * For W commands, convert to a proper Horiba query, save and set_gflag(1).
 * The only flag we are sensitive to is the command read.
 */
int HoribaCmd::ProcessData(int flag) {
  nc = cp = 0;
  int addr;
  float value;
  if (fillbuf()) return 1;
  if (nc == 0 || buf[0] == 'Q') return 1;
  if (not_str("W", 1) ||
      not_int(addr) ||
      not_str(":", 1) ||
      not_float(value) ||
      not_str("\n", 1) ) {
    return 0;
  }
  if (addr < 1 || addr > horiba_channels) {
    report_err("Invalid address %d in HoribaCmd", addr);
    return 0;
  }
  HCquery.format( addr, 0, HORIBA_CMD_S << (addr-1), 'B', "AFC%.2lf,B", value );
  flags = 0; // Don't listen for more commands
  Stor->set_gflag(1);
  report_ok();
  consume(cp);
  return 0;
}

HoribaQuery *HoribaCmd::query() {
  if ( flags ) {
    nl_error( 2, "HoribaCmd::query() called when flags != 0" );
    return NULL;
  }
  // flags = Selector::Sel_Read; // listen again
  return &HCquery;
}

void HoribaCmd::query_complete() {
  flags = Selector::Sel_Read; // listen again
}

/* Buf Size arbitrarily set to 50 for now */
HoribaSer::HoribaSer(const char *ser_dev, horiba_tm_t *data, HoribaCmd *HCmd)
  : Ser_Sel( ser_dev, O_RDWR|O_NONBLOCK, 100 ) {
  Cmd = HCmd;
  setup(38400, 7, 'o', 1, 45, 1 ); // Let's go with the timeout
  flags |= Selector::gflag(0) | Selector::gflag(1) | Selector::Sel_Timeout;
  TMdata = data;
  for (int i = 0; i < HORIBA_MAX_CHANNELS; ++i) {
    TMdata->channel[i].SP = 0.;
    TMdata->channel[i].RB = 0.;
  }
  TMdata->HoribaS = 0;
  // Initialize queries 
  Qlist.resize(horiba_channels*2);
  for (int i = 1; i <= horiba_channels; ++i) {
    Qlist[2*i-2].format(i, &TMdata->channel[i-1].SP, 1<<(2*i-2), 'B', "RFC");
    Qlist[2*i-1].format(i, &TMdata->channel[i-1].RB, 1<<(2*i-1), 'B', "RFV");
  }
  CurQuery = 0;
  nq = qn = 0;
  cmdq = 0;
  state = HS_Idle;
  do {
    nc = cp = 0;
  } while (fillbuf() == 0 && nc > 0);
  cur_min = 1;
  init_termios();
}

HoribaSer::~HoribaSer() {
}

int HoribaSer::ProcessData(int flag) {
  int nbw;
  if (flag & Selector::gflag(0)) { // TM
    TMdata->HoribaS = 0;
    nq = Qlist.size();
  }
  if (flag & Selector::gflag(1)) { // Command Received
    cmdq = 1;
  }
  if (flag & (Selector::Sel_Read | Selector::Sel_Timeout)) {
    switch (parse_response()) {
      case HP_Die: return 1;
      case HP_Wait:
        if (TO.Expired()) {
          report_err("Timeout: Query was: '%s'",
            ascii_escape(CurQuery->query));
          break;
        } else {
          update_termios();
          return 0;
        }
      case HP_OK:
        break;
      default:
        nl_error(4, "Invalid return code from parse_response()");
    }
    if (CurQuery) {
      if (CurQuery->result) {
        if (++qn == Qlist.size())
          qn = 0;
        --nq;
      } else {
        Cmd->query_complete();
      }
      CurQuery = 0;
    }
  }
  if (CurQuery) {
    update_termios();
    return 0;
  }
  if (cmdq) {
    CurQuery = Cmd->query();
    cmdq = 0;
  }
  if ((CurQuery == 0) && nq) {
    CurQuery = &Qlist[qn];
  }
  if (CurQuery == 0) {
    state = HS_Idle;
    TO.Clear();
    update_termios();
    return 0;
  }
  nbw = write(fd, CurQuery->query.c_str(), CurQuery->query.length());
  nc = cp = 0; // flush input buffer
  if (nbw == -1) {
    nl_error(2, "Error on write to device: %s", strerror(errno));
    return 1; // terminate
  } else if ((unsigned)nbw != CurQuery->query.length()) {
    report_err("Incomplete write: expected %d, wrote %d",
      CurQuery->query.length(), nbw);
  }
  if (CurQuery->result) {
    TO.Set(0, 70);
  } else {
    // nl_error(-2, "Set command timeout");
    TO.Set(1, 0);
  }
  state = HS_WaitResp;
  cur_min = opt_echo ? CurQuery->query.length()+5 : 5;
  update_termios();
  return 0;
}

/**
 * Search for string in the input, discarding
 * characters from the front of the buffer as
 * necessary. The string is assumed to begin with
 * a unique synch character ('@') not located
 * elsewhere in the string, so we can
 * search forward from the first unmatched
 * character in the input buffer.
 * @param str The string
 * @return 0 if entire string is found, 1 if the end of input is
 *   reached without matching the string. If a partial match is
 *   found, cp will point to the beginning of the partial match
 */
int HoribaSer::str_not_found(const char *str_in, int len) {
  unsigned int start_cp = cp;
  const unsigned char *str = (const unsigned char *)str_in;
  int i = 0;
  while (i < len && cp < nc) {
    while (cp < nc && buf[cp] != str[0])
      ++cp;
    if (cp < nc) {
      start_cp = cp++;
      for (i = 1; i < len && cp < nc; ++i) {
        if (str[i] != buf[cp])
          break;
        ++cp;
      }
    }
  }
  cur_min = len+5-i;
  if (i >= len) {
    if (start_cp > 0) {
      nl_error(2, "Unexpected input '%s' before string ...",
        ascii_escape((const char *)buf, start_cp));
      nl_error(2, "... Found expected '%s'",
        ascii_escape(ascii_escape(str_in, len)));
      consume(start_cp);
      cp = i;
    }
    return 0;
  } else return 1;
}

/**
 * @return HP_OK means we are done with this query, good or bad.
 *   HP_Wait means we have not received what we're looking for.
 *   HP_Die means a serious error occurred and the driver should terminate.
 */
HoribaSer::Horiba_Parse_Resp HoribaSer::parse_response() {
  cp = 0;
  if (fillbuf()) return HP_Die; // Die on read error
  if (CurQuery == 0) {
    report_err("Unexpected input");
    consume(nc);
    return HP_OK;
  }
  if (opt_echo &&
      str_not_found(CurQuery->query.c_str(), CurQuery->query.length())) {
    return HP_Wait;
  }
  // I expect either ACK for a command response or
  // STX <float>,[A-Z] ETX BCC for a value request
  // NACK for error
  if (cp < nc && buf[cp] == 21) {
    report_err( "NAK on %s response: Query was: '%s'",
      CurQuery->result ? "Data" : "Command",
      ascii_escape(CurQuery->query));
    consume(nc);
    return HP_OK;
  }
  if (CurQuery->result) {
    float val;
    unsigned int cp0 = cp, cp1;
    if (not_str("\002", 1) || not_float(val)) {
      if (cp < nc) {
        consume(nc);
        return HP_OK;
      }
      cur_min -= cp - cp0;
      return HP_Wait;
    }
    cur_min = 1;
    if (cp+1 < nc && buf[cp] == ',' && buf[cp+1] >= 'A' &&
        buf[cp+1] <= 'Z') {
      if (CurQuery->unit != buf[cp+1]) {
        nl_error(2, "Unexpected unit '%c'", buf[cp+1]);
        CurQuery->unit = buf[cp+1];
      }
      cp += 2;
    }
    if (not_str("\003", 1)) {
      if (cp < nc) {
        consume(nc);
        return HP_OK;
      }
      return HP_Wait;
    }
    cp1 = cp;
    if (not_etx()) {
      return((cp < nc) ? HP_OK : HP_Wait);
    }
    if (bcc_ok(cp0, cp1)) {
      *(CurQuery->result) = val;
      TMdata->HoribaS |= CurQuery->mask;
      report_ok();
      consume(cp);
    }
  } else {
    unsigned int cp0 = cp, cp1;
    if (not_str("\002OK\003",4)) {
      if (cp < nc) {
        consume(nc);
        return HP_OK;
      }
      cur_min -= cp-cp0;
      return HP_Wait;
    }
    cur_min = 1;
    cp1 = cp;
    if (not_etx()) {
      return((cp < nc) ? HP_OK : HP_Wait);
    }
    if (bcc_ok(cp0, cp1)) {
      TMdata->HoribaS |= CurQuery->mask;
      report_ok();
      consume(cp);
    }
  }
  return HP_OK;
}

/**
 * On entry, cp is positioned just after the ETX character, so
 * if cp < nc, then buf[cp] is the BCC character.
 *
 * @return non-zero unless all the necessary ETX chars are present
 */
int HoribaSer::not_etx() {
  if (cp >= nc) return 1;
  unsigned int bcc = buf[cp++];
  int extra_etx = 0;
  if (bcc == '@') extra_etx = 3;
  else if ( bcc == '*' || bcc == '.') extra_etx = 9;
  while (extra_etx > 0 && cp < nc && buf[cp] == '\003') {
    --extra_etx;
    ++cp;
  }
  if (extra_etx) {
    if (cp < nc) {
      report_err("Missing one or more trailing ETX");
      consume(cp);
    } else cur_min = extra_etx;
    return 1;
  }
  return 0;
}

/**
 * @param from points to STX char in buf[]
 * @param to points to the BCC character immediately following the ETX (\033)
 *
 * Because the message has already been syntactically checked via not_etx(),
 * we can be confident that to < nc, but we do double-check that at the
 * beginning just to be sure.
 *
 * @return non-zero if a valid bcc code is found.
 */
int HoribaSer::bcc_ok(unsigned int from, unsigned int to) {
  unsigned int bcc = 0, i;
  if (from >= to || buf[from] != '\002' || buf[to-1] != '\003' || to >= nc) {
    report_err("bcc_ok(%d-%d) does not meet preconditions", from, to);
    return 0;
  }
  for (i = from+1; i < to; ++i)
    bcc = (bcc + buf[i]) & 0x7F;
  if ((unsigned)buf[to] != bcc) {
    report_err("BCC mismatch on response: Rec'd: %d Calc'd: %d",
            (unsigned)buf[to], bcc);
    consume(nc);
    return 0;
  }
  return 1;
}

Timeout *HoribaSer::GetTimeout() {
  return state == HS_Idle ? 0 : &TO;
}

void HoribaSer::init_termios() {
  if (tcgetattr(fd, &termios_s)) {
    nl_error(2, "Error from tcgetattr: %s", strerror(errno));
  }
}

/**
 * Adapted from TwisTorr. Adjusts the VMIN termios value
 * based on the specific command. This version is incomplete.
 * It adjusts for the request size so we can skip over the RS485 echo,
 * but it does not anticipate any more than the minimal response
 * of 6 characters. We could add command-specific response size
 * as noted in the comments. We could also adjust the VTIME
 * parameter, but it may be redundant, since we have the overriding
 * Selector timeout working for us.
 */
void HoribaSer::update_termios() {
  if (cur_min < 1) cur_min = 1;
  if (cur_min != termios_s.c_cc[VMIN]) {
    termios_s.c_cc[VMIN] = cur_min;
    if (tcsetattr(fd, TCSANOW, &termios_s)) {
      nl_error(2, "Error from tcsetattr: %s", strerror(errno));
    }
  }
}
