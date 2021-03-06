#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#include "msg.h"
#include "nortlib.h"
#include "nl_assert.h"
#include "oui.h"
#include "UP_int.h"


int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { Selector S;
    UserPkts Pkts(&S); // constructor generated
    Cmd_Selectee CS;
    S.add_child(&CS);
    nl_error(0, "Starting: V3.0");
    S.event_loop();
  }
  nl_error(0, "Terminating");
}

UserPkt::UserPkt(const char *KW_in) {
  KW = KW_in;
  TM_id = 0;
  n_errors = 0;
  n_suppressed = 0;
  total_errors = 0;
  total_suppressed = 0;
  buf = 0;
  nc = 0;
  cp = 0;
}

UserPkt::~UserPkt() {
  if (TM_id) {
    Col_send_reset(TM_id);
    TM_id = 0;
  }
}

void UserPkt::TM_init(void *data, unsigned short n_bytes) {
  memset(data, 0, n_bytes);
  TM_id = Col_send_init( KW, data, n_bytes, 0);
}

int UserPkt::Process_Pkt(unsigned char *s, unsigned nc_in, unsigned cp_in) {
  buf = s;
  nc = nc_in;
  cp = cp_in;
  if (Process_Pkt())
    return 1;
  Col_send(TM_id);
  return 0;
}

#define QERR_THRESHOLD 5
/**
 * Reports the error message, provided the qualified error count
 * is not above the limit. report_ok() will decrement the qualified
 * error count. It is assumed that all messages are of severity
 * MSG_ERR. Messages at other levels, either more or less severe,
 * should be sent directly to msg().
 */
void UserPkt::report_err( const char *fmt, ... ) {
  ++total_errors;
  if ( n_errors < QERR_THRESHOLD )
    ++n_errors;
  if ( n_suppressed == 0 && n_errors < QERR_THRESHOLD ) {
    va_list args;

    va_start(args, fmt);
    msgv(2, fmt, args );
    va_end(args);
    if (nc)
      msg(2, "%s Input was: '%s'", KW, ascii_escape((char*)buf, nc) );
  } else {
    if ( !n_suppressed )
      msg(2, "%s Error threshold reached: suppressing errors", KW);
    ++n_suppressed;
    ++total_suppressed;
  }
}

/**
 * Indicate that data has successfully been received.
 */
void UserPkt::report_ok() {
  if ( n_errors > 0 ) {
    if ( --n_errors <= 0 && n_suppressed ) {
      msg( 0, "%s Error recovery: %d error messages suppressed",
        KW, n_suppressed );
      n_suppressed = 0;
    }
  }
}

int UserPkt::not_ndigits(int n, int &value) {
  int i = 0;
  value = 0;
  while ( i < n && cp < nc && isdigit(buf[cp])) {
    value = value*10 + buf[cp++] - '0';
    ++i;
  }
  if (i < n) {
    report_err("%s Expected %d digits at column %d", KW, n, cp-i);
    return 1;
  }
  return 0;
}

int UserPkt::not_str(const char *str_in, unsigned int len) {
  unsigned int start_cp = cp;
  unsigned int i;
  const unsigned char *str = (const unsigned char *)str_in;
  if (cp < 0 || cp > nc || nc < 0 || buf == 0)
    nl_error(4, "%s UserPkt::not_str precondition failed: "
      "cp = %d, nc = %d, buf %s", KW, cp, nc,
      buf ? "not NULL" : "is NULL");
  for (i = 0; i < len; ++i) {
    if (str[i] != buf[start_cp+i]) {
      report_err("%s Expected string '%s' at column %d",
        KW, ascii_escape(str_in, len), start_cp);
      return 1;
    }
    ++cp;
  }
  return 0;
}

int UserPkt::not_fptext() {
  if ( cp < 0 || cp > nc || nc < 0 || buf == 0 )
    msg( MSG_EXIT_ABNORM, "Ser_Sel precondition failed: "
      "cp = %d, nc = %d, buf %s",
      cp, nc, buf ? "not NULL" : "is NULL" );

  if (cp >= nc) return true;
  if (buf[cp] == '-') {
    if (++cp >= nc) return true;
  }
  if (buf[cp] == '.') {
    if (++cp >= nc) return true;
    if (isdigit(buf[cp])) {
      do { ++cp; }
        while (cp < nc && isdigit(buf[cp]));
    } else {
      return true;
    }
  } else if (isdigit(buf[cp])) {
    do { ++cp; }
      while (cp < nc && isdigit(buf[cp]));
    if (cp < nc && buf[cp] == '.') {
      do { ++cp; }
        while (cp < nc && isdigit(buf[cp]));
    }
  } else if (cp < nc && tolower(buf[cp]) == 'n') {
    if (++cp >= nc || tolower(buf[cp]) != 'a' ||
        ++cp >= nc || tolower(buf[cp]) != 'n') {
      if (cp < nc) {
        report_err("no_fptext() expected 'nan' at col %d", cp);
      }
      return true;
    }
    ++cp;
    return false;
  } else {
    report_err("not_fptext() expected [0-9.] at col %d", cp);
    return true;
  }
  if (cp < nc && tolower(buf[cp]) == 'e') {
    if (++cp >= nc) return true;
    if (buf[cp] == '+' || buf[cp] == '-') {
      if (++cp >= nc) return true;
    }
    if (isdigit(buf[cp])) {
      do { ++cp; } while (cp < nc && isdigit(buf[cp]));
    } else {
      report_err("not_fptext() expected digits at col %d", cp);
      return true;
    }
  }
  return false;
}

int UserPkt::not_double( double *value ) {
  char *endptr;
  int start_cp = cp;
  int ncf;
  if (not_fptext()) return true;
  *value = strtod( (char*)&buf[start_cp], &endptr );
  if (endptr == (char *)&buf[cp]) {
    return false;
  }
  ncf = endptr - (char *)buf;
  report_err("strtof at col %d ended at col %d, not %d",
    start_cp, ncf, cp);
  return true;
}


int UserPkt::not_float( float *value ) {
  double dval;
  int rv = not_double(&dval);
  *value = dval;
  return rv;
}

int UserPkt::not_ISO8601(double *Time, bool w_hyphens) {
  struct tm buft;
  float secs;
  time_t ltime;

  if (not_ndigits(4, buft.tm_year) ||
      (w_hyphens && not_str("-",1)) ||
      not_ndigits(2, buft.tm_mon) ||
      (w_hyphens && not_str("-",1)) ||
      not_ndigits(2, buft.tm_mday) ||
      not_str("T", 1) ||
      not_ndigits(2, buft.tm_hour) ||
      not_str(":",1) ||
      not_ndigits(2, buft.tm_min) ||
      not_str(":",1) ||
      not_float(&secs))
    return 1;
  buft.tm_year -= 1900;
  buft.tm_mon -= 1;
  buft.tm_sec = 0;
  ltime = mktime(&buft);
  if (ltime == (time_t)(-1))
    report_err("%s mktime returned error", KW);
  else *Time = ltime + secs;
  return 0;
}

/**
 * accept a float or return a NaN (99999.)
 * if the next char is a comma or CR
 */
int UserPkt::not_nfloat(float *value, float NaNval) {
  float val;
  while (cp < nc && buf[cp] == ' ') ++cp;
  if (cp >= nc) return 1;
  if (buf[cp] == ',' || buf[cp] == '\r' || buf[cp] == '\n') {
    *value = NaNval;
    return 0;
  }
  if (strnicmp((const char *)&buf[cp], "NaN", 3) == 0) {
    cp += 3;
    *value = NaNval;
    return 0;
  }
  if (not_float(&val)) return 1;
  *value = val;
  return 0;
}

int UserPkt::not_uchar(unsigned char &val) {
  int sval;
  if (not_int(sval)) return 1;
  if (sval < 0 || sval > 255) {
    report_err("%s uchar value out of range: %d", KW, sval);
    return 1;
  }
  val = sval;
  return 0;
}

int UserPkt::not_int(int &val) {
  bool negative = false;
  // fillbuf() guarantees the buffer will be NUL-terminated, so any check
  // that will fail on a NUL is OK without checking the cp < nc
  while (isspace(buf[cp]))
    ++cp;
  if (buf[cp] == '-') {
    negative = true;
    ++cp;
  } else if (buf[cp] == '+') ++cp;
  if ( isdigit(buf[cp]) ) {
    val = buf[cp++] - '0';
    while ( isdigit(buf[cp]) ) {
      val = 10*val + buf[cp++] - '0';
    }
    if (negative) val = -val;
    return 0;
  } else {
    report_err( "%s Expected int at column %d", KW, cp );
    return 1;
  }
}

// UserPkts::UserPkts() generated

UserPkts::~UserPkts() {
  while (!UDPs.empty()) {
    UserPkts_UDP *udp = UDPs.back();
    udp->Stor->delete_child(udp->fd);
    UDPs.pop_back();
  }
}

UserPkts_UDP::UserPkts_UDP(int udp_port) : Ser_Sel( 0, 0, 600 ) {
  Bind(udp_port);
  flags = Selector::Sel_Read;
  flush_input();
  setenv("TZ", "UTC0", 1); // Force UTC for mktime()
}

int UserPkts_UDP::ProcessData(int flag) {
  char KW[30];
  int rv;
  std::vector<UserPkt *>::const_iterator cur_pkt;
  if (fillbuf()) return 1;
  if (not_KW(&KW[0])) {
    nc = cp = 0;
    return 0;
  }
  for (cur_pkt = Pkts.begin(); cur_pkt != Pkts.end(); ++cur_pkt) {
    UserPkt * const pkt = *cur_pkt;
    if (strcmp(KW,pkt->KW) == 0) {
      rv = pkt->Process_Pkt(buf, nc, cp);
      if (rv) {
        nc = cp = 0;
      } else {
        consume(nc);
        report_ok();
      }
      return 0;
    }
  }
  nc = cp = 0;
  
  // Could add code here to report on unrecognized KW values
  return 0;
}

int UserPkts_UDP::not_KW(char *KWbuf) {
  int KWi = 0;
  while (cp < nc && isspace(buf[cp]))
    ++cp;
  while (cp < nc && KWi < 30 && !isspace(buf[cp]) &&
         buf[cp] != ',') {
    KWbuf[KWi++] = buf[cp++];  
  }
  if (KWi >= 30) {
    report_err("Keyword overflow");
    return 1;
  } else if (buf[cp] == ',') {
    KWbuf[KWi] = '\0';
    ++cp;
    return 0;
  } else {
    report_err("Unexpected char in not_KW");
    return 1;
  }
}

void UserPkts_UDP::Bind(int port) {
  char service[10];
  struct addrinfo hints,*results, *p;
  int err, ioflags;

  if (port == 0)
    nl_error( 3, "Invalid port in UserPkts_UDP: 0" );
  snprintf(service, 10, "%d", port);

  memset(&hints, 0, sizeof(hints));	
  hints.ai_family = AF_UNSPEC;		// don't care IPv4 of v6
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;
    
  err = getaddrinfo(NULL, 
                    service,
                    &hints,
                    &results);
  if (err)
    nl_error( 3, "UserPkts_UDP::Bind: getaddrinfo error: %s",
          gai_strerror(err) );
  for(p=results; p!= NULL; p=p->ai_next) {
    fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (fd < 0)
      nl_error( 2, "IWG1_UPD::Bind: socket error: %s", strerror(errno) );
    else if ( bind(fd, p->ai_addr, p->ai_addrlen) < 0 )
      nl_error( 2, "UserPkts_UDP::Bind: bind error: %s", strerror(errno) );
    else break;
  }
  if (fd < 0)
    nl_error(3, "Unable to bind UDP socket");
    
  ioflags = fcntl(fd, F_GETFL, 0);
  if (ioflags != -1)
    ioflags = fcntl(fd, F_SETFL, ioflags | O_NONBLOCK);
  if (ioflags == -1)
    nl_error( 3, "Error setting O_NONBLOCK on UDP socket: %s",
      strerror(errno));
}

int UserPkts_UDP::fillbuf() {
  struct sockaddr_storage from;
  socklen_t fromlen = sizeof(from);
  int rv = recvfrom(fd, &buf[nc], bufsize - nc - 1, 0,
              (struct sockaddr*)&from, &fromlen);
	
  if (rv == -1) {
    if ( errno == EWOULDBLOCK ) {
      ++n_eagain;
    } else if (errno == EINTR) {
      ++n_eintr;
    } else {
      nl_error( 2, "UserPkts_UDP::fillbuf: recvfrom error: %s",
                strerror(errno));
      return 1;
    }
    return 0;
  }
  nc += rv;
  buf[nc] = '\0';
  return 0;
}
