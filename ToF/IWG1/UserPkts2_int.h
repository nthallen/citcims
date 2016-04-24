#ifndef USERPKTS_INT_H_INCLUDED
#define USERPKTS_INT_H_INCLUDED

#include <math.h>
#include <stdarg.h>
#include "UserPkts2.h"

#ifdef __cplusplus
  extern "C" {
#endif
extern void pkts_init_options(int argc, char **argv);
#ifdef __cplusplus
  };
#endif

#ifdef __cplusplus

#include "SerSelector.h"

class UserPkt {
  public:
    UserPkt(const char *KW_in);
    ~UserPkt();
    int Process_Pkt(unsigned char *s, unsigned nc);
    virtual int Process_Pkt() = 0;
    void report_err(const char *fmt, ...);
    void report_ok();
    const char *KW;
    send_id TM_id;
  protected:
    unsigned char *buf;
    unsigned int nc;
    unsigned int cp;
    unsigned int n_errors;
    unsigned int n_suppressed;
    unsigned int total_errors;
    unsigned int total_suppressed;
    void TM_init(void *data, unsigned short size);
    int not_ndigits(int n, int &value);
    int not_str(const char *str, unsigned int len);
    int not_ISO8601(double *Time, bool w_hyphens = true);
    int not_double(double *value);
    int not_float(float *value);
    int not_nfloat(float *value, float NaNval = 999999.);
    int not_uchar(unsigned char &val);
    int not_int(int &val);
};

class AVOCETpkt : public UserPkt {
  public:
    AVOCETpkt();
    int Process_Pkt();
  private:
    AVOCET_t AVOCET;
};

class DACOMpkt : public UserPkt {
  public:
    DACOMpkt();
    int Process_Pkt();
  private:
    DACOM_t DACOM;
};

class DLHpkt : public UserPkt {
  public:
    DLHpkt();
    int Process_Pkt();
  private:
    DLH_t DLH;
};

class TDLIFpkt : public UserPkt {
  public:
    TDLIFpkt();
    int Process_Pkt();
  private:
    TDLIF_t TDLIF;
};

class NOxyO3pkt : public UserPkt {
  public:
    NOxyO3pkt();
    int Process_Pkt();
  private:
    NOxyO3_t NOxyO3;
};

class UserPkts {
  public:
    UserPkts();
    ~UserPkts();
    std::vector<UserPkt*> Pkts;
};

class UserPkts_UDP : public Ser_Sel {
  public:
    UserPkts_UDP(int udp_port, UserPkts *PktDefs);
    int ProcessData(int flag);
  private:
    void Bind(int port);
    int fillbuf();
    int not_KW(char *KWbuf);
    UserPkts *Pkts;
    // send_id LARGE_id;
    // int Process_LARGE();
    // LARGE_t LARGE;
    // send_id MMS_id;
    // int Process_MMS();
    // MMS_t MMS;
    // send_id NOAA_HSP2_id;
    // int Process_NOAA_HSP2();
    // NOAA_HSP2_t NOAA_HSP2;
    // send_id NOAA_SP2_id;
    // int Process_NOAA_SP2();
    // NOAA_SP2_t NOAA_SP2;
    // send_id NOyO3_id;
    // int Process_NOyO3();
    // NOyO3_t NOyO3;
};

#endif // __cplusplus
#endif // USERPKTS_INT_H_INCLUDED
