#include <errno.h>
#include <string.h>
#include "nortlib.h"
#include "UPS.h"

UPS_TM::UPS_TM(UPS_TM_t *data, const char *remnode,
    const char *remexp)
  : Selectee() {
  TMid = 0;
  remote = 0;
  init(data, remnode, remexp);
}

UPS_TM::UPS_TM() : Selectee() {
  TMid = 0;
  remote = 0;
}

const char *UPS_TM::UPS_TM_NAME = "UPS_TM";

void UPS_TM::init(UPS_TM_t *data, const char *remnode,
    const char *remexp) {
  if (remnode || remexp) {
    int nb;
    char *rmt = (char *)nl_new_memory(PATH_MAX);
    if (remexp == 0) {
      nb = snprintf(rmt, PATH_MAX, "/net/%s%s", remnode,
        tm_dev_name(UPS_TM_NAME));
    } else {
      if (remnode) {
        nb = snprintf(rmt, PATH_MAX, "/net/%s/dev/huarp/%s/DG/data/%s",
          remnode, remexp, UPS_TM_NAME);
      } else {
        nb = snprintf(rmt, PATH_MAX, "/dev/huarp/%s/DG/data/%s", remexp,
          UPS_TM_NAME);
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
void UPS_TM::Connect() {
  int save_response = set_response(remote ? 0 : nl_response);
  TMid = Col_send_init( remote ? remote : UPS_TM_NAME, TM_data,
    sizeof(UPS_TM_t), 0 );
  if ( TMid ) {
    TO.Clear();
    fd = TMid->fd;
    flags = Selector::Sel_Write;
    if (remote) {
      nl_error(0, "TM connection established to %s", remote);
    }
  } else {
    if (!TO.Expired()) {
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
UPS_TM::~UPS_TM() {
  if (TMid) {
    Col_send_reset(TMid);
    TMid = 0;
    fd = -1;
  }
}

/**
 * Calls Col_send() and sets gflag(0)
 */
int UPS_TM::ProcessData(int flag) {
  if (TMid == 0) {
    Connect(); // Will either set TMid or TO
  }
  if (TMid) {
    if (Col_send(TMid)) {
      if (Col_send_reset(TMid)) {
        nl_error(3, "Error closing %s TM connection: %s",
          remote ? "remote" : "local", strerror(errno));
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
    if (remote) {
      TM_data->UPS_Response2 &= ~UPSR_RESPONSES;
    } else {
      TM_data->UPS_Response &= ~UPSR_RESPONSES;
    }
  }
  return 0;
}

Timeout *UPS_TM::GetTimeout() {
  return &TO;
}
