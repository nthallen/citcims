#ifndef IONGAUGE_INT_H_INCLUDED
#define IONGAUGE_INT_H_INCLUDED

#include "IonGauge.h"

#ifdef __cplusplus

#include "SerSelector.h"

enum IG_next { Q1, R1, Q2, R2 };

class IonGauge : public Ser_Sel {
  public:
    IonGauge( const char *path, IonGauge_t *data );
    int ProcessData(int flag);
  private:
    void IssueQuery(bool synch);
    void FlushInput();
    IG_next state;
    bool query_pending;
    IonGauge_t *TMdata;
};

#endif

#endif
