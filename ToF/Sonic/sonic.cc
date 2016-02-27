/* sonic.cc
   Driver for CSAT3 Three Dimensional Sonic Anemometer
*/
#include <errno.h>
#include <string.h>
#include "sonic.h"
#include "nortlib.h"
#include "oui.h"

static const char *device_name = "/dev/ser1";

void sonic_init_options( int argc, char **argv) {
  int c;

  optind = OPTIND_RESET; /* start from the beginning */
  opterr = 0; /* disable default error message */
  while ((c = getopt(argc, argv, opt_string)) != -1) {
    switch (c) {
      case 'p':
        device_name = optarg;
        break;
      case '?':
        nl_error(3, "Unrecognized Option -%c", optopt);
    }
  }
}

Sonic_TM::Sonic_TM() : TM_Selectee("SonicData", &SonicData, sizeof(SonicData_t)) {
  clear_TM();
}

Sonic_TM::~Sonic_TM() {}

void Sonic_TM::clear_TM() {
  SonicData.U = 0.;
  SonicData.V = 0.;
  SonicData.W = 0.;
  SonicData.C = 0.;
  SonicData.N = 0;
  SonicData.Status = 0;
}

void Sonic_TM::RecordData(const unsigned char *sonic_buf) {
  SonicData.U += convert_raw(sonic_buf, 0, 10);
  SonicData.V += convert_raw(sonic_buf, 2, 8);
  SonicData.W += convert_raw(sonic_buf, 4, 6);
  SonicData.C += convert_raw(sonic_buf, 6, 0);
  SonicData.Status |= sonic_buf[9] >> 4;
  ++SonicData.N;
}

float Sonic_TM::convert_raw(const unsigned char *buf, int idx, int bits) {
  float value;
  signed short ival = buf[idx] + ( buf[idx+1] << 8 );
  if ( bits ) {
    unsigned short bvals = ((( buf[9] << 8 ) + buf[8]) >> bits) & 0x3;
    value = ival * .002/(1<<bvals);
  } else {
    /* speed of sound */
    value = ival * .001 + 340.;
  }
  return value;
}

void Sonic_TM::finalize_avg( void ) {
  if ( SonicData.N ) {
    SonicData.U /= SonicData.N;
    SonicData.V /= SonicData.N;
    SonicData.W /= SonicData.N;
    SonicData.C /= SonicData.N;
  }
}

int Sonic_TM::ProcessData(int flag) {
  if (flag & Selector::Sel_Write) {
    finalize_avg();
    Col_send(TMid);
    clear_TM();
  }
  return 0;
}

Sonic::Sonic() : Ser_Sel() {
  Driver = 0;
}

Sonic::~Sonic() {}

void Sonic::Sonic_init(const char *path, SonicDriver *Drv) {
  init(path, O_RDONLY | O_NONBLOCK, nb_rec*3);
  setup(19200, 8, 'n', 1, nb_rec, 0);
  Driver = Drv;
  if (tcgetattr(fd, &termios_m)) {
    nl_error(2, "Error from tcgetattr: %s", strerror(errno));
  }
  flush_input();
}

unsigned char reverse(unsigned char in) {
  unsigned char out = 0;
  int i;
  for (i = 0; i < 7; ++i) {
    out = (out << 1) | (in & 1);
    in >>= 1;
  }
  return out;
}

int Sonic::ProcessData(int flag) {
  if (flag & Selector::Sel_Read) {
    unsigned min;
    if (fillbuf()) return 1;
    while (nc >= nb_rec) {
      cp = 0;
      if ( buf[nb_rec-1] == 0xAA &&
           buf[nb_rec-2] == 0x55 ) {
        Driver->RecordData(buf);
        consume(nb_rec);
        report_ok();
      } else {
        /* partial record */
        int i;
        for (i = nb_rec-1; i > 0; --i) {
          if ( buf[i] == 0xAA && buf[i-1] == 0x55 ) {
            report_err("Partial record");
            consume(i+1);
            break;
          }
        }
        if (i == 0) {
          // Didn't see it going backwards: try forwards?
          for (i = nb_rec; i < nc; ++i) {
            if ( buf[i] == 0xAA && buf[i-1] == 0x55 ) {
              report_err("Missed Synch");
              consume(i+1-nb_rec);
              i = 0;
              break;
            }
          }
          if (i >= nc) {
            report_err("No Synch observed");
            consume(nc-nb_rec+1);
          }
        }
      }
    }
    min = nb_rec - nc;
    if (min != termios_m.c_cc[VMIN]) {
      termios_m.c_cc[VMIN] = min;
      if (tcsetattr(fd, TCSANOW, &termios_m)) {
        nl_error(2, "Error from tcsetattr: %s", strerror(errno));
      }
    }
  }
  return 0;
}

SonicDriver::SonicDriver(const char *path) : Selector() {
  Serial.Sonic_init(path, this);
  add_child(&Serial);
  add_child(&TM);
  add_child(&Cmd);
}

SonicDriver::~SonicDriver() {}

int main( int argc, char **argv ) {
  oui_init_options( argc, argv );
  { SonicDriver Drv(device_name);
    nl_error(0, "Started");
    Drv.event_loop();
    nl_error(0, "Terminating");
  }
  return 0;
}
