%{
  #include <fcntl.h>
  #include "SWStat.h"
  #include "address.h"

  #include "SWData.h"
  #ifdef SERVER
    SWData_t SWData;
    
    void send_to_tof(const char *cmd) {
      int fd, nb_in, nb;
      fd = open("/net/tofherc/dev/huarp/ToF/cmd/server", O_WRONLY|O_NONBLOCK);
      if (fd < 0) {
        nl_error(2, "Unable to contact ToF command server");
        return;
      }
      nb_in = strlen(cmd);
      nb = write(fd, cmd, nb_in);
      if (nb < 0) {
        nl_error(2, "Error writing to ToF command server: %s", strerror(errno));
      } else if (nb < nb_in) {
        nl_error(2, "Incomplete write to ToF: wrote %d of %d", nb, nb_in);
      }
      close(fd);
    }
  #endif
%}
%INTERFACE <SWData:DG/data>

&command
  : Telemetry Logging Suspend * {}
  : Telemetry Logging Resume * {}
  : &SWTM * { if_SWData.Turf(); }
  : ToF ambient flow on * {
        send_to_tof( "Set ambient zero flow 390 sccm\n" ); }
  : ToF ambient flow off * {
        send_to_tof( "Set ambient zero flow 450 sccm\n" ); }
  : ToF command %s (Enter command to send to ToF) * {
        send_to_tof( strcat($3, "\n")); }
  ;

&SWTM
  : SW Status &SWStat { SWData.SWStat = $3; }
  ;

&SWStat <int>
  : Set %d { $0 = $2; }
  : Shutdown { $0 = SWS_SHUTDOWN; }
  : Readfile { $0 = SWS_LAB_READ; }
  : Dither One { $0 = SWS_DITHER_ONE; }
  : Dither TwoScan { $0 = SWS_DITHER_TWO; }
  : Dither ThreeCal { $0 = SWS_DITHER_THREE; }
  : Dither Water { $0 = SWS_DITHER_WATER; }
  : Dither Water2 { $0 = SWS_DITHER_WATER2; }
  : Dither End { $0 = SWS_DITHER_END; }
  : Dither Suspend { $0 = SWS_TRIP_SUS; }
  : Inlet Pressure Control { $0 = SWS_INLET_PRESSURE; }
  : Inlet Idle { $0 = SWS_INLET_IDLE; }
  : Scrub Ready { $0 = SWS_SCRUB_READY; }
  : SitOn Data { $0 = SWS_SITON_DATA; }
  : Dither Drycal { $0 = SWS_DITHER_DRYCAL; }
  : Dither Ambcal { $0 = SWS_DITHER_AMBCAL; }
  : Dither Zero { $0 = SWS_DITHER_ZERO; }
  : SitOn Neg DatawMHP { $0 = SWS_SITON_NEG_DATAwMHP; }
  : SitOn Neg DryZero { $0 = SWS_SITON_NEG_DRYZERO; }
  : SitOn Neg DryCal { $0 = SWS_SITON_NEG_DRYCAL; }
  : SitOn Neg AmbZero { $0 = SWS_SITON_NEG_AMBZERO; }
  : SitOn Pos AmbCal { $0 = SWS_SITON_POS_AMBCAL; }
  : Init Continue { $0 = SWS_INIT_CONTINUE; }
  : Auto Cal Start { $0 = SWS_AUTOCALTRIPLE_START; }
  : Auto Cal Stop { $0 = SWS_AUTOCALTRIPLE_STOP; }
  ;
