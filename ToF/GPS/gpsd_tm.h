/* gpsd_tm.h */
#ifndef GPSD_TM_H_INCLUDED
#define GPSD_TM_H_INCLUDED

  typedef struct __attribute__((__packed__)) {
    double time; // unix seconds with fractional part
    double ept; // timestamp error as %
    double lat; // degrees +N 9 decimal places
    double epy; // meters latitude error
    double lon; // degrees +E 9 decimal places
    double epx; // meters longitude error
    double alt; // meters
    double epv; // meters altitude error
    double track; // track over ground degrees from true north
    double epd; // track error, degrees
    double speed; // speed over ground, m/s
    double eps; // speed error est. m/s
    double climb; // m/s
    double epc;  // climb error est. m/s
    unsigned long real_sec;
    unsigned long real_nsec;
    unsigned long clock_sec;
    unsigned long clock_nsec;
    unsigned short data_status;
    unsigned short data2_status;
    unsigned char err_status;
    unsigned char err2_status;
    unsigned char mode; // 0-3
    unsigned char satellites_visible; // was int, but srsly?
    unsigned char satellites_used; // was 
  } gpsd_tm_t;

  /* Values for data_status and data2_status: */
  #define DATA_PACKET (1<<0) // PACKET_SET
  #define DATA_STATUS (1<<1) // STATUS_SET
  #define DATA_TIME   (1<<2) // TIME_SET
  #define DATA_LATLON (1<<3) // LATLON_SET
  #define DATA_ALT    (1<<4) // ALTITUDE_SET
  #define DATA_SPEED  (1<<5) // SPEED_SET
  #define DATA_TRACK  (1<<6) // TRACK_SET
  #define DATA_CLIMB  (1<<7) // CLIMB_SET
  #define DATA_MODE   (1<<8) // MODE_SET
  #define DATA_DOP    (1<<9) // DOP_SET (satellites_used, etc.)
  #define DATA_SATS   (1<<10) // SATELLITE_SET (satellites_visible)
  #define DATA_TOFF   (1<<11) // TOFF_SET (real_*, clock_*)
  #define DATA_PPS    (1<<12) // PPS_SET (real_*, clock_*)
  
  /* Values for err_status and err2_status: */
  #define ERR_TIME    (1<<0) // TIMERR_SET (time)
  #define ERR_HERR    (1<<1) // HERR_SET (epx, epy)
  #define ERR_VERR    (1<<2) // VERR_SET (epv)
  #define ERR_SPEED   (1<<3) // SPEEDERR_SET (eps)
  #define ERR_TRACK   (1<<4) // TRACKERR_SET (epd)
  #define ERR_CLIMB   (1<<5) // CLIMBERR_SET (epc)
  #define ERR_ERROR   (1<<6) // ERROR_SET (value reported in log)
#endif
