%{
  #ifdef SERVER
    #include "address.h"

    static unsigned short MFC_Scale( double val, double scale ) {
      val = 5*val/scale;
      if ( val > 5 ) val = 5;
      else if ( val < -1 ) val = -1;
      return (unsigned short)(4096*(val+10)/20);
    }
  #endif
%}
%INTERFACE <AthenaII:/net/tofathena/dev/huarp/ToF/AthenaII>

&command
  : Set Spare 2 Flow %f (Enter SCCM) sccm *
      { if_AthenaII.Turf( "W%X:%X\n", MFC_S2_sp_Address, MFC_Scale($5, 500) ); }
  : Set Spare 1 Flow %f (Enter SLM) slm *
      { if_AthenaII.Turf( "W%X:%X\n", MFC_S1_sp_Address, MFC_Scale($5,5) ); }
  : Set Total Flow %f (Enter SLM) slm *
      { if_AthenaII.Turf( "W%X:%X\n", Tot_F_sp_Address, MFC_Scale($4,5) ); }
  : Set Ambient Zero Flow %f (Enter SCCM) sccm *
      { if_AthenaII.Turf( "W%X:%X\n", ZF2_F_sp_Address, MFC_Scale($5, 1000) ); }
  : &AII_Cmd &on_off * { if_AthenaII.Turf( "W%X:%X\n", $1, $2 ); }
  ;
&AII_Cmd <unsigned short>
  : Ambient zero valve { $0 = 0x4000; }
  : Spare valve 1 { $0 = 0x4001; }
  : Spare valve 2 { $0 = 0x4002; }
  : Spare valve 3 { $0 = 0x4003; }
  : Spare valve 4 { $0 = 0x4004; }
  : Spare valve 5 { $0 = 0x4005; }
  : Spare valve 6 { $0 = 0x4006; }
  : Spare valve 7 { $0 = 0x4007; }
  ;

&on_off <unsigned short>
  : On { $0 = 1; }
  : Off { $0 = 0; }
  ;
