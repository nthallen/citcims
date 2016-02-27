#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "gps.h"

extern void libgps_dump_state(struct gps_data_t *collect);

int main(int argc, char **argv) {
  struct gps_data_t gpsdata;
  int rc, i;

  rc = gps_open("127.0.0.1", "2947", &gpsdata);
  if (rc < 0) {
    fprintf(stderr, "gps_open() returned error '%s'\n",
      gps_errstr(errno));
    exit(1);
  }
  gps_stream(&gpsdata, WATCH_ENABLE | WATCH_JSON, NULL);
  for (i=0; i < 25; ++i) {
    if (gps_waiting(&gpsdata, 2000000)) {
      errno = 0;
      if (gps_read(&gpsdata) == -1) {
        fprintf(stderr, "gps_read() returned error '%s'\n",
          gps_errstr(errno));
      } else {
        /* Display data from the GPS receiver */
        // fprintf(stdout, "Received something\n");
        libgps_dump_state(&gpsdata);
      }
    } else {
      fprintf(stderr, "gps_waiting() returned false, so timeout or error\n");
      fprintf(stderr, "  error code was '%s'\n", gps_errstr(errno));
      exit(1);
    }
  }
  gps_stream(&gpsdata, WATCH_DISABLE, NULL);
  gps_close(&gpsdata);
  exit(0);
}

void libgps_dump_state(struct gps_data_t *collect) {
    FILE *debugfp = stdout;
    /* no need to dump the entire state, this is a sanity check */
#ifndef USE_QT
    /* will fail on a 32-bit machine */
    (void)fprintf(debugfp, "flags: (0x%04x) %s\n",
          (unsigned int)collect->set, gps_maskdump(collect->set));
#endif
    if (collect->set & ONLINE_SET)
    (void)fprintf(debugfp, "ONLINE: %lf\n", collect->online);
    if (collect->set & TIME_SET)
    (void)fprintf(debugfp, "TIME: %lf\n", collect->fix.time);
    if (collect->set & LATLON_SET)
    (void)fprintf(debugfp, "LATLON: lat/lon: %lf %lf\n",
              collect->fix.latitude, collect->fix.longitude);
    if (collect->set & ALTITUDE_SET)
    (void)fprintf(debugfp, "ALTITUDE: altitude: %lf  U: climb: %lf\n",
              collect->fix.altitude, collect->fix.climb);
    if (collect->set & SPEED_SET)
    (void)fprintf(debugfp, "SPEED: %lf\n", collect->fix.speed);
    if (collect->set & TRACK_SET)
    (void)fprintf(debugfp, "TRACK: track: %lf\n", collect->fix.track);
    if (collect->set & CLIMB_SET)
    (void)fprintf(debugfp, "CLIMB: climb: %lf\n", collect->fix.climb);
    if (collect->set & STATUS_SET) {
    const char *status_values[] = { "NO_FIX", "FIX", "DGPS_FIX" };
    (void)fprintf(debugfp, "STATUS: status: %d (%s)\n",
              collect->status, status_values[collect->status]);
    }
    if (collect->set & MODE_SET) {
    const char *mode_values[] = { "", "NO_FIX", "MODE_2D", "MODE_3D" };
    (void)fprintf(debugfp, "MODE: mode: %d (%s)\n",
              collect->fix.mode, mode_values[collect->fix.mode]);
    }
    if (collect->set & DOP_SET)
    (void)fprintf(debugfp,
              "DOP: satellites %d, pdop=%lf, hdop=%lf, vdop=%lf\n",
              collect->satellites_used, collect->dop.pdop,
              collect->dop.hdop, collect->dop.vdop);
    if (collect->set & VERSION_SET)
    (void)fprintf(debugfp, "VERSION: release=%s rev=%s proto=%d.%d\n",
              collect->version.release,
              collect->version.rev,
              collect->version.proto_major,
              collect->version.proto_minor);
    if (collect->set & POLICY_SET)
    (void)fprintf(debugfp,
              "POLICY: watcher=%s nmea=%s raw=%d scaled=%s timing=%s, split24=%s pps=%s, devpath=%s\n",
              collect->policy.watcher ? "true" : "false",
              collect->policy.nmea ? "true" : "false",
              collect->policy.raw,
              collect->policy.scaled ? "true" : "false",
              collect->policy.timing ? "true" : "false",
              collect->policy.split24 ? "true" : "false",
              collect->policy.pps ? "true" : "false",
              collect->policy.devpath);
    if (collect->set & SATELLITE_SET) {
    struct satellite_t *sp;

    (void)fprintf(debugfp, "SKY: satellites in view: %d\n",
              collect->satellites_visible);
    for (sp = collect->skyview;
         sp < collect->skyview + collect->satellites_visible;
         sp++) {
        (void)fprintf(debugfp, "    %2.2d: %2.2d %3.3d %3.0f %c\n",
              sp->PRN, sp->elevation,
              sp->azimuth, sp->ss,
              sp->used ? 'Y' : 'N');
    }
    }
    if (collect->set & DEVICE_SET)
    (void)fprintf(debugfp, "DEVICE: Device is '%s', driver is '%s'\n",
              collect->dev.path, collect->dev.driver);
    if (collect->set & DEVICELIST_SET) {
    int i;
    (void)fprintf(debugfp, "DEVICELIST:%d devices:\n",
              collect->devices.ndevices);
    for (i = 0; i < collect->devices.ndevices; i++) {
        (void)fprintf(debugfp, "%d: path='%s' driver='%s'\n",
              collect->devices.ndevices,
              collect->devices.list[i].path,
              collect->devices.list[i].driver);
    }
    }

}
