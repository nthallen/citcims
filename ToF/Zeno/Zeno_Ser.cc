#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "nortlib.h"
#include "oui.h"
#include "Zeno_Ser.h"

const char *zeno_path = "/dev/ser4";

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { Selector S;
    Zeno_Ser Zeno(zeno_path);
    Zeno.setup(9600, 8, 'n', 1, 1, 10 );
    Cmd_Selectee CS;
    S.add_child(&Zeno);
    S.add_child(&CS);
    nl_error(0, "Starting: v1.0s");
    S.event_loop();
  }
  nl_error(0, "Terminating");
}

Zeno_Ser::Zeno_Ser(const char *path) : Ser_Sel( path, O_RDONLY|O_NONBLOCK, 600 ) {
  // Set up TM
  tm_id = Col_send_init( "ZENO_TM", &ZENO_TM, sizeof(ZENO_TM_t), 0);
  // Set up UDP listener
  flags = Selector::Sel_Read;
  flush_input();
  setenv("TZ", "UTC0", 1); // Force UTC for mktime()
}

int Zeno_Ser::ProcessData(int flag) {
  int rec;
  unsigned short Lightning;
  double Time;
  signed short WindSpeed;
  unsigned short WindDir; /* deg */
  signed   short WindGust;
  signed   short WindSD; /* m/s */
  signed   short Temp; /* C */
  unsigned short RH; /* % */
  signed   short SolarRadiance; /* W/m^2 */
  signed   short Press; /* hPa */
  unsigned short Rain; /* yes */
  signed   short VBatt; /* Volts */
  unsigned long  BIT;
  
  if (fillbuf()) return 1;
  while (cp < nc && isspace(buf[cp])) ++cp;
  if (not_ndigits(4, rec) || not_str(",", 1) ||
      not_zeno_time(Time) || not_str(",", 1) ||
      not_fix(1, WindSpeed) || not_str(",", 1 ) ||
      not_ushort( WindDir) || not_str(",", 1) ||
      not_fix(1, WindSD) || not_str(",", 1) ||
      not_fix(1, WindGust) || not_str(",", 1) ||
      not_fix(1, Temp) || not_str(",", 1) ||
      not_ushort( RH) || not_str(",", 1) ||
      not_fix(1, SolarRadiance) || not_str(",", 1) ||
      not_fix(1, Press) || not_str(",", 1) ||
      not_ushort( Rain) || not_str(",", 1) ||
      not_ushort( Lightning) || not_str(",", 1) ||
      not_fix(1, VBatt) || not_str(",", 1) ||
      not_hex( BIT ) || not_str(",",1) ) {
    if (cp < nc) {
      consume(nc);
    } else {
      cp = 0;
    }
    return 0;
  }

  ZENO_TM.Time = Time;
  ZENO_TM.WindSpeed = WindSpeed;
  ZENO_TM.WindDir = WindDir;
  ZENO_TM.WindGust = WindGust;
  ZENO_TM.WindSD = WindSD;
  ZENO_TM.Temp = Temp;
  ZENO_TM.RH = RH;
  ZENO_TM.SolarRadiance = SolarRadiance;
  ZENO_TM.Press = Press;
  ZENO_TM.Rain = Rain;
  ZENO_TM.VBatt = VBatt;
  ZENO_TM.Lightning = Lightning;
  ZENO_TM.BIT = BIT;
  Col_send(tm_id);
  report_ok();
  consume(cp);
  return 0;
}

int Zeno_Ser::not_ndigits(int n, int &value) {
  int i = n;
  value = 0;
  while ( i > 0 && cp < nc && isdigit(buf[cp])) {
    value = value*10 + buf[cp++] - '0';
    --i;
  }
  if (i > 0) {
    if (cp < nc)
      report_err("Expected %d digits at column %d", n, cp+i-n);
    return 1;
  }
  return 0;
}

int Zeno_Ser::not_zeno_time(double &Time) {
  struct tm buft;
  float secs;
  time_t ltime;

  if (not_ndigits(2, buft.tm_year) ||
      not_str("/",1) ||
      not_ndigits(2, buft.tm_mon) ||
      not_str("/",1) ||
      not_ndigits(2, buft.tm_mday) ||
      not_str(",", 1) ||
      not_ndigits(2, buft.tm_hour) ||
      not_str(":",1) ||
      not_ndigits(2, buft.tm_min) ||
      not_str(":",1) ||
      not_float(secs))
    return 1;
  buft.tm_year += 100;
  buft.tm_mon -= 1;
  buft.tm_sec = 0;
  ltime = mktime(&buft);
  if (ltime == (time_t)(-1))
    report_err("mktime returned error");
  else Time = ltime + secs;
  return 0;
}

/* Return 1 on failure */
int Zeno_Ser::not_ushort(unsigned short &val) {
  val = 0;
  if (buf[cp] == '-') {
    if (isdigit(buf[++cp])) {
      while (isdigit(buf[cp])) {
        ++cp;
      }
      if (cp < nc)
        report_err("not_ushort: Negative int truncated at col %d", cp);
    } else {
      if (cp < nc)
        report_err("Found '-' and no digits at col %d", cp);
      return 1;
    }
  } else if (isdigit(buf[cp])) {
    while (isdigit(buf[cp])) {
      val = val*10 + buf[cp++] - '0';
    }
  } else {
    if (cp < nc)
      report_err("not_ushort: no digits at col %d", cp);
    return 1;
  }
  return 0;
}

/* Return 1 on failure */
int Zeno_Ser::not_fix(int fix, signed short &val) {
  int saw_decimals = 0, saw_neg = 0;

  val = 0;
  if (buf[cp] == '-') {
    saw_neg = 1;
    ++cp;
  }
  if (! isdigit(buf[cp])) {
    if (cp < nc)
      report_err("No digits in not_fix at column %d", cp);
    return 1;
  }
  while (cp < nc) {
    if ( isdigit(buf[cp]) ) {
      val = val * 10 + buf[cp++] - '0';
      if ( saw_decimals && saw_decimals++ == fix ) break;
    } else if ( !saw_decimals && buf[cp] == '.' ) {
      ++cp;
      saw_decimals = 1;
    } else break;
  }
  if ( saw_decimals == 0 ) {
    // report_err("Missing decimal point at col %d", cp);
    while ( ++saw_decimals <= fix ) val *= 10;
  }
  return 0;
}

int Zeno_Ser::not_hex( unsigned long &hexval ) {
  if (! isxdigit(buf[cp])) {
    if (cp < nc)
      report_err("No hex digits at col %d", cp);
    return 1;
  }
  while ( isxdigit(buf[cp]) ) {
    unsigned short digval = isdigit(buf[cp]) ? ( buf[cp] - '0' ) :
           ( tolower(buf[cp]) - 'a' + 10 );
    hexval = hexval * 16 + digval;
    cp++;
  }
  return 0;
}
