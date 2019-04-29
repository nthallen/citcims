%{
  #include "SWData.h"
  #ifdef SERVER
    SWData_t SWData;
  #endif
%}

%INTERFACE <SWData:DG/data>

&command
  : &SWTM * { if_SWData.Turf(); }
  ;
&SWTM
  : SW Status &SWStat { SWData.SWStat = $3; }
  : SW Flow State &SWFlow { SWData.SWFlow = $4; }
  : Inlet Pgain &InP_Pgain { SWData.InP_Pgain = $3; }
  : Inlet Igain &InP_igain { SWData.InP_igain = $3; }
  : Inlet Pressure Setpoint &InPset { SWData.InPset = $4; }
  ;
&SWStat <unsigned char>
  : Flow State Off { $0 = SWS_FLOWSTATE_OFF; }
  : Set %d { $0 = $2; }
  : Turbo Pumps On { $0 = SWS_TURBOS_ON; }
  : Turbo Pumps Off { $0 = SWS_TURBOS_OFF; }
  : Pumps On { $0 = SWS_PUMPS_ON; }
  : Pumps Off { $0 = SWS_PUMPS_OFF; }
  : Inlet Pressure Control { $0 = SWS_INLET_PCTRL; }
  : Inlet Close { $0 = SWS_INLET_IDLE; }
  : Inlet Lab { $0 = SWS_INLET_LAB; }
  : ToF Start { $0 = SWS_TOF_START; }
  : ToF Stop { $0 = SWS_TOF_STOP; }
  : Data loop start { $0 = SWS_DATA_LOOP; }
  : Data loop stop { $0 = SWS_DATA_STOP; }
  : Data loop no cal { $0 = SWS_DATA_LP_NC; }
  : Quick cal { $0 = SWS_DATA_QC; }
  : Amb zero loop start { $0 = SWS_DATA_AMB_ZERO_LOOP_START; }
  : Amb zero loop stop { $0 = SWS_DATA_AMB_ZERO_LOOP_STOP; }
  : Auto cal start { $0 = SWS_AUTO_CAL_START; }
  : Auto cal stop { $0 = SWS_AUTO_CAL_STOP; }
  : Data flux loop no cal start { $0 = SWS_DATAF_LP_NC; }
  : Data flux loop cal start { $0 = SWS_DATAF_LP_C; }
  : Shutdown Quick { $0 = SWS_QUICK_SHUTDOWN; }
  : Shutdown Full { $0 = SWS_SHUTDOWN; }
  : Auto cal lab start { $0 = SWS_AUTO_CAL_LAB_START; }
  : Auto cal lab stop { $0 = SWS_AUTO_CAL_LAB_STOP; }
  ;
&SWFlow <unsigned char>
  : Transitioning { $0 = 0; }
  : Off { $0 = SWS_FLOWSTATE_OFF; }
  ;
&InP_Pgain <float>
  : %f (Enter Proportional Gain) { $0 = $1; }
  ;
&InP_igain <float>
  : %f (Enter Integral Gain) { $0 = $1; }
  ;
&InPset <signed short>
  : %f (Enter Inlet Pressure Setpoint in mbar) { $0 = $1*32768/133.33; }
  ;
