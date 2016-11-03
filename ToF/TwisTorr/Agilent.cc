/* Agilent.cc
 * Driver for Agilent TwisTorr Turbo Pump
 */
#include "TwisTorr.h"
#include "oui.h"
#include "nortlib.h"

char *agilent_path;
uint8_t agilent_absent;

/** Maps command drive numbers in the range 0 to N_TWISTORR_DRIVES-1
 *  to RS485 device numbers which should match the device's configuration.
 */
const unsigned TwisTorr::TT_DevNo[N_TWISTORR_DRIVES] = {1, 2, 3};

void enqueue_polls(TwisTorr *TT, TwisTorr_t *TT_TM) {
  for (unsigned drv = 0; drv < N_TWISTORR_DRIVES; ++drv) {
    if (!(agilent_absent & (1<<drv))) {
      TT->enqueue_poll_float(drv, 200, &(TT_TM->drive[drv].pump_current)); // mA
      TT->enqueue_poll_float(drv, 201, &(TT_TM->drive[drv].pump_voltage)); // V
      TT->enqueue_poll_float(drv, 202, &(TT_TM->drive[drv].pump_power)); // W
      TT->enqueue_poll_float(drv, 203, &(TT_TM->drive[drv].driving_freq)); // Hz
      TT->enqueue_poll_float(drv, 204, &(TT_TM->drive[drv].pump_temperature)); // C
      TT->enqueue_poll_float(drv, 205, &(TT_TM->drive[drv].pump_status)); // bit-mapped
      // TT->enqueue_poll_float(drv, 210, &(TT_TM->drive[drv].rotation_speed));
      TT->enqueue_poll_bit(drv, 0, &(TT_TM->drive[drv].flags), 0x01);
      TT->enqueue_poll_bit(drv, 1, &(TT_TM->drive[drv].flags), 0x02);
      TT->enqueue_poll_bit(drv, 106, &(TT_TM->drive[drv].flags), 0x04);
      TT->enqueue_poll_bit(drv, 107, &(TT_TM->drive[drv].flags), 0x08);
      TT->enqueue_poll_bit(drv, 122, &(TT_TM->drive[drv].flags), 0x10);
      TT->enqueue_poll_bit(drv, 125, &(TT_TM->drive[drv].flags), 0x20);
    }
  }
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  nl_error( 0, "Starting V0.1.29" );
  { Selector Loop;
    TwisTorr_t TT_TM;
    for (unsigned drv = 0; drv < N_TWISTORR_DRIVES; ++drv) {
      TT_TM.drive[drv].pump_current = 0;
      TT_TM.drive[drv].pump_power = 0;
      TT_TM.drive[drv].driving_freq = 0;
      TT_TM.drive[drv].pump_temperature = 0;
      TT_TM.drive[drv].pump_status = 0;
      TT_TM.drive[drv].rotation_speed = 0;
      TT_TM.drive[drv].error_status = 0;
      TT_TM.drive[drv].flags = 0;
    }
    TwisTorr TT(agilent_path, &TT_TM);
    TM_Selectee TM("TwisTorr", &TT_TM, sizeof(TT_TM));
    TwisTorr_cmd Cmd(&TT);
    Loop.add_child(&TT);
    Loop.add_child(&TM);
    Loop.add_child(&Cmd);
    enqueue_polls(&TT, &TT_TM);
    Loop.event_loop();
  }
  nl_error( 0, "Terminating" );
}
