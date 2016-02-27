/* zaber.h Include file for public consumption */
#ifndef ZABER_H_INCLUDED
#define ZABER_H_INCLUDED


#define N_DRIVES 2
typedef unsigned char drv_t;
typedef struct __attribute__((__packed__)) {
  drv_t drive;
  drv_t cmd;
  long int value;
} zaber_cmd;

/* This is the format of the data that is sent to
   Telemetry */
typedef struct __attribute__((__packed__)) {
  long int position;
  short int PS_voltage;
  unsigned char zero;
} zaber_tm_t;

typedef struct __attribute__((__packed__)) {
  zaber_tm_t drive[N_DRIVES];
} zaber_tms_t;

extern const char *zaber_port;

#ifdef __cplusplus
  extern "C" {
#endif
    extern void zaber_init_options(int argc, char **argv);
#ifdef __cplusplus
  };
#endif


#endif
