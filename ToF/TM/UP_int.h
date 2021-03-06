#ifndef USERPKTS3_INT_H_INCLUDED
#define USERPKTS3_INT_H_INCLUDED

#include <math.h>
#include <stdarg.h>
#include "UP.h"

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
    int Process_Pkt(unsigned char *s, unsigned nc, unsigned cp);
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
    int not_fptext();
    int not_double(double *value);
    int not_float(float *value);
    int not_nfloat(float *value, float NaNval = 999999.);
    int not_uchar(unsigned char &val);
    int not_int(int &val);
};

class UserPkts_UDP : public Ser_Sel {
  public:
    UserPkts_UDP(int udp_port);
    int ProcessData(int flag);
    inline void add_packet(UserPkt *pkt) { Pkts.push_back(pkt); }
  private:
    void Bind(int port);
    int fillbuf();
    int not_KW(char *KWbuf);
    std::vector<UserPkt *> Pkts;
};

class UserPkts {
  public:
    UserPkts(Selector *S); // generated
    ~UserPkts();
  private:
    std::vector<UserPkts_UDP*> UDPs;
};

#endif // __cplusplus
#endif // USERPKTS_INT_H_INCLUDED
