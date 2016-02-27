#ifndef DSDAQMSG_H_INCLUDED
#define DSDAQMSG_H_INCLUDED
#include <sys/iomsg.h>

typedef struct __attribute__((__packed__)) {
  struct _io_msg iohdr;
  /**
   * A sanity check word.
   */
  unsigned short dsdaq_kw;
  /**
   * commands encoded as as dsdaq_cmd values.
   */
  unsigned short command;
  /**
   * The number of unsigned short words in the request. For write operations
   * this is twice the number of writes, and the data includes interleaved
   * address and data.
   */
  unsigned short n_req;
} dsdaq_req_hdr_t;

#define DSDAQ_MGRID_OFFSET 3
#define DSDAQ_MGRID (_IOMGR_PRIVATE_BASE + DSDAQ_MGRID_OFFSET)

/* dsdaq_kw value */
#define DSDAQ_KW 0x4453

/* command values */
enum dsdaq_cmd { DSDAQ_READ, DSDAQ_WRITE, DSDAQ_QUIT };

#define DSDAQ_MAX_ARGS 50

typedef struct __attribute__((__packed__)) {
  dsdaq_req_hdr_t hdr;
  unsigned short data[DSDAQ_MAX_ARGS];
} dsdaq_req_t;

typedef struct __attribute__((__packed__)) {
  dsdaq_req_hdr_t hdr;
  unsigned short data[2];
} dsdaq_req1_t;

typedef struct __attribute__((__packed__)) {
  unsigned short n_data;
} dsdaq_rep_hdr_t;

typedef struct __attribute__((__packed__)) {
  dsdaq_rep_hdr_t hdr;
  unsigned short data[DSDAQ_MAX_ARGS];
} dsdaq_rep_t;

typedef struct __attribute__((__packed__)) {
  dsdaq_rep_hdr_t hdr;
  unsigned short data[1];
} dsdaq_rep1_t;

#endif
