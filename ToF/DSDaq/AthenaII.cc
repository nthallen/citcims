#include <errno.h>
#include <strings.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include "AthenaII.h"
#include "oui.h"
#include "nortlib.h"

AthenaII::AthenaII(int ad_se) : dsdaqdrv("AthenaII") {
  int i;
  n_ad = ad_se ? 16 : 8;
  n_dio = 3;
  n_bio = 8; // hard coded, but really configurable.
  base = 0x280;
  for (i = 0; i < 4; ++i) da_values[i] = 2048;
  for (i = 0; i < n_dio; ++i) dio_values[i] = 0;
}

AthenaII::~AthenaII() {}

/**
 * @return 0 on success.
 */
int AthenaII::init_hardware() {
  if ( ThreadCtl(_NTO_TCTL_IO, 0) == -1 )
    nl_error( 3, "Unable to enable I/O privilege: %s", strerror(errno) );
  out8( base, 0x60 ); // Reset board, including D/A
  out8( base + 11, 0x8B ); // A:Out, B,C:In
  return 0;
}

void AthenaII::parse_ascii(const char *ibuf) {
  // if (ibuf[0] != '\0')
    dsdaqdrv::parse_ascii(ibuf);
}

/**
 * @return 0 on success.
 */
int AthenaII::ad_read(unsigned short offset, unsigned short &data) {
  int i;
  unsigned short channel = offset & 0xFF;
  unsigned short gain = (offset >> 8) & 3;
  if ( channel >= n_ad ) return 1;
  out8( base+2, (channel<<4) | channel ); // select channel
  out8( base+3, gain ); // set gain
  for ( i = 100; i > 0; --i ) {
    if ( (in8( base+3) & 0x20) == 0 ) break;
  }
  if (i > 0) {
    out8(base, 0x80); // start A/D conversion
    for ( i = 100; i > 0; --i ) {
      if ((in8(base + 3) & 0x80) == 0) break;
    }
  }
  if (i == 0) {
    nl_error( 2, "Timeout waiting for A/D to settle or convert" );
    data = 0;
    return 1;
  }
  data = in8(base);
  data += in8(base+1)<<8;
  return 0;
}

/**
 * @return 0 on success.
 */
int AthenaII::da_read(unsigned short offset, unsigned short &data) {
  if ( offset >= 4 ) return 1;
  data = da_values[offset];
  return 0;
}

/**
 * @return 0 on success.
 */
int AthenaII::da_write(unsigned short offset, unsigned short value) {
  if ( offset >= 4 ) return 1;
  nl_error( -2, "da_write(%d, 0x%04X)", offset, value);
  da_values[offset] = value;
  out8(base + 6, value & 0xFF);
  out8(base + 7, ((value >> 8) & 0xF) + (offset << 6));
  return 0;
}

/**
 * @return 0 on success.
 */
int AthenaII::dio_read(unsigned short offset, unsigned short &data) {
  if (offset >= n_dio) return 1;
  data = in8(base + 8 + offset);
  return 0;
}

/**
 * @return 0 on success.
 */
int AthenaII::dio_write(unsigned short offset, unsigned short value) {
  if ( offset != 0 ) return 1; // Because only one port is writable
  dio_values[0] = value;
  out8(base + 8, value);
  return 0;
}

/**
 * @return 0 on success.
 */
int AthenaII::bit_read(unsigned short offset, unsigned short &data) {
  unsigned char mask;
  if (offset >= n_dio) return 1; // and we know n_dio == 3
  mask = 1 << offset;
  data = (in8(base + 8) & mask) ? 1 : 0; // Read from port A
  return 0;
}

/**
 * @return 0 on success.
 */
int AthenaII::bit_write(unsigned short offset, unsigned short value) {
  unsigned char mask;
  if (offset >= n_bio) return 1; // and we know n_bio == 8
  mask = 1 << offset;
  if (value) {
    dio_values[0] |= mask;
  } else {
    dio_values[0] &= ~mask;
  }
  nl_error(-2, "Bit value 0x%02X", dio_values[0]);
  out8(base + 8, dio_values[0]);
  return 0;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { AthenaII dsd(1);
    dsd.init();
    dsd.operate();
  }
}
