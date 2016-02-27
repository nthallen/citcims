#ifndef DSDAQ_H_INCLUDED
#define DSDAQ_H_INCLUDED

#include <sys/neutrino.h>
#include <stdarg.h>
#include <time.h>
#include "dsdaqmsg.h"

class dsdaq_req;

/**
 * Class for clients of DSDaq Drivers.
 */
class dsdaq {
  public:
    dsdaq(const char *path, const char *node = 0);
    ~dsdaq();
    void init();
    int read(unsigned short addr, unsigned short &data);
    unsigned short read(unsigned short addr);
    int write(unsigned short addr, unsigned short data);
    int sendv(iov_t *siov, int nw_expected = 0, unsigned short *data = NULL);
    dsdaq_req *pack( dsdaq_cmd rtype, int n_arg, ... );
    inline unsigned char status() { return stat; }
  private:
    int connect(int first = 0);
    void lost_connection();
    unsigned char stat;
    int fd;
    char *devpath;
    time_t next_attempt;
    dsdaq_req1_t rdreq;
    dsdaq_req1_t wrreq;
    dsdaq_rep_hdr_t rep;
    iov_t rd_siov, wr_siov, riov[2];
};

enum dsdaq_status { dsdaq_uninit, dsdaq_init, dsdaq_conn };

/**
 * Class for pre-allocated requests (multi-read). Can be used for
 * multi-write as well, but I haven't come up with a use case.
 */
class dsdaq_req {
  public:
    dsdaq_req( dsdaq *ds_in, dsdaq_cmd rtype, int n_arg, va_list args );
    int send( unsigned short *data = NULL );
  private:
    dsdaq_req_t *req;
    iov_t siov;
    int nw_expected;
    dsdaq *ds;
};

#endif
