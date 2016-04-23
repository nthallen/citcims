#ifndef USERPKTS_INT_H_INCLUDED
#define USERPKTS_INT_H_INCLUDED

#include <math.h>
#include "SerSelector.h"
#include "UserPkts.h"

class UserPkts_UDP : public Ser_Sel {
  public:
    UserPkts_UDP();
    int ProcessData(int flag);
  private:
    void Bind(int port);
    int fillbuf();
    int not_ndigits(int n, int &value);
    int not_ISO8601(double *Time);
    int not_nfloat(float *value, float NaNval = 999999.);
    int not_uchar(unsigned char &val);
    int not_KW(char *KWbuf);
    send_id AVOCET_id;
    int Process_AVOCET();
    AVOCET_t AVOCET;
    send_id DACOM_id;
    int Process_DACOM();
    DACOM_t DACOM;
    send_id DLH_id;
    int Process_DLH();
    DLH_t DLH;
    send_id LARGE_id;
    int Process_LARGE();
    LARGE_t LARGE;
    send_id MMS_id;
    int Process_MMS();
    MMS_t MMS;
    send_id NOAA_HSP2_id;
    int Process_NOAA_HSP2();
    NOAA_HSP2_t NOAA_HSP2;
    send_id NOAA_SP2_id;
    int Process_NOAA_SP2();
    NOAA_SP2_t NOAA_SP2;
    send_id NOyO3_id;
    int Process_NOyO3();
    NOyO3_t NOyO3;
};

#endif

// Port 5101 just IWG1 packets
// Port 7071 is the standard port, but for historical reasons, DC-8 uses 5101 as the primary.
// Instrument data comes on port 5110 in a format similar to IWG1:
// InstMnc,TIME,data,data,data,...,\r\n

// April 23, 2016: Prep for KORUS/ATOM
//   IWG1 is coming in on 7071
//   Instrument data is coming in on multiple UDP ports
