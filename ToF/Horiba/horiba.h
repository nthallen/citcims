#ifndef HORIBA_H_INCLUDED
#define HORIBA_H_INCLUDED

typedef struct __attribute__((__packed__)) {
  short DilFlowSP;
  short DilFlow;
  short IonSrcFlowSP;
  short IonSrcFlow;
  short FFlowSP;
  short FFlow;
  short HoribaPSP;
  short HoribaP;
  unsigned short HoribaS; // Status word
} horiba_tm_t;

#define DILFLOWSP_S 0x01
#define DILFLOW_S 0x02
#define IONSRCFLOWSP_S 0x04
#define IONSRCFLOW_S 0x08
#define FFLOWSP_S 0x10
#define FFLOW_S 0x20
#define HORIBAPSP_S 0x40
#define HORIBAP_S 0x80
#define HORIBA_CMD_S 0x100

extern horiba_tm_t Horiba;

#endif

