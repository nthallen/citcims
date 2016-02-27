#ifndef IO_ASCII_DRV_H_INCLUDED
#define IO_ASCII_DRV_H_INCLUDED

#include <sys/iofunc.h>
#include <sys/dispatch.h>

/**
 * io_ascii_drv is a class to abstract a basic read/write driver that also
 * supports an ascii write interface. I have kept it completely
 * hardware agnostic to make it easier to reuse.
 */
class io_ascii_drv {
  public:
    io_ascii_drv(const char *name);
    int init(); // actually register with the OS
    int operate();
    virtual void parse_ascii(const char *ibuf);
    /**
     * @param nr The number of read requests
     * @param addr Array of addresses to read from
     * @param data Array where read results will be written
     * @return zero on success, non-zero on any error
     */
    virtual int mread(int nr, unsigned short *addr, unsigned short *data);
    /**
     * @param nw The number of arguments, which should be twice the
     * number of writes
     * @param args Interleaved address and data
     * @return zero on success, non-zero on any error
     */
    virtual int mwrite(int nw, unsigned short *args);
    static void quit();
    virtual ~io_ascii_drv();
    static io_ascii_drv *inst;
  private:
    resmgr_connect_funcs_t connect_funcs;
    resmgr_io_funcs_t io_funcs;
    iofunc_attr_t attr;
    resmgr_attr_t resmgr_attr;
    dispatch_t *dpp;
    dispatch_context_t *ctp;
    static int Shutdown;
    int id;
    char *path;
};

extern "C" {
  int io_ascii_drv_io_write(resmgr_context_t *ctp, io_write_t *msg,
               RESMGR_OCB_T *ocb);
  void sigint_handler( int sig );
  int io_ascii_drv_io_msg(resmgr_context_t *ctp, io_msg_t *msg,
               RESMGR_OCB_T *ocb);
};

#endif
