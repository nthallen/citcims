/* zaber.cc Driver for Zaber Linear Actuator */
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include "nortlib.h"
#include "nl_assert.h"
#include "oui.h"
#include "zaber_int.h"

const char *zaber_port = "/dev/ser1";

void zaber_init_options(int argc, char **argv) {
  int optltr;

  optind = OPTIND_RESET;
  opterr = 0;
  while ((optltr = getopt(argc, argv, opt_string)) != -1) {
    switch (optltr) {
      case 'p':
        zaber_port = optarg;
        break;
      case '?':
        nl_error(3, "Unrecognized Option -%c", optopt);
      default:
        break;
    }
  }
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { Selector S;
    zaber_tms_t Zbrdata;
    ZaberCmd ZC;
    TM_Selectee TM( "Zaber", &Zbrdata, sizeof(Zbrdata) );
    Zaber Z( zaber_port, &Zbrdata, &ZC );
    // Z.setup(9600, 8, 'n', 1, sizeof(zaber_cmd), 0 );
    Z.setup(9600, 8, 'n', 1, 1, 1 );
    S.add_child(&Z);
    S.add_child(&ZC);
    S.add_child(&TM);
    nl_error( 0, "Starting v1.0d" );
    Z.init();
    S.event_loop();
  }
  nl_error( 0, "Terminating" );
}


/**
 * Will inherit from Ser_Sel although not a serial interface per se. I
 * just want access to all the parsing and error reporting functions.
 * I won't call setup(), which is the only device-specific function.
 */
ZaberCmd::ZaberCmd()
  : Ser_Sel( tm_dev_name("cmd/Zaber"), O_RDONLY|O_NONBLOCK, 50 ) {
}

ZaberCmd::~ZaberCmd() {
}

/**
 * Process commands from command server:
 * W\d:\d+:[-]\d+\n
 * Q\n
 * "" same as quit command
 * For W commands, convert to a proper Zaber query, save and set_gflag(1).
 * The only flag we are sensitive to is the command read.
 */
int ZaberCmd::ProcessData(int flag) {
  nc = cp = 0;
  int drive, cmd, value;
  if (fillbuf()) return 1;
  if (nc == 0 || buf[0] == 'Q') return 1;
  if (not_str("W", 1) ||
      not_int(drive) ||
      not_str(":", 1) ||
      not_int(cmd) ||
      not_str(":", 1) ||
      not_int(value) ||
      not_str("\n", 1) ) {
    return 0;
  }
  if (drive < 0 || drive > 2) {
    report_err("Invalid drive %d in ZaberCmd", drive);
    return 0;
  }
  if (cmd < 0 || cmd > 255) {
    report_err("Invalid command code %d in ZaberCmd", cmd);
    return 0;
  }
  zc.drive = drive;
  zc.cmd = cmd;
  zc.value = value;
  flags = 0; // Don't listen for more commands
  Stor->set_gflag(1);
  report_ok();
  consume(cp);
  return 0;
}

zaber_cmd *ZaberCmd::Command() {
  if ( flags ) {
    nl_error( 2, "ZaberCmd::Command() called when flags != 0" );
    return NULL;
  }
  flags = Selector::Sel_Read;
  return &zc;
}

int Zaber::normal_callin( zaber_cmd *zc, Timeout *timeout ) {
  timeout->Set(0, zc->cmd == 2 ? 1000 : 250);
  return 0;
}

int Zaber::invalid_callin( zaber_cmd *zc, Timeout *timeout ) {
  nl_error( 2, "Invalid command %d:%d '%s'", zc->drive, zc->cmd,
            cmddefs[zc->cmd].cmd_name );
  return 1;
}

void Zaber::renumber_callout( zaber_cmd *zc ) {
  nl_error( 0, "Received renumber response for drive %d", zc->drive );
}

void Zaber::invalid_callout( zaber_cmd *zc ) {
  nl_error( 1, "Invalid reply %d:%d '%s'", zc->drive, zc->cmd,
          cmddefs[zc->cmd].cmd_name );
}

int Zaber::reset_callin( zaber_cmd *zc, Timeout *timeout ) {
  return 0;
}

/* Target speed value TS, then 10^7/TS = microsteps/second
   (so TS is the number of seconds to traverse 10^7 microsteps)
   If we want to travel nsteps, it will take nsteps*TS/10^7
   seconds, or nsteps*TS*ONE_SECOND/10^7 clocks. If we know
   ONE_SECOND = CLOCKS_PER_SEC = 1000, this reduces to
   nsteps*TS/10000 clocks.
   But I need to know the target speed! The time to drive
   will be a bit longer due to acceleration, etc. but that
   can be part of the STD_TIMEOUT already added.
*/
int Zaber::move_callin( zaber_cmd *zc, Timeout *timeout ) {
  return 0;
}

int Zaber::stop_callin( zaber_cmd *zc, Timeout *timeout ) {
  timeout->Set(1,0);
  return 0;
}

void Zaber::position_callout( zaber_cmd *zc ) {
  TMdata->drive[zc->drive-1].position = zc->value;
}

void Zaber::devid_callout( zaber_cmd *zc ) {
  nl_error( 0, "Zaber Drive %d Device ID: %ld", zc->drive, zc->value );
}

void Zaber::version_callout( zaber_cmd *zc ) {
  nl_error( 0, "Zaber Drive %d Firmware Versions %.2lf", zc->drive,
              zc->value * .01 );
}

void Zaber::status_callout( zaber_cmd *zc ) {
  // TMdata->drive[zc->drive-1].status = (unsigned char) zc->value;
  nl_error( 1, "Zaber Drive %d Status %ld", zc->drive, zc->value);
}

void Zaber::voltage_callout( zaber_cmd *zc ) {
  TMdata->drive[zc->drive-1].PS_voltage = (short int) zc->value;
}

void Zaber::error_callout( zaber_cmd *zc ) {
  nl_error( 2, "Drive %d Error Code %ld received", zc->drive,
              zc->value );
}

Zaber::Zaber( const char *path, zaber_tms_t *data, ZaberCmd *ZCmd ) :
    Ser_Sel( path, O_RDWR | O_NONBLOCK, 50 ) {
  int i;
  TMdata = data;
  ZC = ZCmd;
  // To start, we will only listen to the device for initialization
  // flags |= Selector::gflag(0) | Selector::gflag(1);
  CmdsInit();
  for ( i = 0; i < N_DRIVES; i++ ) {
    TMdata->drive[i].position = 0L;
    TMdata->drive[i].PS_voltage = 0;
    TMdata->drive[i].zero = 0;
    drive_state[i].state = 0;
    drive_state[i].failing_cmd = 0;
  }
  n_writes = n_reads = 0;
  nl_error( -2, "Zaber fd = %d, flags = %d, bufsize = %d",
    fd, flags, bufsize );
}

Zaber::~Zaber() {
  nl_error( 0, "n_writes = %d  n_reads = %d", n_writes, n_reads);
}

/**
 * Issues the renumber command
 */
void Zaber::init() {
  flush_input();
  send_command( 0, 2, 0L ); /* Issue renumber command */
  flags |= Selector::Sel_Timeout;
  TO.Set(2,0);
}

Timeout *Zaber::GetTimeout() {
  return &TO;
}

/*
 * So far handling gflag(0) and Sel_Read
 */
int Zaber::ProcessData(int flag) {
  int i;
  if (flag & Selector::gflag(0)) {
    poll();
  }
  if (flag & Selector::Sel_Read) {
    // nl_error(-2, "Saw Sel_Read");
    zaber_cmd zc;
    fillbuf();
    while (nc > 0) {
      if ( nc < sizeof(zc)) {
        // report_err("Received only %d bytes", nc);
        // I'm going to clear out the buffer to try to
        // maintain alignment
        // consume(nc);
        return 0;
      }
      ++n_reads;
      memcpy(&zc, buf, sizeof(zc));
      receive_data( &zc );
      consume(sizeof(zc));
    }
  }
  if (flag & Selector::gflag(1)) {
    send_zcommand(ZC->Command());
  }
  if (flag & Selector::Sel_Timeout) {
    int not_yet = 0;
    for ( i = 0; i < N_DRIVES; i++ ) {
      cmd_stats_t *cs = cmd_stats(2, i+1);
      if (cs->timeout.Set()) not_yet = 1;
    }
    if ( not_yet == 0 ) {
      nl_error( 0, "Received all renumber responses" );
    } else {
      report_err("Timeout waiting for renumber command");
    }
    identify();
  }
  return 0;
}

void Zaber::identify() {
  flags &= ~Selector::Sel_Timeout;
  flags |= Selector::gflag(0) | Selector::gflag(1);
  TO.Clear(); // Just to make sure
  send_command( 0, 50, 0L ); /* Return Device ID */
  send_command( 0, 51, 0L ); /* Return Firmware Version */
  // poll();
}

void Zaber::poll() {
  int i;
  for (i=0; i < N_DRIVES; i++)
    TMdata->drive[i].zero = 1;
  send_command( 0, 60, 0L );   /* Return Position for all drives */
  send_command( 0, 52, 0L );   /* Return Power Supply Voltage for all drives */
  // send_command( 0, 54, 0L );   /* Return Status for all drives */
}

void Zaber::CmdsInit() {
  cmddefs.resize(256);
  cmddefs[0].init( "Reset", false, &Zaber::reset_callin,
         &Zaber::invalid_callout);
  cmddefs[1].init( "Home", false, &Zaber::normal_callin,
         &Zaber::position_callout);
  cmddefs[2].init( "Renumber", false, &Zaber::normal_callin,
         &Zaber::renumber_callout);
  cmddefs[8].init( "Position Tracking During instructed move", true,
         &Zaber::invalid_callin, &Zaber::invalid_callout);
  cmddefs[9].init( "Position Tracking During Manual Move", true,
         &Zaber::invalid_callin, &Zaber::invalid_callout);
  cmddefs[20].init( "Move Absolute", true,
         &Zaber::move_callin, &Zaber::position_callout);
  cmddefs[21].init( "Move Relative", true,
         &Zaber::move_callin, &Zaber::position_callout);
  cmddefs[22].init( "Move at Constant Speed", false,
         &Zaber::invalid_callin, &Zaber::invalid_callout);
  cmddefs[23].init( "Stop", false,
         &Zaber::stop_callin, &Zaber::position_callout);
  cmddefs[37].init( "Set micro-step resolution", false,
         &Zaber::invalid_callin, &Zaber::invalid_callout);
  cmddefs[38].init( "Set running Current", false,
         &Zaber::invalid_callin, &Zaber::invalid_callout);
  cmddefs[39].init( "Set hold Current", false,
         &Zaber::invalid_callin, &Zaber::invalid_callout);
  cmddefs[40].init( "Set Mode", false,
         &Zaber::invalid_callin, &Zaber::invalid_callout);
  cmddefs[41].init( "Set Start Speed", false,
         &Zaber::invalid_callin, &Zaber::invalid_callout);
  cmddefs[42].init( "Set Target Speed", false,
         &Zaber::invalid_callin, &Zaber::invalid_callout);
  cmddefs[43].init( "Set Acceleration Rate", false,
         &Zaber::invalid_callin, &Zaber::invalid_callout);
  cmddefs[44].init( "Set Range", false,
         &Zaber::invalid_callin, &Zaber::invalid_callout);
  cmddefs[45].init( "Set Position", false,
         &Zaber::normal_callin, &Zaber::position_callout);
  cmddefs[50].init( "Return Device ID", false,
         &Zaber::normal_callin, &Zaber::devid_callout);
  cmddefs[51].init( "Return Firmware Version", false,
         &Zaber::normal_callin, &Zaber::version_callout);
  cmddefs[52].init( "Return Power Supply Voltage", false,
         &Zaber::normal_callin, &Zaber::voltage_callout);
  cmddefs[54].init( "Return Status", false,
         &Zaber::normal_callin, &Zaber::status_callout);
  cmddefs[60].init( "Return Position", false,
         &Zaber::normal_callin, &Zaber::position_callout);
  cmddefs[255].init( "Errors", true,
         &Zaber::invalid_callin, &Zaber::error_callout);
}

cmd_stats_t *Zaber::cmd_stats(unsigned char cmd, unsigned drive) {
  if (drive == 0 || drive > N_DRIVES) {
    nl_error(2, "Invalid drive number %d in Zaber::cmd_stats", drive);
  } else if (cmddefs[cmd].stats) {
    return &cmddefs[cmd].stats->cmd_stats[drive-1];
  }
  return 0;
}

void Zaber::send_zcommand( zaber_cmd *zc ) {
  Timeout new_timeout;
  int i, rv;

  if ( zc == 0 ) return;
  if ( zc->drive > N_DRIVES ) {
    nl_error( 2, "Invalid drive number %d", zc->drive );
    return;
  }
  if ( (this->*(cmddefs[zc->cmd].cmd_callin))( zc, &new_timeout ) )
    return;
  nl_assert(cmddefs[zc->cmd].stats);
  for ( i = 1; i <= N_DRIVES; i++ ) {
    if ( zc->drive == i || zc->drive == 0 ) {
      cmd_stats_t *cs = cmd_stats(zc->cmd, i);
      if (cs->timeout.Set()) {
        if (cs->timeout.Expired()) {
          register_timeout( zc->cmd, i );
        } else {
          cs->overwrites++;
        }
      }
      cs->timeout = new_timeout;
      cs->cmds_sent++;
    }
  }
  rv = write( fd, zc, sizeof(zaber_cmd) );
  ++n_writes;
  if ( rv != sizeof(zaber_cmd) ) {
    nl_error( 2, "write(%d) returned %d", sizeof(zaber_cmd), rv );
  }
  delay(20);
}

void Zaber::send_command( drv_t drive, drv_t cmd, long int value ) {
  zaber_cmd zc;
  zc.drive = drive;
  zc.cmd = cmd;
  zc.value = value;
  send_zcommand(&zc);
}


void Zaber::receive_data( zaber_cmd *zc ) {
  int cmd_index = zc->cmd;
  cmd_stats_t *cs;
  drive_state_t *ds;
  int late_reply = 0;

  report_ok();
  if ( zc->drive == 0 || zc->drive > N_DRIVES ) {
    report_err( "Received Invalid drive number %d,%d,%d",
      zc->drive, zc->cmd, zc->value );
    return;
  }
  TMdata->drive[zc->drive-1].zero = 0;
  cs = cmd_stats(cmd_index, zc->drive);
  if (cs) {
    ds = &drive_state[zc->drive-1];
    if ( cs->timeout.Set() ) {
      if ( cs->timeout.Expired() )
        late_reply = 1;
      cs->timeout.Clear();
    } else if ( !cmddefs[cmd_index].unsolicited ) {
      report_err( "Unexpected reply %d:%d '%s'", zc->drive, zc->cmd,
              cmddefs[cmd_index].cmd_name );
    }
    register_reply( zc, late_reply );
  }
  (this->*(cmddefs[cmd_index].cmd_callout))( zc );
}

/* register_timeout() and register_reply() define a state
   machine whose entire purpose is to report communications
   errors while preventing an avalanche of error reports
   in the event of total device failure. Certain types of
   intermittent errors may still produce many error messages,
   but it should be possible to tune these out. One likely
   scenario is a timeout that is set too low so commands
   repeatedly timeout and then recover.
*/
void Zaber::register_timeout( unsigned char cmd_index, unsigned drive ) {
  cmd_stats_t *cs;
  drive_state_t *ds;

  nl_assert(drive > 0 && drive <= N_DRIVES);
  cs = cmd_stats(cmd_index, drive);
  ds = &drive_state[drive-1];
  /* timeout state machine */
  cs->timeouts++;
  switch ( cs->state ) {
    case 0: /* was healthy */
    case 3: /* or tardy */
      if ( ds->state == 0 )
        report_err("Timeout on %d:%d %s",
          drive, cmd_index,
          cmddefs[cmd_index].cmd_name );
      cs->state = 1;
      break;
    case 1:
      if ( ds->state == 0 )
        report_err("Continuing timeout on %d:%d %s",
          drive, cmd_index,
          cmddefs[cmd_index].cmd_name );
      cs->state = 2;
      break;
    case 2:
      break;
    default:
      report_err( "Invalid cs->state: %d", cs->state );
      cs->state = 0;
      break;
  }
  switch ( ds->state ) {
    case 0:
      ds->failing_cmd = cmd_index;
      ds->state = 1;
      break;
    case 1:
      if ( cmd_index != ds->failing_cmd ) {
        report_err( "No response from drive %d", drive );
        ds->state = 2;
      }
      break;
    case 2:
      break;
    default:
      report_err( "Invalid ds->state: %d", ds->state );
      ds->state = 0;
      break;
  }
}

void Zaber::register_reply( zaber_cmd *zc, int late_reply ) {
  unsigned cmd_index = zc->cmd;
  const char *cmd_name = cmddefs[cmd_index].cmd_name;
  cmd_stats_t *cs;
  drive_state_t *ds;
  
  if (zc->drive == 0 || zc->drive > N_DRIVES) {
    report_err( "Invalid drive number %d in register_reply", zc->drive);
    return;
  }
  if (cmddefs[cmd_index].stats == 0) {
    report_err( "cmddefs[cmd_index].stats == 0 in register_reply" );
    return;
  }
  cs = cmd_stats(cmd_index, zc->drive);
  nl_assert(cs);
  ds = &drive_state[zc->drive - 1];
  
  if ( late_reply ) cs->late_replies++;
  else cs->replies_recd++;
  switch ( cs->state ) {
    case 0:
      if ( late_reply ) {
        if ( ds->state == 0 )
          nl_error( 1, "Late reply: %d:%d %s",
            zc->drive, zc->cmd, cmd_name );
        cs->state = 3;
      }
      break;
    case 1:
      if ( late_reply ) {
        if ( ds->state == 0 )
          nl_error( 1, "Late recovery: %d:%d %s",
            zc->drive, zc->cmd, cmd_name );
        cs->state = 3;
      } else cs->state = 0;
      break;
    case 2:
      if ( late_reply ) {
        if ( ds->state == 0 )
          nl_error( 1, "Late recovery: %d:%d %s",
            zc->drive, zc->cmd, cmd_name );
        cs->state = 3;
      } else {
        if ( ds->state == 0 )
          nl_error( 0, "Recovery: %d:%d %s",
            zc->drive, zc->cmd, cmd_name );
        cs->state = 0;
      }
    case 3:
      if ( ! late_reply )
        cs->state = 0;
      break;
    default:
      nl_error( 2, "Invalid cs->state: %d", cs->state );
      cs->state = 0;
      break;
  }
  switch ( ds->state ) {
    case 0: break;
    case 1:
      ds->state = 0;
      break;
    case 2:
      nl_error( 0, "Drive %d recovery", zc->drive );
      ds->state = 0;
      break;
    default:
      nl_error( 2, "Invalid ds->state: %d", ds->state );
      ds->state = 0;
      break;
  }
}

zcmd_def::zcmd_def() {
  init("Unknown Command", true, &Zaber::invalid_callin,
          &Zaber::invalid_callout, false);
}

void zcmd_def::init(const char *name, bool unsol,
      callinfn callin, calloutfn callout, bool valid ) {
  cmd_name = name;
  unsolicited = unsol;
  cmd_callin = callin;
  cmd_callout = callout;
  stats = valid ? new cmd_stat_c : 0;
}

cmd_stat_c::cmd_stat_c() {
  int i;
  for ( i = 0; i < N_DRIVES; i++ ) {
    cmd_stats_t *s = &cmd_stats[i];
    s->cmds_sent = s->replies_recd = s->timeouts =
      s->overwrites = s->state = 0;
  }
}
