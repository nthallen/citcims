#ifndef HORIBA_INT_H_INCLUDED
#define HORIBA_INT_H_INCLUDED

#include "horiba.h"

extern const char *horiba_path;

#ifdef __cplusplus

#include <string>
#include <vector>
#include "SerSelector.h"

class HoribaQuery {
  public:
    HoribaQuery();
    void format(unsigned short addr, short *resultp, double rscale,
        unsigned short smask, unsigned char sunit, const char *cmd, ...);
    std::string query;
    short *result;
    double scale;
    unsigned short mask;
    unsigned char unit;
};

class HoribaCmd : public Ser_Sel {
  public:
    HoribaCmd();
    ~HoribaCmd();
    int ProcessData(int flag);
    HoribaQuery *query();
  private:
    HoribaQuery HCquery;
};

class HoribaSer : public Ser_Sel {
  public:
    HoribaSer(const char *ser_dev, horiba_tm_t *data, HoribaCmd *HCmd);
    ~HoribaSer();
    int ProcessData(int flag);
    Timeout *GetTimeout();
  private:
    int parse_response();
    int bcc_ok(unsigned int from);
    HoribaCmd *Cmd;
    Timeout TO;
    horiba_tm_t *TMdata;
    std::vector<HoribaQuery> Qlist;
    HoribaQuery *CurQuery;
    unsigned int nq, qn, cmdq;
    enum Horiba_State {HS_Idle, HS_WaitResp} state;
};

#endif // __cplusplus

#endif
