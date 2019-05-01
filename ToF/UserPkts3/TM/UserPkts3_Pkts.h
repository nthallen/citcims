#ifndef USERPKTS3_PKTS_H_INCLUDED
#define USERPKTS3_PKTS_H_INCLUDED

#include "UserPkts3_int.h"

class Keyword3pkt : public UserPkt {
  public:
    Keyword3pkt();
    int Process_Pkt();
  private:
    Keyword3_t Keyword3;
};

class Keywordpkt : public UserPkt {
  public:
    Keywordpkt();
    int Process_Pkt();
  private:
    Keyword_t Keyword;
};

class Keyword2pkt : public UserPkt {
  public:
    Keyword2pkt();
    int Process_Pkt();
  private:
    Keyword2_t Keyword2;
};

#endif
