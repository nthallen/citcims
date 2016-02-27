/* nXDS_main.cc
 * Driver for Edwards nXDS Scroll Pump
 */
#include "nXDS.h"
#include "oui.h"
#include "nortlib.h"

char *nxds_path;
uint8_t nxds_absent;

/** Maps command drive numbers in the range 0 to N_NXDS_DRIVES-1
 *  to RS485 device numbers which should match the device's configuration.
 */
const unsigned nXDS::nX_DevNo[N_NXDS_DRIVES] = {1,2};

void enqueue_polls(nXDS *nX, nXDS_t *nX_TM) {
  for (unsigned drv = 0; drv < N_NXDS_DRIVES; ++drv) {
    if (!(nxds_absent & (1<<drv))) {
      nX->enqueue_poll(drv, 'V', 808);
      nX->enqueue_poll(drv, 'V', 809);
      nX->enqueue_poll(drv, 'V', 802);
      nX->enqueue_request(drv, 'S', 801, true);
      nX->enqueue_request(drv, 'V', 826, true);
    }
  }
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  nl_error( 0, "Starting V0.1.12" );
  { Selector Loop;
    nXDS_t nX_TM;
    for (unsigned drv = 0; drv < N_NXDS_DRIVES; ++drv) {
      nX_TM.drive[drv].link_voltage = 0;
      nX_TM.drive[drv].motor_current = 0;
      nX_TM.drive[drv].motor_power = 0;
      nX_TM.drive[drv].status = 0;
      //nX_TM.drive[drv].pump_temp = 0;
      nX_TM.drive[drv].controller_temp = 0;
      nX_TM.drive[drv].motor_freq = 0;
      nX_TM.drive[drv].pump_on = 0;
      nX_TM.drive[drv].fill = 0;
    }
    nXDS nX(nxds_path, &nX_TM);
    TM_Selectee TM("nXDS", &nX_TM, sizeof(nX_TM));
    nXDS_cmd Cmd(&nX);
    nl_error(MSG_DBG(2), "Finished constructors");
    Loop.add_child(&nX);
    Loop.add_child(&TM);
    Loop.add_child(&Cmd);
    enqueue_polls(&nX, &nX_TM);
    nl_error(MSG_DBG(2), "Entering event_loop");
    Loop.event_loop();
  }
  nl_error( 0, "Terminating" );
}
