#ifndef USERPKTS_H_INCLUDED
#define USERPKTS_H_INCLUDED

#include <time.h>

typedef struct __attribute__((__packed__)) {
  double Time;
  float CO2; // ppb
} AVOCET_t;
extern AVOCET_t AVOCET;

typedef struct __attribute__((__packed__)) {
  double Time;
  float CO; // ppb
  float Methane; // ppb
} DACOM_t;
extern DACOM_t DACOM;

typedef struct __attribute__((__packed__)) {
  double Time;
  float WaterVapor; // ppm
} DLH_t;
extern DLH_t DLH;

typedef struct __attribute__((__packed__)) {
  double Time;
  float ColdCN; // #/cm^3
  float HotCN; // #/cm^3
  float Dry_Scattering; // Mm-1
} LARGE_t;
extern LARGE_t LARGE;

typedef struct __attribute__((__packed__)) {
  double Time;
  float TotalPressure; // mb
  float StaticPressure; // mb
  float Pitch; // deg
  float Roll; // deg
  float Heading; // deg
  float Vns; // m/s
  float Vew; // m/s
  float Vup; // m/s
  float Az; // m/s^2
  float MultiVariable;
} MMS_t;
extern MMS_t MMS;

typedef struct __attribute__((__packed__)) {
  double Time;
  float HSP2_IncParticleCount; //	#/cc
  unsigned char Status;
} NOAA_HSP2_t;
extern NOAA_HSP2_t NOAA_HSP2;

typedef struct __attribute__((__packed__)) {
  double Time;
  float SP2_IncParticleCount; // #/cc
  unsigned char Status;
} NOAA_SP2_t;
extern NOAA_SP2_t NOAA_SP2;

typedef struct __attribute__((__packed__)) {
  double Time;
  float NO; // ppb
  float NOy; // ppb
  float O3; // ppb
} NOyO3_t;
extern NOyO3_t NOyO3;

#endif
