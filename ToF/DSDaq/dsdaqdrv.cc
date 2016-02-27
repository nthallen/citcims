#include <errno.h>
#include <strings.h>
#include <ctype.h>
#include "dsdaqdrv.h"
#include "dsdaqmsg.h"
#include "nortlib.h"
#include "tm.h"

dsdaqdrv::dsdaqdrv(const char *name)
  : io_ascii_drv(name) {
}

dsdaqdrv::~dsdaqdrv() {
}

/**
 * Calls io_ascii_drv::init() and virtual init_hardware()
 * @return non-zero on error
 */
int dsdaqdrv::init() {
  if ( io_ascii_drv::init() ) return 1;
  return init_hardware();
}

/**
 * If **p matches the specified character, advances *p to the next character.
 * @return non-zero if **p does not match the specified character.
 */
static int not_char( const char **p, unsigned char c ) {
  if ( **p == c ) {
    ++*p;
    return 0;
  } else {
    return 1;
  }
}

/**
 * Advances *p to point after the hex value. Sets data to the
 * converted value
 * @return zero non-zero if **p is not a hex digit.
 */
static int not_uhex( const char**p, unsigned short &data ) {
  const unsigned char *s = (const unsigned char *)(*p);
  if ( !isxdigit(*s) ) return 1;
  data = 0;
  while ( isxdigit(*s) ) {
    data = data*0x10 +
      ( isdigit(*s) ?
        (*s - '0') : 
        ( tolower(*s) - 'a' + 0xA));
    ++s;
  }
  *p = (const char *)s;
  return 0;
}

#define MAX_ASCII_WRITES 10
void dsdaqdrv::parse_ascii(const char *ibuf) {
  unsigned short args[MAX_ASCII_WRITES * 2];
  int i = 0;
  const char *p = &ibuf[1];
  switch ( ibuf[0] ) {
    case 'Q':
    case 0: quit(); return;
    case 'W': break;
    default:
      nl_error( 2, "Unrecognized ascii command: '%s'",
	      ascii_escape(ibuf) );
      return;
  }
  while ( i < MAX_ASCII_WRITES && *p != '\0' ) {
    if ( not_uhex( &p, args[2*i] ) ||
         not_char( &p, ':' ) ||
         not_uhex( &p, args[2*i+1] ) ||
         (*p != '\0' &&
          not_char( &p, '\n') &&
          not_char( &p, ';'))) {
      nl_error( 2, "Syntax error: '%s'", ascii_escape(ibuf) );
      return;
    }
    ++i;
  }
  mwrite(2*i, &args[0] );
}

/**
 * @return 0 on success.
 */
int dsdaqdrv::mread(int nr, unsigned short *addr, unsigned short *data) {
  int i, rv = 0;
  // nl_error( 0, "mread( %d )", nr );
  for ( i = 0; i < nr; ++i ) {
    switch (addr[i] & DSDADDR_TYPE) {
      case DSDADDR_AD:
        rv = ad_read( addr[i] & DSDADDR_OFFSET, data[i]);
        break;
      case DSDADDR_DA:
        rv = da_read( addr[i] & DSDADDR_OFFSET, data[i]);
        break;
      case DSDADDR_DIO:
        rv = dio_read( addr[i] & DSDADDR_OFFSET, data[i]);
        break;
      case DSDADDR_BIO:
        rv = bit_read( addr[i] & DSDADDR_OFFSET, data[i]);
        break;
      default:
        rv = 1;
        break;
    }
  }
  return rv;
}

/**
 * @return 0 on success.
 */
int dsdaqdrv::mwrite(int nw, unsigned short *args) {
  int i, rv = 0;
  // nl_error( 0, "mwrite( %d )", nw );
  for ( i = 0; i+2 <= nw; i += 2 ) {
    switch (args[i] & DSDADDR_TYPE) {
      case DSDADDR_AD:
        rv = ad_write( args[i] & DSDADDR_OFFSET, args[i+1]);
        break;
      case DSDADDR_DA:
        rv = da_write( args[i] & DSDADDR_OFFSET, args[i+1]);
        break;
      case DSDADDR_DIO:
        rv = dio_write( args[i] & DSDADDR_OFFSET, args[i+1]);
        break;
      case DSDADDR_BIO:
        rv = bit_write( args[i] & DSDADDR_OFFSET, args[i+1]);
        break;
      default:
        rv = 1;
        break;
    }
  }
  return rv;
}

int dsdaqdrv::init_hardware() {
  return 0;
}

int dsdaqdrv::ad_read(unsigned short offset, unsigned short &data) {
  return 1;
}

int dsdaqdrv::ad_write(unsigned short offset, unsigned short value) {
  return 1;
}

int dsdaqdrv::da_read(unsigned short offset, unsigned short &data) {
  return 1;
}

int dsdaqdrv::da_write(unsigned short offset, unsigned short value) {
  return 1;
}

int dsdaqdrv::dio_read(unsigned short offset, unsigned short &data) {
  return 1;
}

int dsdaqdrv::dio_write(unsigned short offset, unsigned short value) {
  return 1;
}

int dsdaqdrv::bit_read(unsigned short offset, unsigned short &data) {
  return 1;
}

int dsdaqdrv::bit_write(unsigned short offset, unsigned short value) {
  return 1;
}
