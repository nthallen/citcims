#include "oui.h"
#include "nortlib.h"
#include "dsdaqdrv.h"

/* This is a demonstration module to test the dsdaqdrv library */

class dsd : public dsdaqdrv {
  public:
    dsd();
    virtual ~dsd();
  private:
    int ad_read(unsigned short offset, unsigned short &data);
};

dsd::dsd() : dsdaqdrv("AthenaII") {
}

dsd::~dsd() {}

int dsd::ad_read(unsigned short offset, unsigned short &data) {
  nl_error( -2, "mread(0x%X)", offset );
  data = offset;
  return 0;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { dsd dsdrv;
    dsdrv.init();
    dsdrv.operate();
  }
}
