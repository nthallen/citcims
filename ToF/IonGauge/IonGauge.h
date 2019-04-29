#ifndef IONGAUGE_H_INCLUDED
#define IONGAUGE_H_INCLUDED

typedef struct __attribute__((__packed__)) {
  float Hex_P;
  float ToF_P;
  unsigned char IG_stat;
} IonGauge_t;

#define IG_PRESENT 1 
#define IG_HEX_P_FRESH 2
#define IG_TOF_P_FRESH 4

extern const char *iongauge_path;
extern int channel_1_enable;
extern int channel_2_enable;

#endif
