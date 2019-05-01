#ifndef USERPKTS3_H_INCLUDED
#define USERPKTS3_H_INCLUDED

#include <time.h>

typedef struct __attribute__((__packed__)) {
  double Time;
  float VarG;
  float VarH;
} Keyword3_t;
extern Keyword3_t Keyword3;

typedef struct __attribute__((__packed__)) {
  double Time;
  float VarA;
  float VarB;
  float VarC;
  float VarD;
} Keyword_t;
extern Keyword_t Keyword;

typedef struct __attribute__((__packed__)) {
  double Time;
  float VarE;
  float VarF;
} Keyword2_t;
extern Keyword2_t Keyword2;

#endif
