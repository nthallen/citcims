#include "dsdaq.h"
#include "tm.h"
#include "nortlib.h"
#include "nl_assert.h"

dsdaq::dsdaq(const char *path, const char *node) {
  const char *devname = tm_dev_name(path);
  if (node) {
    int pathlen = snprintf( 0, 0, "/net/%s%s", node, devname );
    devpath = (char *)nl_new_memory(pathlen+1);
    snprintf( devpath, pathlen+1, "/net/%s%s", node, devname );
  } else {
    devpath = nl_strdup(devname);
  }
  fd = -1;
  stat = dsdaq_init;
  
  // Setup Read structures
  SETIOV(&rd_siov, &rdreq, sizeof(dsdaq_req_hdr_t) + sizeof(unsigned short));
  SETIOV(&riov[0], &rep, sizeof(dsdaq_rep_hdr_t) );
  rdreq.hdr.iohdr.type = _IO_MSG;
  rdreq.hdr.iohdr.combine_len = 0;
  rdreq.hdr.iohdr.mgrid = DSDAQ_MGRID;
  rdreq.hdr.iohdr.subtype = 0;
  rdreq.hdr.dsdaq_kw = DSDAQ_KW;
  rdreq.hdr.command = DSDAQ_READ;
  rdreq.hdr.n_req = 1;
  
  // And write structures
  wrreq.hdr.iohdr.type = _IO_MSG;
  wrreq.hdr.iohdr.combine_len = 0;
  wrreq.hdr.iohdr.mgrid = DSDAQ_MGRID;
  wrreq.hdr.iohdr.subtype = 0;
  wrreq.hdr.dsdaq_kw = DSDAQ_KW;
  wrreq.hdr.command = DSDAQ_WRITE;
  wrreq.hdr.n_req = 2;
  SETIOV(&wr_siov, &wrreq, sizeof(wrreq) );
}

void dsdaq::init() {
  connect(1);
}

dsdaq::~dsdaq() {
  if ( fd >= 0 ) {
    close(fd);
    fd = -1;
  }
  if ( devpath ) {
    nl_free_memory(devpath);
    devpath = NULL;
  }
}

/**
 * @return non-zero on success.
 */
int dsdaq::connect(int first) {
  int nlr;
  if ( !first ) {
    if ( time(NULL) < next_attempt )
      return 0;
  }
  nlr = set_response(first ? MSG_WARN : 0);
  fd = tm_open_name(devpath, NULL, O_RDWR);
  set_response(nlr);
  if ( fd < 0 ) {
    if ( first ) {
      nl_error( 2, "Unable to contact driver %s: will retry", devpath );
    }
    next_attempt = time(NULL) + 10;
    return 0;
  } else if ( !first ) {
    nl_error( 0, "Re-established connection with %s", devpath );
  }
  stat = dsdaq_conn;
  return 1;
}

/**
 * Internal function called when we receive an error on the device.
 */
void dsdaq::lost_connection() {
  nl_error( 2, "Lost contact with %d: will attempt to reconnect", devpath );
  close(fd);
  fd = -1;
  stat = dsdaq_init;
  next_attempt = time(NULL) + 10;
}

int dsdaq::read(unsigned short addr, unsigned short &data) {
  rdreq.data[0] = addr;
  if (sendv(&rd_siov, 1, &data) ) return 1;
  if ( rep.n_data != 1 ) {
    nl_error( 2, "sendv returned %d, expected 1", rep.n_data );
  }
  return 0;
}

unsigned short dsdaq::read(unsigned short addr) {
  unsigned short data;
  return read(addr, data) ? 0 : data;
}

int dsdaq::write(unsigned short addr, unsigned short data) {
  wrreq.data[0] = addr;
  wrreq.data[1] = data;
  if ( sendv(&wr_siov ) ) return 1;
  if ( rep.n_data != 0 ) {
    nl_error( 2, "sendv returned %d, expected 0", rep.n_data );
  }
  return 0;
}

/**
 * @param nw_expected set on read operation to specify the size of
 * the data expected in the reply.
 * @return zero on success, non-zero on failure of any kind.
 */
int dsdaq::sendv(iov_t *siov, int nw_expected, unsigned short *data ) {
  int rparts, rv;
  if ( fd < 0 && !connect() ) return 1;
  if ( nw_expected > 0 ) {
    nl_assert(data != 0);
    SETIOV(&riov[1], data, nw_expected * sizeof(unsigned short) );
    rparts = 2;
  } else {
    rparts = 1;
  }
  rv = MsgSendv(fd, siov, 1, &riov[0], rparts);
  if ( rv < 0 ) {
    lost_connection();
    return 1;
  }
  if ( rep.n_data != nw_expected ) {
    nl_error( 2, "dsdaq::sendv expected %d words, received %d",
	      nw_expected, rep.n_data );
    return 1;
  }
  return rv;
}

/**
 * @param n_arg The number of arguments in the list. If rtype is DSDAQ_WRITE, there
 * should be two arguments for each write to cover both address and data.
 */
dsdaq_req *dsdaq::pack( dsdaq_cmd rtype, int n_arg, ... ) {
  dsdaq_req *dsr;
  va_list args;
  va_start( args, n_arg );
  dsr = new dsdaq_req( this, rtype, n_arg, args );
  va_end( args );
  return dsr;
}

/**
 * @param n_arg The number of arguments in the list. If rtype is DSDAQ_WRITE, there
 * should be two arguments for each write to cover both address and data.
 */
dsdaq_req::dsdaq_req( dsdaq *ds_in, dsdaq_cmd rtype, int n_arg, va_list args ) {
  int req_size, i;
  ds = ds_in;
  req_size = sizeof(dsdaq_req_hdr_t) + n_arg * sizeof(unsigned short);
  req = (dsdaq_req_t *)nl_new_memory( req_size );
  req->hdr.iohdr.type = _IO_MSG;
  req->hdr.iohdr.combine_len = 0;
  req->hdr.iohdr.mgrid = DSDAQ_MGRID;
  req->hdr.iohdr.subtype = 0;
  req->hdr.dsdaq_kw = DSDAQ_KW;
  req->hdr.command = rtype;
  req->hdr.n_req = n_arg;
  nw_expected = (rtype == DSDAQ_READ) ? n_arg : 0;
  for ( i = 0; i < n_arg; ++i ) {
    unsigned int arg = va_arg(args, unsigned int);
    req->data[i] = (unsigned short)arg;
  }
  SETIOV( &siov, req, req_size );
}

/**
 * @param data Where to store data if request is DSDAQ_READ.
 * @return zero on success, non-zero on failure of any kind.
 */
int dsdaq_req::send( unsigned short *data ) {
  return ds->sendv( &siov, nw_expected, data );
}

