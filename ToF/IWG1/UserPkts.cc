#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#include "nortlib.h"
#include "oui.h"
#include "UserPkts_int.h"

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { Selector S;
    UserPkts_UDP UP;
    Cmd_Selectee CS;
    S.add_child(&UP);
    S.add_child(&CS);
    nl_error(0, "Starting: v1.0");
    S.event_loop();
  }
  nl_error(0, "Terminating");
}

UserPkts_UDP::UserPkts_UDP() : Ser_Sel( 0, 0, 600 ) {
  // Set up TM
  AVOCET_id = Col_send_init( "AVOCET", &AVOCET, sizeof(AVOCET_t), 0);
  DACOM_id = Col_send_init( "DACOM", &DACOM, sizeof(DACOM_t), 0);
  DLH_id = Col_send_init( "DLH", &DLH, sizeof(DLH_t), 0);
  LARGE_id = Col_send_init( "LARGE", &LARGE, sizeof(LARGE_t), 0);
  MMS_id = Col_send_init( "MMS", &MMS, sizeof(MMS_t), 0);
  NOAA_HSP2_id = Col_send_init( "NOAA_HSP2", &NOAA_HSP2, sizeof(NOAA_HSP2_t), 0);
  NOAA_SP2_id = Col_send_init( "NOAA_SP2", &NOAA_SP2, sizeof(NOAA_SP2_t), 0);
  NOyO3_id = Col_send_init( "NOyO3", &NOyO3, sizeof(NOyO3_t), 0);
  // Set up UDP listener
  Bind(5108);
  flags = Selector::Sel_Read;
  flush_input();
  setenv("TZ", "UTC0", 1); // Force UTC for mktime()
}

int UserPkts_UDP::Process_AVOCET() {
  if (not_ISO8601(&AVOCET.Time) || not_str( ",", 1) ||
      not_nfloat(&AVOCET.CO2)) {
    return 1;
  }
  Col_send(AVOCET_id);
  return 0;
}

int UserPkts_UDP::Process_DACOM() {
  if (not_ISO8601(&DACOM.Time) || not_str( ",", 1) ||
      not_nfloat(&DACOM.CO) || not_str( ",", 1) ||
      not_nfloat(&DACOM.Methane)) {
    return 1;
  }
  Col_send(DACOM_id);
  return 0;
}

int UserPkts_UDP::Process_DLH() {
  if (not_ISO8601(&DLH.Time) || not_str( ",", 1) ||
      not_nfloat(&DLH.WaterVapor)) {
    return 1;
  }
  Col_send(DLH_id);
  return 0;
}

int UserPkts_UDP::Process_LARGE() {
  if (not_ISO8601(&LARGE.Time) || not_str( ",", 1) ||
      not_nfloat(&LARGE.ColdCN) || not_str( ",", 1) ||
      not_nfloat(&LARGE.HotCN) || not_str( ",", 1) ||
      not_nfloat(&LARGE.Dry_Scattering)) {
    return 1;
  }
  Col_send(LARGE_id);
  return 0;
}

int UserPkts_UDP::Process_MMS() {
  float discard;
  if (not_ISO8601(&MMS.Time) || not_str( ",", 1) ||
      not_nfloat(&MMS.TotalPressure) || not_str(",", 1) || // mb
      not_nfloat(&MMS.StaticPressure) || not_str(",", 1) || // mb
      not_nfloat(&discard) || not_str(",", 1) || // volts
      not_nfloat(&discard) || not_str(",", 1) || // volts
      not_nfloat(&discard) || not_str(",", 1) || // volts
      not_nfloat(&discard) || not_str(",", 1) || // volts
      not_nfloat(&discard) || not_str(",", 1) || // volts
      not_nfloat(&MMS.Pitch) || not_str(",", 1) || // deg
      not_nfloat(&MMS.Roll) || not_str(",", 1) || // deg
      not_nfloat(&MMS.Heading) || not_str(",", 1) || // deg
      not_nfloat(&MMS.Vns) || not_str(",", 1) || // m/s
      not_nfloat(&MMS.Vew) || not_str(",", 1) || // m/s
      not_nfloat(&MMS.Vup) || not_str(",", 1) || // m/s
      not_nfloat(&MMS.Az) || not_str(",", 1)) { // m/s^2
    return 1;
  }
  Col_send(MMS_id);
  return 0;
}

int UserPkts_UDP::Process_NOAA_HSP2() {
  if (not_ISO8601(&NOAA_HSP2.Time) || not_str(",", 1) ||
      not_uchar(NOAA_HSP2.Status) || not_str(",", 1) ||
      not_nfloat(&NOAA_HSP2.HSP2_IncParticleCount)) {
    return 1;
  }
  Col_send(NOAA_HSP2_id);
  return 0;
}

int UserPkts_UDP::Process_NOAA_SP2() {
  if (not_ISO8601(&NOAA_SP2.Time) || not_str(",", 1) ||
      not_uchar(NOAA_SP2.Status) || not_str(",", 1) ||
      not_nfloat(&NOAA_SP2.SP2_IncParticleCount)) {
    return 1;
  }
  Col_send(NOAA_SP2_id);
  return 0;
}

int UserPkts_UDP::Process_NOyO3() {
  if (not_ISO8601(&NOyO3.Time) || not_str(",", 1) ||
      not_nfloat(&NOyO3.NO) || not_str(",", 1) ||
      not_nfloat(&NOyO3.NOy) || not_str(",", 1) ||
      not_nfloat(&NOyO3.O3)) {
    return 1;
  }
  Col_send(NOyO3_id);
  return 0;
}


int UserPkts_UDP::ProcessData(int flag) {
  char KW[30];
  int rv;
  
  if (fillbuf()) return 1;
  if (not_KW(&KW[0])) {
    nc = cp = 0;
    return 0;
  }
  if (strcmp(KW,"AVOCET") == 0) rv = Process_AVOCET();
  else if (strcmp(KW, "DACOM") == 0) rv = Process_DACOM();
  else if (strcmp(KW, "DLH") == 0) rv = Process_DLH();
  else if (strcmp(KW, "LARGE") == 0) rv = Process_LARGE();
  else if (strcmp(KW, "MMS") == 0) rv = Process_MMS();
  else if (strcmp(KW, "NOAA_HSP2") == 0) rv = Process_NOAA_HSP2();
  else if (strcmp(KW, "NOAA_SP2") == 0) rv = Process_NOAA_SP2();
  else if (strcmp(KW, "NOyO3") == 0) rv = Process_NOyO3();
  if (rv) {
    nc = cp = 0;
  } else {
    consume(nc);
    // report_ok();
  }
  return 0;
}

int UserPkts_UDP::not_ndigits(int n, int &value) {
  int i = n;
  value = 0;
  while ( i > 0 && cp < nc && isdigit(buf[cp])) {
    value = value*10 + buf[cp++] - '0';
    --i;
  }
  if (i > 0) {
    if (cp < nc)
      report_err("Expected %d digits at column %d", n, cp-i);
    return 1;
  }
  return 0;
}

int UserPkts_UDP::not_ISO8601(double *Time) {
  struct tm buft;
  float secs;
  time_t ltime;

  if (not_ndigits(4, buft.tm_year) ||
      not_str("-",1) ||
      not_ndigits(2, buft.tm_mon) ||
      not_str("-",1) ||
      not_ndigits(2, buft.tm_mday) ||
      not_str("T", 1) ||
      not_ndigits(2, buft.tm_hour) ||
      not_str(":",1) ||
      not_ndigits(2, buft.tm_min) ||
      not_str(":",1) ||
      not_float(secs))
    return 1;
  buft.tm_year -= 1900;
  buft.tm_mon -= 1;
  buft.tm_sec = 0;
  ltime = mktime(&buft);
  if (ltime == (time_t)(-1))
    report_err("mktime returned error");
  else *Time = ltime + secs;
  return 0;
}

/**
 * accept a float or return a NaN (99999.)
 * if the next char is a comma or CR
 */
int UserPkts_UDP::not_nfloat(float *value, float NaNval) {
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
  if (not_float(val)) return 1;
  *value = val;
  return 0;
}

int UserPkts_UDP::not_uchar(unsigned char &val) {
  int sval;
  if (not_int(sval)) return 1;
  if (sval < 0 || sval > 255) {
    report_err("uchar value out of range: %d", sval);
    return 1;
  }
  val = sval;
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
