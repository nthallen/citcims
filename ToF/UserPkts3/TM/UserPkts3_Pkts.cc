#include "UserPkts3_Pkts.h"

Keyword3pkt::Keyword3pkt() : UserPkt("Keyword3") {
  TM_init(&Keyword3, sizeof(Keyword3_t));
}

int Keyword3pkt::Process_Pkt() {
  return (
    not_double(&Keyword3.Time) || not_str(",", 1) ||
    not_nfloat(&Keyword3.VarG) || not_str(",", 1) ||
    not_nfloat(&Keyword3.VarH)
  );
}

Keywordpkt::Keywordpkt() : UserPkt("Keyword") {
  TM_init(&Keyword, sizeof(Keyword_t));
}

int Keywordpkt::Process_Pkt() {
  return (
    not_double(&Keyword.Time) || not_str(",", 1) ||
    not_nfloat(&Keyword.VarA) || not_str(",", 1) ||
    not_nfloat(&Keyword.VarB) || not_str(",", 1) ||
    not_nfloat(&Keyword.VarC) || not_str(",", 1) ||
    not_nfloat(&Keyword.VarD)
  );
}

Keyword2pkt::Keyword2pkt() : UserPkt("Keyword2") {
  TM_init(&Keyword2, sizeof(Keyword2_t));
}

int Keyword2pkt::Process_Pkt() {
  return (
    not_ISO8601(&Keyword2.Time, false) || not_str(",", 1) ||
    not_nfloat(&Keyword2.VarE) || not_str(",", 1) ||
    not_nfloat(&Keyword2.VarF)
  );
}

#endif
