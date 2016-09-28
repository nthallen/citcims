#include <errno.h>
#include "IonGauge_int.h"
#include "nortlib.h"
#include "oui.h"

const char *iongauge_path = "/net/athenaII_a/dev/ser4";
int channel_1_enable = 0;
int channel_2_enable = 1;

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  nl_error( 0, "Starting V1.1" );
  if (channel_1_enable == 0 && channel_2_enable == 0)
    nl_error(-1, "No channels enabled, Terminating");
  { Selector S;
    IonGauge_t IGdata;
    IonGauge IG( iongauge_path, &IGdata );
    IG.setup(38400, 8, 'n', 1, 28, 1 );
    Cmd_Selectee QC;
    TM_Selectee TM( "IonGauge", &IGdata, sizeof(IGdata) );
    S.add_child(&IG);
    S.add_child(&QC);
    S.add_child(&TM);
    S.event_loop();
  }
  nl_error( 0, "Terminating" );
}

IonGauge::IonGauge( const char *path, IonGauge_t *data ) :
    Ser_Sel( path, O_RDWR | O_NONBLOCK, 40 ) {
  state = channel_1_enable ? Q1 : Q2;
  query_pending = 0;
  TMdata = data;
  flags |= Selector::gflag(0);
  TMdata->Hex_P = 0.0;
  TMdata->ToF_P = 0.0;
  TMdata->IG_stat = IG_PRESENT;
  FlushInput();
  nl_error( -2, "IonGauge fd = %d, flags = %d", fd, flags );
}

void IonGauge::FlushInput() {
  do {
    nc = cp = 0;
    if (fillbuf()) return;
  } while (nc > 0);
}

int IonGauge::ProcessData(int flag) {
  if ( flag & Selector::gflag(0) ) {
    IssueQuery(1);
  } else {
    int addr1, addr2;
    float val;
    if ( flag & Selector::Sel_Read ) {
      // Read and parse data
      // @100PR3?;FF@100ACKx.xxE+2;FF
      // @100PR4?;FF@100ACKx.xxxE+2;FF
      if ( fillbuf() ) return 1;
      cp = 0;
      while ( cp < nc ) {
        if ( not_found('@') ) return 0;
        if ( cp > 1 ) {
          consume(cp-1); // reverts cp to 0
          cp = 1;
        }
        if ( nc < 28 ) return 0;
        if ( not_int( addr1 ) ||
             not_str( "PR4?;FF@" ) ||
             not_int( addr2 ) ||
             not_str( "ACK" ) ||
             not_float( val ) ||
             not_str( ";FF" ) ) {
          if ( cp < nc ) {
            consume(1); // We'll look ahead for the next '@'
          }
        } else {
          switch (addr2) {
            case 100:
              TMdata->Hex_P = val;
              TMdata->IG_stat |= IG_HEX_P_FRESH;
              state = channel_2_enable ? Q2 : Q1;
              break;
            case 101:
              TMdata->ToF_P = val;
              TMdata->IG_stat |= IG_TOF_P_FRESH;
              state = channel_1_enable ? Q1 : Q2;
              break;
            default:
              nl_error(1, "Unexpected address: @%d", addr2 );
              break;
          }
          consume(cp);
          report_ok();
          if (query_pending )
            IssueQuery(0);
        }
      }
    }
  }
  return 0;
}

void IonGauge::IssueQuery(bool synch) {
  const char *query;
  query_pending = synch;
  int rv;

  if ( synch ) {
    TMdata->IG_stat &= ~(IG_HEX_P_FRESH|IG_TOF_P_FRESH);
  }
  switch (state) {
    case R2:
      fillbuf();
      report_err("Timeout reading from @101");
      FlushInput();
      state = channel_1_enable ? Q1 : Q2;
      break;
    case R1:
      fillbuf();
      report_err("Timeout reading from @100");
      FlushInput();
      state = channel_2_enable ? Q2 : Q1;
      break;
    default:
      break;
  }
  switch (state) {
    case Q1:
      query = "@100PR4?;FF";
      state = R1;
      break;
    case Q2:
      query = "@101PR4?;FF";
      state = R2;
      break;
    default:
      nl_error(4,"Invalid state in second switch");
  }
  rv = write( fd, query, 11 ); //
  if ( rv < 0 ) {
    report_err( "Error %d writing to IonGauge", errno );
  } else if ( rv < 11 ) {
    report_err( "Wrote only %d bytes", rv );
  }
}
