#include <errno.h>
#include <strings.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include "Hercules.h"
#include "oui.h"
#include "nortlib.h"

Hercules::Hercules(int ad_se) : dsdaqdrv("Hercules") {
  int i;
  n_ad = ad_se ? 16 : 8;
  n_dio = 5;
  n_bio = 48; // hard coded, but really configurable.
  dabu = 0; // bipolar. Set to 4 for unipolar
  base = 0x240;
  for (i = 0; i < n_dio; ++i) dio_values[i] = 0;
}

Hercules::~Hercules() {}

/**
 * @return 0 on success.
 */
int Hercules::init_hardware() {
  if ( ThreadCtl(_NTO_TCTL_IO, 0) == -1 )
    nl_error( 3, "Unable to enable I/O privilege: %s", strerror(errno) );
  out8(base, 0x40); // Reset board
  out8(base, 0x00); // Unreset board
  out8(base + 22, 0xF ); // A-D: Out, E: In
  da_write(HERC_DA_SU + 0, 2048);
  da_write(HERC_DA_SU + 1, 2048);
  da_write(HERC_DA_SU + 2, 2048);
  da_write(3, 2048); // D/As will Glitch to +5V
  out8(base + 1, dabu); // D/As will return to zero, Bipolar, single-ended
  return 0;
}

/**
 * @return 0 on success.
 */
int Hercules::ad_read(unsigned short offset, unsigned short &data) {
  int i;
  int i1, i2;
  static int n_verbose = 0;
  unsigned short channel = offset & 0x1F;
  unsigned short gain = (offset >> 5) & 3;
  unsigned short sed_adbu = (offset >> 7) & 3;
  if (offset > HERC_AD_OFFSET_MAX) return 1;
  out8(base + 1, dabu | sed_adbu); // select se/diff and bipolar/unipolar
  out8(base + 2, channel ); // low channel
  out8(base + 3, channel ); // high channel
  out8(base + 4, gain ); // set gain (global)
  for ( i = 20; i > 0; --i ) {
    if ( (in8(base + 4) & 0x40) == 0 ) break; // WAIT bit
  }
  i1 = i;
  if (i > 0) {
    out8(base+15, 1); // start A/D conversion
    for ( i = 20; i > 0; --i ) {
      if ((in8(base + 4) & 0x80) == 0) break;
    }
  }
  i2 = i;
  if (i == 0) {
    nl_error( 2, "Timeout waiting for A/D to settle or convert" );
    data = 0;
    return 1;
  }
  data = in16(base);
  if ( nl_debug_level <= -2 && n_verbose < 32 ) {
    ++n_verbose;
    nl_error(-2, "da_read(0x%02X) i1 = %d  i2 = %d", channel, i1, i2 );
  }
  return 0;
}

/**
 * @return 0 on success.
 */
int Hercules::da_read(unsigned short offset, unsigned short &data) {
  if ( offset >= 4 ) return 1;
  data = da_values[offset];
  return 0;
}

/**
 * @return 0 on success.
 */
int Hercules::da_write(unsigned short offset, unsigned short value) {
  int i;
  unsigned short channel = offset & ~HERC_DA_SU;
  if ( channel >= 4 ) return 1;
  nl_error( -2, "da_write(%d, 0x%04X)%s", channel, value,
    (offset & HERC_DA_SU) ? " SU" : "");
  for ( i = 100; i > 0; --i ) {
    if ( (in8(base + 4) & 0x20) == 0 ) break; // DABUSY bit
  }
  if ( i == 0 ) {
    nl_error(2, "Timeout writing to D/A");
    return 1;
  }
  da_values[channel] = value;
  out8(base + 6, value & 0xFF);
  out8(base + 7, (value >> 8) & 0xF);
  out8(base + 5, offset);
  return 0;
}

/**
 * @return 0 on success.
 */
int Hercules::dio_read(unsigned short offset, unsigned short &data) {
  if (offset >= n_dio) return 1;
  data = in8(base + 16 + offset);
  return 0;
}

/**
 * @return 0 on success.
 */
int Hercules::dio_write(unsigned short offset, unsigned short value) {
  if ( offset >= n_dio ) return 1;
  dio_values[offset] = value;
  out8(base + 16 + offset, value);
  nl_error(-2, "DIOW: port:%d value:%02X", offset, value);
  if (offset == 3) {
    value = in8(base+16+offset);
    nl_error(-2, "RDBK: port:%d value:%02X", offset, value);
  }
  return 0;
}

/**
 * @return 0 on success.
 */
int Hercules::bit_read(unsigned short offset, unsigned short &data) {
  unsigned char mask;
  if (offset >= n_dio) return 1; // and we know n_dio == 3
  mask = 1 << offset;
  data = (in8(base + 8) & mask) ? 1 : 0; // Read from port A
  return 0;
}

dio_scdc_def Hercules::scdc_def[] = {
  { HERC_UNSTRB, 0,  0x1,    0 }, // 0: Cal  bypass off
  { HERC_UNSTRB, 0,  0x1,  0x1 }, // 1: Cal  bypass on
  { HERC_UNSTRB, 0,  0x2,    0 }, // 2: Cal scrub  off
  { HERC_UNSTRB, 0,  0x2,  0x2 }, // 3: Cal scrub  on
  { HERC_UNSTRB, 0,  0x4,    0 }, // 4: Cal H2O2 off
  { HERC_UNSTRB, 0,  0x4,  0x4 }, // 5: Cal H2O2 on
  { HERC_UNSTRB, 0,  0x8,    0 }, // 6: Cal oacid off
  { HERC_UNSTRB, 0,  0x8,  0x8 }, // 7: Cal oacid on
  { HERC_UNSTRB, 0, 0x10,    0 }, // 8: Cal MHP off
  { HERC_UNSTRB, 0, 0x10, 0x10 }, // 9: Cal MHP on
  { HERC_UNSTRB, 0, 0x20,    0 }, // 10: Cal spare1 off 
  { HERC_UNSTRB, 0, 0x20, 0x20 }, // 11: Cal spare1 on 
  { HERC_UNSTRB, 0, 0x40,    0 }, // 12: Cal spare2 off
  { HERC_UNSTRB, 0, 0x40, 0x40 }, // 13: Cal spare2 on
  { HERC_UNSTRB, 0, 0x80,    0 }, // 14: Ambient zero off
  { HERC_UNSTRB, 0, 0x80, 0x80 }, // 15: Ambient zero on
  { HERC_STRB,   1,  0x2,  0x2 }, // 16  Turbo scroll pump on
  { HERC_STRB,   1,  0x4,  0x4 }, // 17  Turbo scroll pump off
  { HERC_STRB,   1,  0x8,  0x8 }, // 18  Turbo scroll pump valve on
  { HERC_STRB,   1, 0x10, 0x10 }, // 19  Turbo scroll pump valve off
  { HERC_STRB,   1, 0x20, 0x20 }, // 20  Flow tube scroll pump on
  { HERC_STRB,   1, 0x40, 0x40 }, // 21  Flow tube scroll pump off
  { HERC_STRB,   1, 0x80, 0x80 }, // 22  Flow tube scroll pump valve on
  { HERC_STRB,   2,  0x1,  0x1 }, // 23  Flow tube scroll pump valve off
  { HERC_STRB,   2,  0x2,  0x2 }, // 24  Flow tube dewar valve on
  { HERC_STRB,   2,  0x4,  0x4 }, // 25  Flow tube dewar valve off
  { HERC_UNSTRB, 2, 0x10,    0 }, // 26: Turbopump b power off
  { HERC_UNSTRB, 2, 0x10, 0x10 }, // 27: Turbopump b power on
  { HERC_UNSTRB, 2, 0x20,    0 }, // 28: Turbopump a power off
  { HERC_UNSTRB, 2, 0x20, 0x20 }, // 29: Turbopump a power on
  { HERC_UNSTRB, 2, 0x40,    0 }, // 30: Turbopump a stop
  { HERC_UNSTRB, 2, 0x40, 0x40 }, // 31: Turbopump a start
  { HERC_UNSTRB, 2, 0x80,    0 }, // 32: Turbopump a high
  { HERC_UNSTRB, 2, 0x80, 0x80 }, // 33: Turbopump a low
  { HERC_UNSTRB, 3,  0x1,    0 }, // 34: Turbopump b stop
  { HERC_UNSTRB, 3,  0x1,  0x1 }, // 35: Turbopump b start
  { HERC_UNSTRB, 3,  0x2,    0 }, // 36: Turbopump b high
  { HERC_UNSTRB, 3,  0x2,  0x2 }, // 37: Turbopump b low
  { HERC_UNSTRB, 3, 0x10,    0 }, // 38: Butterfly Valve control mode
  { HERC_UNSTRB, 3, 0x10, 0x10 }, // 39: Butterfly Valve control mode
  { HERC_UNSTRB, 3, 0x40,    0 }, // 40: HV power off
  { HERC_UNSTRB, 3, 0x40, 0x40 }, // 41: HV power on
  { HERC_UNSTRB, 3, 0x80,    0 }, // 42: Oct power off
  { HERC_UNSTRB, 3, 0x80, 0x80 }, // 43: Oct power on
  { HERC_UNSTRB, 3, 0x2C, 0x04 }, // 44: Butterfly Valve hold
  { HERC_UNSTRB, 3, 0x2C, 0x08 }, // 45: Butterfly Valve close
  { HERC_UNSTRB, 3, 0x2C, 0x20 }, // 46: Butterfly Valve open
  { HERC_UNSTRB, 3, 0x2C, 0x00 }  // 47: Butterfly Valve control
};

static void delay_20_usecs() {
  int i;
  for (i = 0; i < 1000; ++i);
}

/**
 * @return 0 on success.
 */
int Hercules::bit_write(unsigned short offset, unsigned short value) {
  unsigned short val;
  if (offset >= n_bio) return 1; // and we know n_bio == 8
  dio_scdc_def *cdef = &scdc_def[offset];
  switch (cdef->cmdtype) {
    case HERC_SPARE:
      nl_error(2, "Invalid command index: %d", offset);
      return 1;
    case HERC_STRB:
      val = dio_values[cdef->portno];
      val = (val & ~cdef->mask) | ( cdef->value & cdef->mask);
      nl_error(-2, "STRB(%d) port:%d val:%02X", offset, cdef->portno, val);
      dio_write(cdef->portno, val); // makes sure dio_values is updated
      // set strobe (port 1 bit 0)
      out8(base+16+1, dio_values[1] | 1);
      delay_20_usecs();
      out8(base+16+1, dio_values[1]);
      delay_20_usecs();
      val = val & ~cdef->mask;
      dio_write(cdef->portno, val);
      return 0;
    case HERC_UNSTRB:
      val = dio_values[cdef->portno];
      val = (val & ~cdef->mask) | ( cdef->value & cdef->mask);
      nl_error(-2, "UNSTRB(%d) port:%d val:%02X", offset, cdef->portno, val);
      dio_write(cdef->portno, val); // makes sure dio_values is updated
      return 0;
    default:
      nl_error(2, "Unknown cmdtype %d in bit_write cmd offset %d",
        cdef->cmdtype, offset);
      return 1;
  }
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { Hercules dsd(1);
    dsd.init();
    dsd.operate();
  }
}
