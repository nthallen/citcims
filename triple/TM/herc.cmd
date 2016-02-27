%{
  /* herc.cmd */
  #include "herc_cmds.h"
%}
%INTERFACE <Hercules:Hercules>

&command
  : &herc_strobe_cmd * { if_Hercules.Turf( "W%X:0\n", 0x4000 + $1 ); }
  : &herc_on_off &on_off *
      { if_Hercules.Turf( "W%X:%X\n", 0x4000 + $1, $2 ? 0xFF : 0 ); }
  : &herc_op_cl &op_cl *
      { if_Hercules.Turf( "W%X:%X\n", 0x4000 + $1, $2 ? 0xFF : 0 ); }
  : &herc_sc_by &scrub_bypass *
      { if_Hercules.Turf( "W%X:%X\n", 0x4000 + $1, $2 ? 0xFF : 0 ); }
  : &herc_sys_vent &sys_vent *
      { if_Hercules.Turf( "W%X:%X\n", 0x4000 + $1, $2 ? 0xFF : 0 ); }
  : Set &herc_da &herc_da_val *
      { if_Hercules.Turf( "W%X:%X\n", 0x2000 + $2, $3); }
  ;

&herc_strobe_cmd <int>
  : Flowtube Valve close { $0 = CMD_A5; }
  : Flowtube Valve open  { $0 = CMD_A0; }
  : Flowtube Pump off    { $0 = CMD_A6; }
  : Flowtube Pump on     { $0 = CMD_A1; }
  : Turbo Valve close    { $0 = CMD_B2; }
  : Turbo Valve open     { $0 = CMD_A2; }
  : Turbo Rough Pump off { $0 = CMD_B3; }
  : Turbo Rough Pump on  { $0 = CMD_A3; }
  : Dewar Valve open     { $0 = CMD_B4; }
  : Dewar Valve close    { $0 = CMD_A4; }
  ;
					
&herc_on_off <int>
  : ScrubMFC Open { $0 = CMD_E0; }
  : ScrubMFC Close { $0 = CMD_E1; }
  : DiluteMFC Open { $0 = CMD_E2; }
  : DiluteMFC Close { $0 = CMD_E3; }
  : IonSourceMFC Open { $0 = CMD_E4; }
  : IonSourceMFC Close { $0 = CMD_E5; }
  : ReagentMFC Open { $0 = CMD_E6; }
  : ReagentMFC Close { $0 = CMD_E7; }
  : 1200 Enable A { $0 = CMD_A7; }
  : 1200 Enable B { $0 = CMD_B7; }
  : LensHV Enable { $0 = CMD_C7; }
  ;

&herc_sc_by <int>
  : Labelled Cal Scrub { $0 = CMD_C1; }
  : Normal Cal Scrub { $0 = CMD_C3; }
  ;

&herc_sys_vent <int>
  : Labelled Cal Bypass { $0 = CMD_C2; }
  : Normal Cal Bypass { $0 = CMD_C4; }
  ;

&herc_op_cl <int>
  : Reagent Valve { $0 = CMD_B0; }
  : ScrubAir Valve { $0 = CMD_C0; }
  ;


&on_off <int>
  : on { $0 = 1; }
  : off { $0 = 0; }
  ;

&op_cl <int>
  : open { $0 = 1; }
  : close { $0 = 0; }
  ;

&scrub_bypass <int>
  : On { $0 = 1; }
  : Bypass { $0 = 0; }
  ;

&sys_vent <int>
  : into System { $0 = 1; }
  : Bypass { $0 = 0; }
  ;

%{
 /* spare CMD_B1 */
 /* spare CMD_B6 */
 /* spare CMD_C5 */
 /* spare CMD_C6 */
%}

&herc_da <int>
  : Scrub MFC { $0 = 0; }
  : Dilute MFC { $0 = 1; }
  : IonSource MFC { $0 = 2; }
  : Reagent MFC { $0 = 3; }
  ;

&herc_da_val <int>
  : %d ( Enter d/a value 0-2048 ) {
      int val = $1;
      if ( val < 0 ) val = 0;
      else if ( val > 2048 ) val = 2048;
      $0 = val;
    }
  ;
