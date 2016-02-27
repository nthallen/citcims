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
  n_bio = 40; // hard coded, but really configurable.
  dabu = 4; // 0 for bipolar. Set to 4 for unipolar
  base = 0x240;
  for (i = 0; i < n_dio; ++i) dio_values[i] = 0;
  for (i = 0; i < 4; ++i) da_values[i] = 0;
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
  out8(base+22, 0x17); /* A, B, C & E output */
  if (dabu == 0) {
    da_write(HERC_DA_SU + 0, 2048);
    da_write(HERC_DA_SU + 1, 2048);
    da_write(HERC_DA_SU + 2, 2048);
    da_write(3, 2048); // D/As will Glitch to +5V
    out8(base + 1, dabu); // D/As will return to zero, Bipolar, single-ended
  }
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
  { HERC_STRB,   0, 0x01, 0x01 }, //   CMD_A0
  { HERC_STRB,   0, 0x02, 0x02 }, //   CMD_A1
  { HERC_STRB,   0, 0x04, 0x04 }, //   CMD_A2
  { HERC_STRB,   0, 0x08, 0x08 }, //   CMD_A3
  { HERC_STRB,   0, 0x10, 0x10 }, //   CMD_A4
  { HERC_STRB,   0, 0x20, 0x20 }, //   CMD_A5
  { HERC_STRB,   0, 0x40, 0x40 }, //   CMD_A6
  { HERC_SET,    0, 0x80, 0x80 }, //   CMD_A7
  { HERC_SET,    1, 0x01, 0x01 }, //   CMD_B0
  { HERC_SET,    1, 0x02, 0x02 }, //   CMD_B1
  { HERC_STRB,   1, 0x04, 0x04 }, //   CMD_B2
  { HERC_STRB,   1, 0x08, 0x08 }, //   CMD_B3
  { HERC_STRB,   1, 0x10, 0x10 }, //   CMD_B4
  { HERC_INV,    1, 0x20, 0x20 }, //   CMD_B5 Strobe
  { HERC_SET,    1, 0x40, 0x40 }, //   CMD_B6
  { HERC_SET,    1, 0x80, 0x80 }, //   CMD_B7
  { HERC_SET,    2, 0x01, 0x01 }, //   CMD_C0
  { HERC_SET,    2, 0x02, 0x02 }, //   CMD_C1
  { HERC_SET,    2, 0x04, 0x04 }, //   CMD_C2
  { HERC_SET,    2, 0x08, 0x08 }, //   CMD_C3
  { HERC_SET,    2, 0x10, 0x10 }, //   CMD_C4
  { HERC_INV,    2, 0x20, 0x20 }, //   CMD_C5
  { HERC_INV,    2, 0x40, 0x40 }, //   CMD_C6
  { HERC_SET,    2, 0x80, 0x80 }, //   CMD_C7
  { HERC_INV,    3, 0x01, 0x01 }, //   CMD_D0 Invalid
  { HERC_INV,    3, 0x02, 0x02 }, //   CMD_D1 Invalid
  { HERC_INV,    3, 0x04, 0x04 }, //   CMD_D2 Invalid
  { HERC_INV,    3, 0x08, 0x08 }, //   CMD_D3 Invalid
  { HERC_INV,    3, 0x10, 0x10 }, //   CMD_D4 Invalid
  { HERC_INV,    3, 0x20, 0x20 }, //   CMD_D5 Invalid
  { HERC_INV,    3, 0x40, 0x40 }, //   CMD_D6 Invalid
  { HERC_INV,    3, 0x80, 0x80 }, //   CMD_D7 Invalid
  { HERC_SET,    4, 0x01, 0x01 }, //   CMD_E0
  { HERC_SET,    4, 0x02, 0x02 }, //   CMD_E1
  { HERC_SET,    4, 0x04, 0x04 }, //   CMD_E2
  { HERC_SET,    4, 0x08, 0x08 }, //   CMD_E3
  { HERC_SET,    4, 0x10, 0x10 }, //   CMD_E4
  { HERC_SET,    4, 0x20, 0x20 }, //   CMD_E5
  { HERC_SET,    4, 0x40, 0x40 }, //   CMD_E6
  { HERC_SET,    4, 0x80, 0x80 }  //   CMD_E7
};

static void delay_20_usecs() {
  int i;
  for (i = 0; i < 4600; ++i);
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
      // set strobe (port 1 bit 5)
      out8(base+16+1, dio_values[1] | 0x20);
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
    case HERC_SET:
      val = dio_values[cdef->portno];
      val = (val & ~cdef->mask) | (value & cdef->mask);
      nl_error(-2, "SET(%d) port:%d val:%02X", offset, cdef->portno, val);
      dio_write(cdef->portno, val); // makes sure dio_values is updated
      return 0;
    case HERC_INV:
      nl_error(2, "Invalid command offset %d in bit_write", offset);
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
