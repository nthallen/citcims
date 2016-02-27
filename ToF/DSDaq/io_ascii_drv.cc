#include <errno.h>
#include <strings.h>
#include "io_ascii_drv.h"
#include "dsdaqmsg.h"
#include "nortlib.h"
#include "tm.h"

int io_ascii_drv::Shutdown = 0;

int io_ascii_drv_io_write(resmgr_context_t *ctp, io_write_t *msg,
               RESMGR_OCB_T *ocb) {
  char buf[81];
  int nb, nbmr;
  int status;

  status = iofunc_write_verify(ctp, msg, ocb, NULL);
  if (status != EOK) return (status);
  if ((msg->i.xtype & _IO_XTYPE_MASK) != _IO_XTYPE_NONE)
      return(ENOSYS);
  nb = msg->i.nbytes;
  _IO_SET_WRITE_NBYTES (ctp, nb);
  nbmr = resmgr_msgread(ctp, buf, nb, sizeof(msg->i));
  if ( nbmr < 0 ) {
    nl_error(2, "Error on resmgr_msgread in io_ascii_drv_io_write(): %s",
	  strerror(errno));
  } else if (nbmr != nb) {
    nl_error(2, "resmg_msgread returned %d, expected %d", nbmr, nb );
  } else {
    buf[nb] = '\0';
    if (io_ascii_drv::inst) io_ascii_drv::inst->parse_ascii(&buf[0]);
  }
  return (_RESMGR_NPARTS (0));
}

/**
 * Status return to sender of 0 is success, 1 is failure. Other status
 * values may be determined in the future.
 */
int io_ascii_drv_io_msg(resmgr_context_t *ctp, io_msg_t *msg,
               RESMGR_OCB_T *ocb) {
  dsdaq_req_t dsdaq_req;
  int nb, nb_exp, rsize, rv = 0;
  dsdaq_rep_t dsdaq_rep;

  // I include the io_msg_t header in this read to do some sanity checking,
  // but I could probably skip it and reorganize my message structure.
  nb = resmgr_msgread(ctp, &dsdaq_req, sizeof(dsdaq_req), 0); 
  if ( nb < 0 ) {
    nl_error( 2, "Error from resmgr_msgread: %s", strerror(errno));
    return ENOSYS;
  }
  if ( (unsigned) nb < sizeof(dsdaq_req_hdr_t) ||
       dsdaq_req.hdr.iohdr.mgrid != DSDAQ_MGRID ||
       dsdaq_req.hdr.dsdaq_kw != DSDAQ_KW ||
       dsdaq_req.hdr.n_req > DSDAQ_MAX_ARGS)
    return ENOSYS;
  nb_exp = sizeof(dsdaq_req_hdr_t)+dsdaq_req.hdr.n_req*sizeof(unsigned short);
  if ( nb != nb_exp )
    nl_error( 1, "Invalid message length: Expected %d received %d",
      nb_exp, nb );
  dsdaq_rep.hdr.n_data = 0;
  rsize = sizeof(dsdaq_rep_hdr_t);
  switch (dsdaq_req.hdr.command) {
    case DSDAQ_READ:
      dsdaq_rep.hdr.n_data = dsdaq_req.hdr.n_req;
      rsize += dsdaq_rep.hdr.n_data*sizeof(unsigned short);
      rv = io_ascii_drv::inst ?
	io_ascii_drv::inst->mread( dsdaq_req.hdr.n_req, &dsdaq_req.data[0],
		&dsdaq_rep.data[0] ) :
	1;
      break;
    case DSDAQ_WRITE:
      rv = io_ascii_drv::inst ?
	    io_ascii_drv::inst->mwrite( dsdaq_req.hdr.n_req, &dsdaq_req.data[0] ) :
	    1;
      break;
    case DSDAQ_QUIT:
      io_ascii_drv::quit();
      break;
    default:
      nl_error( 4, "Invalid dsdaq request: %d", dsdaq_req.hdr.command );
  }
  // status return to sender is the second arg here:
  rv = MsgReply( ctp->rcvid, rv, &dsdaq_rep, rsize );
  return (_RESMGR_NOREPLY);
}

void sigint_handler( int sig ) {
  io_ascii_drv::quit();
}

io_ascii_drv *io_ascii_drv::inst = 0;

io_ascii_drv::io_ascii_drv(const char *name) {
  /* initialize resource manager attributes */
  memset(&resmgr_attr, 0, sizeof resmgr_attr);
  resmgr_attr.nparts_max = 1;
  resmgr_attr.msg_max_size = 2048;

  /* initialize functions for handling messages */
  iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &connect_funcs, 
                   _RESMGR_IO_NFUNCS, &io_funcs);

  io_funcs.msg = io_ascii_drv_io_msg;
  io_funcs.write = io_ascii_drv_io_write;

  /* initialize attribute structure used by the device */
  iofunc_attr_init(&attr, S_IFNAM | 0666, 0, 0);
  id = -1;
  path = nl_strdup(tm_dev_name( name ));
  dpp = NULL;
  ctp = NULL;
}

/**
 * Attaches to the device path, initializes the singleton instance pointer
 * and sets up signal handlers for SIGINT and SIGHUP.
 * @return non-zero on error
 */
int io_ascii_drv::init() {
  if (inst) nl_error(4, "More than one instance of io_ascii_drv");
  inst = this;
  
  /* initialize dispatch interface */
  if((dpp = dispatch_create()) == NULL) {
    nl_error(3, "Unable to allocate dispatch handle");
    return 1;
  }

  /* attach our device name */
  id = resmgr_attach(
          dpp,            /* dispatch handle        */
          &resmgr_attr,   /* resource manager attrs */
          path,        /* device name            */
          _FTYPE_ANY,     /* open type              */
          0,              /* flags                  */
          &connect_funcs, /* connect routines       */
          &io_funcs,      /* I/O routines           */
          &attr);         /* handle                 */
  if (id == -1)
      nl_error( 3, "Unable to attach name '%s': %s", path, strerror(errno) );

  nl_error( 0, "%s Initialized", path );

  signal( SIGINT, sigint_handler );
  signal( SIGHUP, sigint_handler );

  /* allocate a context structure */
  ctp = dispatch_context_alloc(dpp);
  return 0;
}

/**
 * @return non-zero on error
 */
int io_ascii_drv::operate() {
  /* start the resource manager message loop */
  while (1) {
    if((ctp = dispatch_block(ctp)) == NULL) {
      if (errno == EINTR) break;
      nl_error( 3, "block error: %s", strerror(errno));
      return 1;
    }
    dispatch_handler(ctp);
    if (Shutdown == 1 && ctp->resmgr_context.rcvid == 0
        && attr.count == 0)
      break;
  }
  nl_error( 0, "%s Shutting down", path );
  return 0;
}

io_ascii_drv::~io_ascii_drv() {
  if (id >= 0) {
    if ( resmgr_detach(dpp, id, _RESMGR_DETACH_ALL) )
      nl_error( 2, "Error detaching %s: %s", path, strerror(errno));
    id = -1;
  }
  if (dpp) {
    if ( dispatch_destroy(dpp) )
      nl_error( 2, "Error in dispatch_destroy(): %s", strerror(errno) );
    dpp = NULL;
  }
  if (ctp) {
    dispatch_context_free(ctp);
    ctp = NULL;
  }
  nl_free_memory(path);
  path = NULL;
}

void io_ascii_drv::parse_ascii(const char *ibuf) {
  nl_error( 0, "Received ascii command: '%s'",
	    ascii_escape(ibuf) );
  if ( ibuf[0] == '\0' ) quit();
}

/**
 * @return 0 on success.
 */
int io_ascii_drv::mread(int nr, unsigned short *addr, unsigned short *data) {
  int i, rv = 0;
  nl_error( 0, "io_mread( %d )", nr );
  for ( i = 0; i < nr; ++i ) {
    // report error on read from addr 0
    if ( addr[i] == 0 )
      rv = 1;
    // if ( read_operation(...) ) rv = 1;
    data[i] = addr[i];
  }
  return rv;
}

/**
 * @return 0 on success.
 */
int io_ascii_drv::mwrite(int nw, unsigned short *args) {
  int i, rv = 0;
  nl_error( 0, "io_mwrite( %d )", nw );
  for ( i = 0; i+2 <= nw; i += 2 ) {
    // report error on read from addr 0
    if ( args[i] == 0 )
      rv = 1;
    // if ( write_operation(...) ) rv = 1;
  }
  return rv;
}

void io_ascii_drv::quit() {
  Shutdown = 1;
}
