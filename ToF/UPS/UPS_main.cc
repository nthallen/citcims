/* UPS.cc
 * Driver for Orion Power Systems DC3000RT UPS
 */
#include "UPS.h"
#include "oui.h"
#include "nortlib.h"

char *device_path;
const char *ups_remote_node;
const char *ups_remote_exp;

void ups_init_options( int argc, char **argv) {
  int c;

  optind = OPTIND_RESET; /* start from the beginning */
  opterr = 0; /* disable default error message */
  while ((c = getopt(argc, argv, opt_string)) != -1) {
    switch (c) {
      case 'p':
        device_path = optarg;
        break;
     case 'n':
       ups_remote_node = optarg;
       break;
     case 'e':
       ups_remote_exp = optarg;
       break;
      case '?':
        nl_error(3, "Unrecognized Option -%c", optopt);
    }
  }
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  nl_error( 0, "Starting V0.7" );
  { Selector Loop;
    UPS_TM_t UPSData;
    // Initialize 
    UPS_ser UPS(device_path, &UPSData);
    // TM_Selectee TM("UPS_TM", &UPSData, sizeof(UPSData));
    UPS_TM TM(&UPSData);
    UPS_TM *TM2 = 0;
    UPS_cmd Cmd(&UPS);
    Loop.add_child(&UPS);
    Loop.add_child(&TM);
    Loop.add_child(&Cmd);
    if (ups_remote_node || ups_remote_exp) {
      TM2 = new UPS_TM(&UPSData, ups_remote_node, ups_remote_exp);
      Loop.add_child(TM2);
    }
    UPS.enqueue_polls();
    Loop.event_loop();
    if (TM2) {
      delete(TM2);
    }
  }
  nl_error( 0, "Terminating" );
}
