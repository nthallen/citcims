/* Agilent.cc
 * Driver for Agilent TwisTorr Turbo Pump
 */
#include "Agilent.h"
#include "oui.h"

char *agilent_path;

void enqueue_polls(TwisTorr *TT, TwisTorr_t *TT_TM) {
  TT->enqueue_poll_float(TwisTorr::TT_DevNo, 200, &(TT_TM->pump_current));
  TT->enqueue_poll_float(TwisTorr::TT_DevNo, 201, &(TT_TM->pump_voltage));
  TT->enqueue_poll_float(TwisTorr::TT_DevNo, 202, &(TT_TM->pump_power));
  TT->enqueue_poll_float(TwisTorr::TT_DevNo, 203, &(TT_TM->driving_freq));
  TT->enqueue_poll_float(TwisTorr::TT_DevNo, 204, &(TT_TM->pump_temperature));
  TT->enqueue_poll_float(TwisTorr::TT_DevNo, 205, &(TT_TM->pump_status));
  TT->enqueue_poll_float(TwisTorr::TT_DevNo, 210, &(TT_TM->rotation_speed));
  TT->enqueue_poll_bit(TwisTorr::TT_DevNo, 0, &(TT_TM->flags), 0x01);
  TT->enqueue_poll_bit(TwisTorr::TT_DevNo, 1, &(TT_TM->flags), 0x02);
  TT->enqueue_poll_bit(TwisTorr::TT_DevNo, 106, &(TT_TM->flags), 0x04);
  TT->enqueue_poll_bit(TwisTorr::TT_DevNo, 107, &(TT_TM->flags), 0x08);
  TT->enqueue_poll_bit(TwisTorr::TT_DevNo, 122, &(TT_TM->flags), 0x10);
  TT->enqueue_poll_bit(TwisTorr::TT_DevNo, 123, &(TT_TM->flags), 0x20);
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { Selector Loop;
    TwisTorr_t TT_TM;
    TwisTorr TT(agilent_path);
    enqueue_polls(&TT, &TT_TM);
    TM_Selectee TM("TwisTorr", &TT_TM, sizeof(TT_TM));
    TwisTorr_cmd Cmd(&TT);
    Loop.add_child(&TT);
    Loop.add_child(&TM);
    Loop.add_child(&Cmd);
    Loop.event_loop();
  }
}
