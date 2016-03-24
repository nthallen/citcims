#include <errno.h>
#include <string.h>
#include "nortlib.h"
#include "nXDS.h"

nXDS_TM::nXDS_TM(nXDS_t *data, const char *remnode,
    const char *remexp)
  : Selectee() {
  TMid = 0;
  remote = 0;
  init(data, remnode, remexp);
}

nXDS_TM::nXDS_TM() : Selectee() {
  TMid = 0;
  remote = 0;
}

void nXDS_TM::init(nXDS_t *data, const char *remnode,
    const char *remexp) {
  if (remnode || remexp) {
    int nb;
    char *rmt = (char *)nl_new_memory(PATH_MAX);
    if (remexp == 0) {
      nb = snprintf(rmt, PATH_MAX, "/net/%s%s", remnode,
        tm_dev_name(NXDS_TM_NAME));
    } else {
      if (remnode) {
        nb = snprintf(rmt, PATH_MAX, "/net/%s/dev/huarp/%s/DG/data/%s",
          remnode, remexp, NXDS_TM_NAME);
      } else {
        nb = snprintf(rmt, PATH_MAX, "/dev/huarp/%s/DG/data/%s", remexp,
          NXDS_TM_NAME);
      }
    }
    if (nb >= PATH_MAX)
      nl_error(3, "Constructed path for remote experiment exceeds limit");
    remote = (const char *)rmt;
  }
  TM_data = data;
  Connect();
}

/**
 * Failure of the local connection is considered fatal.
 */
void nXDS_TM::Connect() {
  int save_response = set_response(remote ? 0 : nl_response);
  TMid = Col_send_init( remote ? remote : NXDS_TM_NAME, TM_data,
    sizeof(nXDS_t), 0 );
  if ( TMid ) {
    TO.Clear();
    fd = TMid->fd;
    flags = Selector::Sel_Write;
    if (remote) {
      nl_error(0, "TM connection established to %s", remote);
      flags |= Selector::Sel_Except;
    }
  } else {
    if (!TO.Set()) {
      nl_error(1, "TM connection failed to %s", remote);
    }
    TO.Set(10,0);
    flags = Selector::Sel_Timeout;
  }
  set_response(save_response);
}

/**
 * Issues Col_send_reset()
 */
nXDS_TM::~nXDS_TM() {
  if (TMid) {
    Col_send_reset(TMid);
    TMid = 0;
    fd = -1;
  }
}

/**
 * Calls Col_send() and sets gflag(0)
 */
int nXDS_TM::ProcessData(int flag) {
  const char *rem_text = remote ? "remote" : "local";
  if (TMid == 0 && TO.Expired()) {
    nl_error(0, "TMid==0, flag=%d", flag);
    Connect(); // Will either set TMid or TO
  }
  if ((flag & Selector::Sel_Except) ||
      (TMid && (flag & Selector::Sel_Write) && Col_send(TMid))) {
    if (flag&Selector::Sel_Except) {
      nl_error(0, "Closing %s TM connection due to Sel_Except. flags=%d, flag=%d", rem_text, flags, flag);
    } else {
      nl_error(0, "Closing %s TM connection due to Col_send() error", rem_text);
    }
    if (Col_send_reset(TMid)) {
      if (flag&Selector::Sel_Except) {
        nl_error(0, "Expected error closing %s TM connection: %s",
          remote ? "remote" : "local", strerror(errno));
      } else {
        nl_error(2, "Error closing %s TM connection: %s",
          remote ? "remote" : "local", strerror(errno));
      }
    }
    TMid = 0;
    fd = -1;
    if (remote) {
      TO.Set(10,0);
      flags = Selector::Sel_Timeout;
      return 0;
    } else {
      flags = 0;
      nl_error(0, "Connection to local TM closed");
      return 1;
    }
  }
  if (!remote && (flag & Selector::Sel_Write)) {
    Stor->set_gflag(0);
  }
// nXDS does not have specific response flags
//if (remote) {
//  TM_data->data2_status = 0;
//  TM_data->err2_status = 0;
//} else {
//  TM_data->data_status = 0;
//  TM_data->err_status = 0;
//}
  return 0;
}

Timeout *nXDS_TM::GetTimeout() {
  return &TO;
}

