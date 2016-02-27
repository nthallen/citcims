/* Zeno.h Defines data structures for the Zeno */
#ifndef Zeno_H_INCLUDED
#define Zeno_H_INCLUDED

typedef struct __attribute__((__packed__)) {
  double         Time; /* seconds since epoch */
  signed   short WindSpeed; /* m/s */
  unsigned short WindDir; /* deg */
  signed   short WindSD; /* m/s */
  signed   short WindGust;
  signed   short Temp; /* C */
  unsigned short RH; /* % */
  signed   short SolarRadiance; /* W/m^2 */
  signed   short Press; /* hPa */
  unsigned short Rain; /* yes */
  signed   short VBatt; /* Volts */
  unsigned long BIT; /* Bits */
  unsigned char Lightning; /* yes */
} ZENO_TM_t;

extern ZENO_TM_t ZENO_TM;

#endif
