#ifndef SONIC_H_INCLUDED
#define SONIC_H_INCLUDED

typedef struct {
  float U;
  float V;
  float W;
  float C;
  unsigned char N;
  unsigned char Status;
} SonicData_t;

/* Status byte bit values: */
#define CSAT_MISSED_REC 0x10
#define CSAT_B15 0x8
#define CSAT_B14 0x4
#define CSAT_B13 0x2
#define CSAT_B12 0x1

#ifdef __cplusplus
extern "C" {
#endif
  extern void sonic_init_options( int argc, char **argv );
#ifdef __cplusplus
};
#endif

#ifdef __cplusplus

#include <termios.h>
#include "SerSelector.h"

class SonicDriver;

class Sonic_TM : public TM_Selectee {
  public:
    Sonic_TM();
    ~Sonic_TM();
    int ProcessData(int flag);
    void RecordData(const unsigned char *sonic_buf);
  private:
    SonicData_t SonicData;
    void clear_TM();
    void finalize_avg();
    float convert_raw(const unsigned char *buf, int idx, int bits);
};

class Sonic : public Ser_Sel {
  public:
    Sonic();
    ~Sonic();
    void Sonic_init(const char *port, SonicDriver *Drv);
    int ProcessData(int flag);
  private:
    static const unsigned int nb_rec = 12;
    SonicDriver *Driver;
    termios termios_m;
};

class SonicDriver : public Selector {
  public:
    SonicDriver(const char *port);
    ~SonicDriver();
    inline void RecordData(const unsigned char *sonic_buf) {
      TM.RecordData(sonic_buf);
    };
  private:
    Sonic_TM TM;
    Sonic Serial;
    Cmd_Selectee Cmd;
};

#endif

#endif
