/* SWData.h */
#ifndef SWDATA_H_INCLUDED
#define SWDATA_H_INCLUDED

typedef struct __attribute__((__packed__)) {
  unsigned char SWStat;
  unsigned char SWFlow;
  float InP_Pgain;
  float InP_igain;
  signed short InPset;
} SWData_t;
extern SWData_t SWData;

#define SWS_FLOWSTATE_OFF 1
#define SWS_TURBOS_ON 90
#define SWS_TURBOS_OFF 91
#define SWS_PUMPS_ON 96
#define SWS_PUMPS_OFF 97
#define SWS_INLET_PCTRL 100
#define SWS_INLET_IDLE 101
#define SWS_INLET_LAB 102
#define SWS_TOF_START 110
#define SWS_TOF_STOP 111
#define SWS_DATA_LOOP 115
#define SWS_DATA_STOP 116
#define SWS_DATA_LP_NC 117
#define SWS_DATA_QC 118
#define SWS_QUICK_SHUTDOWN 254
#define SWS_SHUTDOWN 255

#endif
