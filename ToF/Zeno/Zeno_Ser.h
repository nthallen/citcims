#ifndef ZENO_SER_INT_H_INCLUDED
#define ZENO_SER_INT_H_INCLUDED

#include <math.h>
#include "Zeno.h"

#ifdef __cplusplus

#include "SerSelector.h"

class Zeno_Ser : public Ser_Sel {
  public:
    Zeno_Ser( const char *path );
    int ProcessData(int flag);
  private:
    int not_ndigits(int n, int &value);
    int not_fix(int n, signed short &val);
    int not_ushort(unsigned short &val);
    int not_zeno_time(double &Time);
    int not_hex(unsigned long &hex);
    send_id tm_id;
    ZENO_TM_t ZENO_TM;
};

#endif

extern const char *zeno_path;

#endif
