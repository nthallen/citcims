#include <unistd.h>
#include "oui.h"
#include "nortlib.h"
#include "dsdaq.h"

/* This is a demonstration dsdaq client to test the dsdaqdrv library */

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  {
    int i;
    dsdaq dsc("AthenaII");
    dsc.init();
//  dsdaq_req *mread =
//	dsc.pack( DSDAQ_READ, 5, 0x2000, 0x2001, 0x2002, 0x2003, 0x2004 );
    unsigned short data, mdata[5];
//  if ( dsc.read( 0x1000, data ) ) {
//    unsigned short i;
//    nl_error( 2, "Error reading from 0x1000" );
//    for ( i = 0; i < 10; ++i ) {
//	sleep(1);
//	if ( !dsc.read( 0x1000, data ) )
//	  break;
//    }
//  } else if ( data != 0 ) {
//    nl_error( 2, "Expected 0 on read from 0x1000: read 0x%04X", data );
//  }
    for ( i = 0; i < 16; ++i ) {
      if ( dsc.read( 0x1000+i, data ) ) {
        nl_error( 2, "Error reading from 0x%04X", 0x1000+i);
      } else {
        nl_error( 0, "Read 0x%04X:%04X",
          0x1000+i, data );
      }
    }

    if ( dsc.write( 0x2000, 0x5555 ) )
      nl_error( 2, "Error writing to 0x2000" );
    if ( dsc.read( 0x2000, data ) )
      nl_error( 2, "Error reading 0x2000" );
    nl_error( 0, "Read 0x%04X:%04X", 0x2000, data );

    if ( dsc.write( 0x4000, 1 ) )
      nl_error( 2, "Error writing to 0x4000" );
    if ( dsc.read( 0x3000, data ) )
      nl_error( 2, "Error reading from 0x3000" );
    nl_error( 0, "Read 0x%04X:%04X", 0x3000, data );

//    if ( mread->send( &mdata[0] ) )
//      nl_error( 2, "Error on mread" );
//    if ( dsc.read( 0, data ) )
//      nl_error( 0, "Received error on read from 0" );
//    else
//      nl_error( 2, "Did not receive error on read from 0" );
//    delete(mread);
  }
  nl_error( 0, "Ending" );
  return 0;
}
