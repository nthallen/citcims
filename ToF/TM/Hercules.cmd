%{
  #ifdef SERVER
    #include "address.h"

    static unsigned short Herc_Scale( double val, double minV, double maxV ) {
      signed short s_val;
      unsigned short u_val;
      if ( val < minV ) val = minV;
      else if ( val > maxV) val = maxV;
      s_val = (val * 2048 / 10.);
      if ( s_val < -2048 ) s_val = -2048;
      else if (s_val > 2047 ) s_val = 2047;
      u_val = s_val + 2048;
      return u_val;
    }
  #endif
%}
%INTERFACE <Hercules:/net/tofherc/dev/huarp/ToF/Hercules>

&command
  : &Herc_On_Off_Cmd &on_off * { if_Hercules.Turf( "W%X:0\n", 0x4000+$1+$2 ); }
  : &Herc_Cmd * { if_Hercules.Turf( "W%X:0\n", 0x4000+$1 ); }
  : Set Oct Amp %f (Enter Volts) Volts *
    { if_Hercules.Turf( "W%X:%X\n", Oct_Amp_sp_Address, Herc_Scale($4, 0, 5)); }
  : Set Oct Bias %f (Enter Volts) Volts *
    { if_Hercules.Turf( "W%X:%X\n", Oct_Bias_sp_Address, Herc_Scale($4, -5, 5)); }
  : Set Fly Valve Set Point %f (Enter Volts) Volts *
    { if_Hercules.Turf( "W%X:%X\n", FlySt_Address, Herc_Scale($6, 0, 10)); }
  : Set Spare Analog Out %f (Enter Volts) Volts *
    { if_Hercules.Turf( "W%X:%X\n", SpAO1_sp_Address, Herc_Scale($5, -10, 10)); }
  ;
&Herc_On_Off_Cmd <unsigned short>
  : Cal Bypass { $0 = 0; }
  : Cal Scrub  { $0 = 2; }
  : Cal H2O2 { $0 = 4; }
  : Cal Oacid { $0 = 6; }
  : Cal MHP { $0 = 8; }
  : Cal Spare1 { $0 = 10; }
  : Cal Spare2 { $0 = 12; }
  : Turbopump B power { $0 = 26; }
  : Turbopump A power { $0 = 28; }
  : HV Power { $0 = 40; }
  : Oct Power { $0 = 42; }
  ;

&Herc_Cmd <unsigned short>
  : Ambient Zero Off { $0 = 14; }
  : Ambient Zero On { $0 = 15; }
  : Turbopump A Stop { $0 = 30; }
  : Turbopump A Start { $0 = 31; }
  : Turbopump B Stop { $0 = 34; }
  : Turbopump B Start { $0 = 35; }
  : Turbopump A High { $0 = 32; }
  : Turbopump A Low { $0 = 33; }
  : Turbopump B High { $0 = 36; }
  : Turbopump B Low { $0 = 37; }
  : Butterfly Valve Position Mode { $0 = 38; }
  : Butterfly Valve Pressure Mode { $0 = 39; }
  : Butterfly Valve hold { $0 = 44; }
  : Butterfly Valve close { $0 = 45; }
  : Butterfly Valve open { $0 = 46; }
  : Butterfly Valve control { $0 = 47; }
  : Turbo scroll pump on { $0 = 16; }
  : Turbo scroll pump off { $0 = 17; }
  : Turbo scroll pump valve on { $0 = 18; }
  : Turbo scroll pump valve off { $0 = 19; }
  : Flow tube scroll pump on { $0 = 20; }
  : Flow tube scroll pump off { $0 = 21; }
  : Flow tube scroll pump valve on { $0 = 22; }
  : Flow tube scroll pump valve off { $0 = 23; }
  : Flow tube dewar valve on { $0 = 24; }
  : Flow tube dewar valve off { $0 = 25; }
  ;

&start_stop <unsigned short>
  : Start { $0 = 1; }
  : Stop { $0 = 0; }
  ;
