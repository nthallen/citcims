#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "gps.h"
#include "gpsd_client.h"
#include "nortlib.h"
#include "oui.h"

const char *gpsd_remote_node;
const char *gpsd_remote_exp;
const char *gpsd_TM::GPSD_TM_NAME = "gpsd_tm";

void gpsd_init_options( int argc, char **argv) {
  int c;

  optind = OPTIND_RESET; /* start from the beginning */
  opterr = 0; /* disable default error message */
  while ((c = getopt(argc, argv, opt_string)) != -1) {
    switch (c) {
      case 'n':
        gpsd_remote_node = optarg;
        break;
      case 'e':
        gpsd_remote_exp = optarg;
        break;
      case '?':
        nl_error(3, "Unrecognized Option -%c", optopt);
    }
  }
}

gpsd_TM::gpsd_TM(gpsd_tm_t *data, const char *remnode,
    const char *remexp)
  : Selectee() {
  TMid = 0;
  remote = 0;
  init(data, remnode, remexp);
}

gpsd_TM::gpsd_TM() : Selectee() {
  TMid = 0;
  remote = 0;
}

void gpsd_TM::init(gpsd_tm_t *data, const char *remnode,
    const char *remexp) {
  if (remnode || remexp) {
    int nb;
    char *rmt = (char *)nl_new_memory(PATH_MAX);
    if (remexp == 0) {
      nb = snprintf(rmt, PATH_MAX, "/net/%s%s", remnode,
        tm_dev_name(GPSD_TM_NAME));
    } else {
      if (remnode) {
        nb = snprintf(rmt, PATH_MAX, "/net/%s/dev/huarp/%s/DG/data/%s",
          remnode, remexp, GPSD_TM_NAME);
      } else {
        nb = snprintf(rmt, PATH_MAX, "/dev/huarp/%s/DG/data/%s", remexp,
          GPSD_TM_NAME);
      }
    }
    if (nb >= PATH_MAX)
      nl_error(3, "Constructed path for remote experiment exceeds limit");
    remote = (const char *)rmt;
  }
  TM_data = data;
  Connect();
}

/**
 * Failure of the local connection is considered fatal.
 */
void gpsd_TM::Connect() {
  int save_response = set_response(remote ? 0 : nl_response);
  TMid = Col_send_init( remote ? remote : GPSD_TM_NAME, TM_data,
    sizeof(gpsd_tm_t), 0 );
  if ( TMid ) {
    TO.Clear();
    fd = TMid->fd;
    flags = Selector::Sel_Write;
    if (remote) {
      nl_error(0, "TM connection established to %s", remote);
    }
  } else {
    nl_error(MSG_DBG(0), "TM connection failed to %s", remote);
    TO.Set(10,0);
    flags = Selector::Sel_Timeout;
  }
  set_response(save_response);
}

/**
 * Issues Col_send_reset()
 */
gpsd_TM::~gpsd_TM() {
  if (TMid) {
    Col_send_reset(TMid);
    TMid = 0;
    fd = -1;
  }
}

/**
 * Calls Col_send() and sets gflag(0)
 */
int gpsd_TM::ProcessData(int flag) {
  if (TMid == 0) {
    Connect(); // Will either set TMid or TO
  }
  if (TMid) {
    if (Col_send(TMid)) {
      if (Col_send_reset(TMid)) {
        nl_error(3, "Error closing %s TM connection: %s",
          remote ? "remote" : "local", strerror(errno));
      }
      TMid = 0;
      fd = -1;
      if (remote) {
        TO.Set(10,0);
        flags = Selector::Sel_Timeout;
        return 0;
      } else {
        flags = 0;
        nl_error(0, "Connection to local TM closed");
        return 1;
      }
    }
    if (remote) {
      TM_data->data2_status = 0;
      TM_data->err2_status = 0;
    } else {
      TM_data->data_status = 0;
      TM_data->err_status = 0;
    }
  }
  return 0;
}

Timeout *gpsd_TM::GetTimeout() {
  return &TO;
}
    
gpsd_client::gpsd_client(gpsd_tm_t *data) : Selectee() {
  TM_data = data;
  //Open connection to gpsd and set fd accordingly
  int rc = gps_open("127.0.0.1", "2947", &gpsdata);
  if (rc < 0) {
    nl_error(3, "gps_open() returned error '%s'",
      gps_errstr(errno));
  }
  gps_stream(&gpsdata, WATCH_ENABLE | WATCH_JSON, NULL);
  fd = gpsdata.gps_fd;
  flags = Selector::Sel_Read;
  total_error_count = 0;
  consecutive_error_count = 0;
  errors_suppressed = false;
}

gpsd_client::~gpsd_client() {
  nl_error(0, "Closing connection to gpsd");
  gps_stream(&gpsdata, WATCH_DISABLE, NULL);
  gps_close(&gpsdata);
}

void gpsd_client::set_data_bit(unsigned bit) {
  TM_data->data_status |= bit;
  TM_data->data2_status |= bit;
}

void gpsd_client::set_error_bit(unsigned bit) {
  TM_data->err_status |= bit;
  TM_data->err2_status |= bit;
}

int gpsd_client::ProcessData(int flag) {
  errno = 0;
  if (gps_read(&gpsdata) == -1) {
    ++total_error_count;
    if (!errors_suppressed) {
      if (total_error_count >= total_error_limit ) {
        nl_error(2, "Errors suppressed");
        errors_suppressed = true;
      } else {
        nl_error(2, "gps_read() returned error '%s'",
          gps_errstr(errno));
      }
    }
    if (++consecutive_error_count > consecutive_error_limit) {
      nl_error(3, "Consecutive Error limit exceeded");
    }
  } else {
    consecutive_error_count = 0;
    if (errors_suppressed) {
      if (total_error_count > 0) {
        --total_error_count;
      }
      if (total_error_count == 0) {
        errors_suppressed = false;
      }
    }
    if (gpsdata.set & PACKET_SET) set_data_bit(DATA_PACKET);
    if (gpsdata.set & TIME_SET) {
      TM_data->time = gpsdata.fix.time;
      set_data_bit(DATA_TIME);
    }
    if (gpsdata.set & TIMERR_SET) {
      TM_data->ept = gpsdata.fix.ept;
      set_error_bit(ERR_TIME);
    }
    if (gpsdata.set & LATLON_SET) {
      set_data_bit(DATA_LATLON);
      TM_data->lat = gpsdata.fix.latitude;
      TM_data->lon = gpsdata.fix.longitude;
    }
    if (gpsdata.set & HERR_SET) {
      TM_data->epx = gpsdata.fix.epx;
      TM_data->epy = gpsdata.fix.epy;
      set_error_bit(ERR_HERR);
    }
    if (gpsdata.set & ALTITUDE_SET) {
      set_data_bit(DATA_ALT);
      TM_data->alt = gpsdata.fix.altitude;
    }
    if (gpsdata.set & VERR_SET) {
      TM_data->epv = gpsdata.fix.epv;
      set_error_bit(ERR_VERR);
    }
    if (gpsdata.set & SPEED_SET) {
      set_data_bit(DATA_SPEED);
      TM_data->speed = gpsdata.fix.speed;
    }
    if (gpsdata.set & SPEEDERR_SET) {
      TM_data->eps = gpsdata.fix.eps;
      set_error_bit(ERR_SPEED);
    }
    if (gpsdata.set & TRACK_SET) {
      set_data_bit(DATA_TRACK);
      TM_data->track = gpsdata.fix.track;
    }
    if (gpsdata.set & TRACKERR_SET) {
      TM_data->epd = gpsdata.fix.epd;
      set_error_bit(ERR_TRACK);
    }
    if (gpsdata.set & CLIMB_SET) {
      set_data_bit(DATA_CLIMB);
      TM_data->climb = gpsdata.fix.climb;
    }
    if (gpsdata.set & CLIMBERR_SET) {
      TM_data->epc = gpsdata.fix.epc;
      set_error_bit(ERR_CLIMB);
    }
    if (gpsdata.set & STATUS_SET) {
      set_data_bit(DATA_STATUS);
      // TM_data->status = gpsdata.status;
    }
    if (gpsdata.set & MODE_SET) {
      set_data_bit(DATA_MODE);
      TM_data->mode = gpsdata.fix.mode;
    }
    if (gpsdata.set & DOP_SET) {
      set_data_bit(DATA_DOP);
      TM_data->satellites_used = gpsdata.satellites_used;
    }
    if (gpsdata.set & VERSION_SET) {
      nl_error(0, "VERSION: release=%s rev=%s proto=%d.%d\n",
                gpsdata.version.release,
                gpsdata.version.rev,
                gpsdata.version.proto_major,
                gpsdata.version.proto_minor);
    }
    // if (gpsdata.set & POLICY_SET)
    //   nl_error(0,
    //        "POLICY: watcher=%s nmea=%s raw=%d scaled=%s timing=%s, split24=%s pps=%s, devpath=%s\n",
    //        gpsdata.policy.watcher ? "true" : "false",
    //        gpsdata.policy.nmea ? "true" : "false",
    //        gpsdata.policy.raw,
    //        gpsdata.policy.scaled ? "true" : "false",
    //        gpsdata.policy.timing ? "true" : "false",
    //        gpsdata.policy.split24 ? "true" : "false",
    //        gpsdata.policy.pps ? "true" : "false",
    //        gpsdata.policy.devpath);
    if (gpsdata.set & SATELLITE_SET) {
      set_data_bit(DATA_SATS);
      TM_data->satellites_visible = gpsdata.satellites_visible;
    }
    // if (gpsdata.set & DEVICE_SET)
    //   nl_error(0, "DEVICE: Device is '%s', driver is '%s'\n",
    //        gpsdata.dev.path, gpsdata.dev.driver);
    //  if (gpsdata.set & DEVICELIST_SET) {
    //    int i;
    //    nl_error(0, "DEVICELIST:%d devices:\n",
    //              gpsdata.devices.ndevices);
    //    for (i = 0; i < gpsdata.devices.ndevices; i++) {
    //        nl_error(0, "%d: path='%s' driver='%s'\n",
    //              gpsdata.devices.ndevices,
    //              gpsdata.devices.list[i].path,
    //              gpsdata.devices.list[i].driver);
    //    }
    //  }
    if (gpsdata.set & (TOFF_SET|PPS_SET)) {
      TM_data->real_sec = gpsdata.pps.real.tv_sec;
      TM_data->real_nsec = gpsdata.pps.real.tv_nsec;
      TM_data->clock_sec = gpsdata.pps.clock.tv_sec;
      TM_data->clock_nsec = gpsdata.pps.clock.tv_nsec;
      if (gpsdata.set & TOFF_SET) set_data_bit(DATA_TOFF);
      if (gpsdata.set & PPS_SET) set_data_bit(DATA_PPS);
    }
    if (gpsdata.set & ERROR_SET) {
      nl_error(2, "JSON Error: %s", gpsdata.error);
      set_error_bit(ERR_ERROR);
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  nl_error(0, "Starting V0.1");
  { Selector Loop;
    gpsd_tm_t GPSData;
    memset(&GPSData,0,sizeof(GPSData));
    gpsd_client GPS(&GPSData);
    gpsd_TM TM(&GPSData);
    Cmd_Selectee Cmd;
    gpsd_TM *TM2 = 0;
    
    Loop.add_child(&GPS);
    Loop.add_child(&TM);
    Loop.add_child(&Cmd);
    if (gpsd_remote_node || gpsd_remote_exp) {
      TM2 = new gpsd_TM(&GPSData, gpsd_remote_node, gpsd_remote_exp);
      Loop.add_child(TM2);
    }
    Loop.event_loop();
    delete(TM2); // This is the only dynamically allocated one
  }
  nl_error(0, "Terminating");
}
