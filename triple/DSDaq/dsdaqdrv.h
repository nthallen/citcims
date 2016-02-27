#ifndef DSDAQDRV_H_INCLUDED
#define DSDAQDRV_H_INCLUDED

#include "io_ascii_drv.h"

/** These definitions support the address space mapping. */
#define DSDADDR_TYPE 0xF000
#define DSDADDR_OFFSET 0x0FFF
#define DSDADDR_AD   0x1000
#define DSDADDR_DA   0x2000
#define DSDADDR_DIO  0x3000
#define DSDADDR_BIO  0x4000

/**
 * dsdaqdrv provides some general architecture specific structure
 * on top of the hardware-agnostic io_ascii_drv class. Subclasses
 * will be created for specific hardware.
 */
class dsdaqdrv : public io_ascii_drv {
  public:
    dsdaqdrv(const char *name); // This probably needs more args...
    void parse_ascii(const char *ibuf);
    int init();
    int mread(int nr, unsigned short *addr, unsigned short *data);
    int mwrite(int nw, unsigned short *args);
    virtual ~dsdaqdrv();
  protected:
    unsigned short base;
  private:
    virtual int init_hardware();
    virtual int ad_read(unsigned short offset, unsigned short &data);
    virtual int ad_write(unsigned short offset, unsigned short value);
    virtual int da_read(unsigned short offset, unsigned short &data);
    virtual int da_write(unsigned short offset, unsigned short value);
    virtual int dio_read(unsigned short offset, unsigned short &data);
    virtual int dio_write(unsigned short offset, unsigned short value);
    virtual int bit_read(unsigned short offset, unsigned short &data);
    virtual int bit_write(unsigned short offset, unsigned short value);
};

#endif
