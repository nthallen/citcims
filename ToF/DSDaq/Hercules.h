#ifndef HERCULES_H_INCLUDED
#define HERCULES_H_INCLUDED

#include "dsdaqdrv.h"

typedef enum {
  HERC_SPARE,
  HERC_STRB,
  HERC_UNSTRB
} herccmdtype;

typedef struct {
  herccmdtype cmdtype;
  unsigned char portno;
  unsigned char mask;
  unsigned char value;
} dio_scdc_def;

/**
 * Provides methods specific to the Hercules hardware.
 */
class Hercules : public dsdaqdrv {
  public:
    Hercules(int ad_se); // This probably needs more args...
    virtual ~Hercules();
  protected:
    
  private:
    int n_ad;
    int n_dio;
    int n_bio;
    unsigned short dabu;
    unsigned short da_values[4];
    unsigned char dio_values[5];
    static dio_scdc_def scdc_def[];
    int init_hardware();
    int ad_read(unsigned short offset, unsigned short &data);
    int da_read(unsigned short offset, unsigned short &data);
    int da_write(unsigned short offset, unsigned short value);
    int dio_read(unsigned short offset, unsigned short &data);
    int dio_write(unsigned short offset, unsigned short value);
    int bit_read(unsigned short offset, unsigned short &data);
    int bit_write(unsigned short offset, unsigned short value);
};

#define HERC_AD_CHANNEL 0x1F
#define HERC_AD_GAIN 0x60
#define HERC_AD_UNIPOLAR 0x80
#define HERC_AD_DIFFERENTIAL 0x100
#define HERC_AD_OFFSET_MAX 0x1FF
#define HERC_DA_SU 0x80 // simultaneous update

#endif
