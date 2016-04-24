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
#include "UserPkts2_int.h"

#define MAX_UDP_PORTS 10
static int udp_ports[MAX_UDP_PORTS];
static int n_udp_ports = 0;

void pkts_init_options(int argc, char **argv) {
  int c;

  optind = OPTIND_RESET; /* start from the beginning */
  opterr = 0; /* disable default error message */
  while ((c = getopt(argc, argv, opt_string)) != -1) {
    switch (c) {
      case 'p':
        if (n_udp_ports >= MAX_UDP_PORTS) {
          nl_error(3, "Too many UDP ports specified");
        }
        udp_ports[n_udp_ports++] = atoi(optarg);
        break;
      case '?':
        nl_error(3, "Unrecognized Option -%c", optopt);
    }
  }
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { Selector S;
    UserPkts Pkts; // Sets up the TM connections
    std::vector<UserPkts_UDP*> UDPs;
    for (int i = 0; i < n_udp_ports; ++i) {
      UserPkts_UDP *UP = new UserPkts_UDP(udp_ports[i], &Pkts);
      S.add_child(UP);
      UDPs.push_back(UP);
    }
    Cmd_Selectee CS;
    S.add_child(&CS);
    nl_error(0, "Starting: v2.0");
    S.event_loop();
    
    // Delete the dynamically allocated UserPkts_UDP objects
    while (!UDPs.empty()) {
      UserPkts_UDP *udp = UDPs.back();
      delete(udp);
      UDPs.pop_back();
    }
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

int UserPkt::Process_Pkt(unsigned char *s, unsigned nc_in) {
  buf = s;
  nc = nc_in;
  cp = 0;
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
  int i = n;
  value = 0;
  while ( i > 0 && cp < nc && isdigit(buf[cp])) {
    value = value*10 + buf[cp++] - '0';
    --i;
  }
  if (i > 0) {
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

int UserPkt::not_double( double *value ) {
  char *endptr;
  int ncf;
  if ( cp < 0 || cp > nc || nc < 0 || buf == 0 )
    msg( 4, "%s not_float precondition failed: "
      "cp = %d, nc = %d, buf %s",
      KW, cp, nc, buf ? "not NULL" : "is NULL" );
  *value = strtod( (char*)&buf[cp], &endptr );
  ncf = endptr - (char*)&buf[cp];
  if ( ncf == 0 ) {
    report_err( "%s Expected float at column %d", KW, cp );
    return 1;
  } else {
    nl_assert( ncf > 0 && cp + ncf <= nc );
    cp += ncf;
    return 0;
  }
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

AVOCETpkt::AVOCETpkt() : UserPkt("AVOCET") {
  TM_init(&AVOCET, sizeof(AVOCET_t));
}

int AVOCETpkt::Process_Pkt() {
  // AVOCET,20160421T21:52:19.497,408.67,409.34,1.914,0.196
  // AVO_HSKPG,40.869,2.777,250.488,0.786
  return (
    not_ISO8601(&AVOCET.Time, false) || not_str( ",", 1) ||
    not_nfloat(&AVOCET.CO2_Licor) || not_str( ",", 1) ||
    not_nfloat(&AVOCET.CO2_Picaro) || not_str( ",", 1) ||
    not_nfloat(&AVOCET.Methane) || not_str( ",", 1) ||
    not_nfloat(&AVOCET.CO)
  );
}

DACOMpkt::DACOMpkt() : UserPkt("DACOM") {
  TM_init(&DACOM, sizeof(DACOM_t));
}

int DACOMpkt::Process_Pkt() {
  // DACOM,78499.17,166.61,1873.44
  return (
    not_double(&DACOM.Time) || not_str( ",", 1) ||
    not_nfloat(&DACOM.CO) || not_str( ",", 1) ||
    not_nfloat(&DACOM.Methane));
}

DLHpkt::DLHpkt() : UserPkt("DLH") {
  TM_init(&DLH, sizeof(DLH_t));
}

int DLHpkt::Process_Pkt() {
  // DLH,78742.50,52.886
  return (
    not_double(&DLH.Time) ||
    not_str( ",", 1) ||
    not_nfloat(&DLH.WaterVapor));
}

TDLIFpkt::TDLIFpkt() : UserPkt("TDLIF") {
  TM_init(&TDLIF, sizeof(TDLIF_t));
}

int TDLIFpkt::Process_Pkt() {
  // TDLIF,20160421T21:52:21,0.008,0.067,0.001
  return (
    not_ISO8601(&TDLIF.Time) || not_str( ",", 1) ||
    not_nfloat(&TDLIF.NO2_ppbv) || not_str( ",", 1) ||
    not_nfloat(&TDLIF.PNs_ppbv) || not_str( ",", 1) ||
    not_nfloat(&TDLIF.ANs_ppbv)
  );
}

NOxyO3pkt::NOxyO3pkt() : UserPkt("NOxyO3") {
  TM_init(&NOxyO3, sizeof(NOxyO3_t));
}

int NOxyO3pkt::Process_Pkt() {
  // NOxyO3,
  return (
    not_double(&NOxyO3.Time) || not_str( ",", 1) ||
    not_nfloat(&NOxyO3.NO) || not_str( ",", 1) ||
    not_nfloat(&NOxyO3.NO2) || not_str( ",", 1) ||
    not_nfloat(&NOxyO3.NOy) || not_str( ",", 1) ||
    not_nfloat(&NOxyO3.O3)
  );
}

UserPkts::UserPkts() {
  Pkts.push_back(new AVOCETpkt());
  Pkts.push_back(new DACOMpkt());
  Pkts.push_back(new DLHpkt());
  Pkts.push_back(new TDLIFpkt());
  // Pkts.push_back(new NOxyO3pkt());
}

UserPkts::~UserPkts() {
  while (!Pkts.empty()) {
    UserPkt *pkt = Pkts.back();
    delete(pkt);
    Pkts.pop_back();
  }
}

UserPkts_UDP::UserPkts_UDP(int udp_port, UserPkts *PktDefs) : Ser_Sel( 0, 0, 600 ) {
  Pkts = PktDefs;
  // Set up TM
  // LARGE_id = Col_send_init( "LARGE", &LARGE, sizeof(LARGE_t), 0);
  // MMS_id = Col_send_init( "MMS", &MMS, sizeof(MMS_t), 0);
  // NOAA_HSP2_id = Col_send_init( "NOAA_HSP2", &NOAA_HSP2, sizeof(NOAA_HSP2_t), 0);
  // NOAA_SP2_id = Col_send_init( "NOAA_SP2", &NOAA_SP2, sizeof(NOAA_SP2_t), 0);
  // NOyO3_id = Col_send_init( "NOyO3", &NOyO3, sizeof(NOyO3_t), 0);
  // Set up UDP listener
  Bind(udp_port);
  flags = Selector::Sel_Read;
  flush_input();
  setenv("TZ", "UTC0", 1); // Force UTC for mktime()
}


// int UserPkts_UDP::Process_LARGE() {
  // if (not_ISO8601(&LARGE.Time) || not_str( ",", 1) ||
      // not_nfloat(&LARGE.ColdCN) || not_str( ",", 1) ||
      // not_nfloat(&LARGE.HotCN) || not_str( ",", 1) ||
      // not_nfloat(&LARGE.Dry_Scattering)) {
    // return 1;
  // }
  // Col_send(LARGE_id);
  // return 0;
// }

// int UserPkts_UDP::Process_MMS() {
  // float discard;
  // if (not_ISO8601(&MMS.Time) || not_str( ",", 1) ||
      // not_nfloat(&MMS.TotalPressure) || not_str(",", 1) || // mb
      // not_nfloat(&MMS.StaticPressure) || not_str(",", 1) || // mb
      // not_nfloat(&discard) || not_str(",", 1) || // volts
      // not_nfloat(&discard) || not_str(",", 1) || // volts
      // not_nfloat(&discard) || not_str(",", 1) || // volts
      // not_nfloat(&discard) || not_str(",", 1) || // volts
      // not_nfloat(&discard) || not_str(",", 1) || // volts
      // not_nfloat(&MMS.Pitch) || not_str(",", 1) || // deg
      // not_nfloat(&MMS.Roll) || not_str(",", 1) || // deg
      // not_nfloat(&MMS.Heading) || not_str(",", 1) || // deg
      // not_nfloat(&MMS.Vns) || not_str(",", 1) || // m/s
      // not_nfloat(&MMS.Vew) || not_str(",", 1) || // m/s
      // not_nfloat(&MMS.Vup) || not_str(",", 1) || // m/s
      // not_nfloat(&MMS.Az) || not_str(",", 1)) { // m/s^2
    // return 1;
  // }
  // Col_send(MMS_id);
  // return 0;
// }

// int UserPkts_UDP::Process_NOAA_HSP2() {
  // if (not_ISO8601(&NOAA_HSP2.Time) || not_str(",", 1) ||
      // not_uchar(NOAA_HSP2.Status) || not_str(",", 1) ||
      // not_nfloat(&NOAA_HSP2.HSP2_IncParticleCount)) {
    // return 1;
  // }
  // Col_send(NOAA_HSP2_id);
  // return 0;
// }

// int UserPkts_UDP::Process_NOAA_SP2() {
  // if (not_ISO8601(&NOAA_SP2.Time) || not_str(",", 1) ||
      // not_uchar(NOAA_SP2.Status) || not_str(",", 1) ||
      // not_nfloat(&NOAA_SP2.SP2_IncParticleCount)) {
    // return 1;
  // }
  // Col_send(NOAA_SP2_id);
  // return 0;
// }

// int UserPkts_UDP::Process_NOyO3() {
  // if (not_ISO8601(&NOyO3.Time) || not_str(",", 1) ||
      // not_nfloat(&NOyO3.NO) || not_str(",", 1) ||
      // not_nfloat(&NOyO3.NOy) || not_str(",", 1) ||
      // not_nfloat(&NOyO3.O3)) {
    // return 1;
  // }
  // Col_send(NOyO3_id);
  // return 0;
// }


int UserPkts_UDP::ProcessData(int flag) {
  char KW[30];
  int rv;
  std::vector<UserPkt *>::const_iterator cur_pkt;
  if (fillbuf()) return 1;
  if (not_KW(&KW[0])) {
    nc = cp = 0;
    return 0;
  }
  for (cur_pkt = Pkts->Pkts.begin(); cur_pkt != Pkts->Pkts.end(); ++cur_pkt) {
    UserPkt * const pkt = *cur_pkt;
    if (strcmp(KW,pkt->KW) == 0) {
      rv = pkt->Process_Pkt(buf+cp, nc-cp);
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
