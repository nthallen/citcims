#ifndef IWG1_INT_H_INCLUDED
#define IWG1_INT_H_INCLUDED

#include <math.h>
#include "SerSelector.h"
#include "IWG1.h"

class IWG1_UDP : public Ser_Sel {
  public:
    IWG1_UDP();
    int ProcessData(int flag);
  private:
    void Bind(int port);
    int fillbuf();
    int not_ndigits(int n, int &value);
    int not_ISO8601(double *Time);
    int not_nfloat(float *value);
    send_id tm_id;
    IWG1_data_t IWG1;
};

#endif

// Port 5101 just IWG1 packets
// Port 7071 is the standard port, but for historical reasons, DC-8 uses 5101 as the primary.
// Instrument data comes on port 5110 in a format similar to IWG1:
// InstMnc,TIME,data,data,data,...,\r\n
