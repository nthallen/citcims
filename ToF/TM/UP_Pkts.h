#ifndef UP_PKTS_H_INCLUDED
#define UP_PKTS_H_INCLUDED

#include "UP_int.h"

class ChemWADpkt : public UserPkt {
  public:
    ChemWADpkt();
    int Process_Pkt();
  private:
    ChemWAD_t ChemWAD;
};

#endif
