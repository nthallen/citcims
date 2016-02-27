#ifndef ATHENAII_H_INCLUDED
#define ATHENAII_H_INCLUDED

#include "dsdaqdrv.h"


/**
 * Provides methods specific to the AthenaII hardware.
 */
class AthenaII : public dsdaqdrv {
  public:
    AthenaII(int ad_se); // This probably needs more args...
    virtual ~AthenaII();
    void parse_ascii(const char *ibuf);
  protected:
    
  private:
    int n_ad;
    int n_dio;
    int n_bio;
    unsigned short da_values[4];
    unsigned char dio_values[3];
    int init_hardware();
    int ad_read(unsigned short offset, unsigned short &data);
    int da_read(unsigned short offset, unsigned short &data);
    int da_write(unsigned short offset, unsigned short value);
    int dio_read(unsigned short offset, unsigned short &data);
    int dio_write(unsigned short offset, unsigned short value);
    int bit_read(unsigned short offset, unsigned short &data);
    int bit_write(unsigned short offset, unsigned short value);
};

#endif
