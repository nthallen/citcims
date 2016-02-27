/* SWData.h */
#ifndef SWDATA_H_INCLUDED
#define SWDATA_H_INCLUDED

typedef struct __attribute__((__packed__)) {
  unsigned char SWStat;
  unsigned short VarSeq;
  unsigned short VarStat;
} SWData_t;
extern SWData_t SWData;


#endif
