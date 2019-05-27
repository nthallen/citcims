%{
  typedef struct {
    int channel;
    float value;
  } Horiba_Cmd;
%}
%INTERFACE <Horiba>

&command
  : Set &Horiba_Chan * {
      if_Horiba.Turf( "W%d:%.2f\n", $2.channel, $2.value );
    }
  ;
&Horiba_Chan <Horiba_Cmd>
  : Dilution Flow %f (Enter value in sccm) sccm
    { $0.channel = 1; $0.value = $3/1; }
  : Ion Source Flow %f (Enter value in sccm) sccm
    { $0.channel = 2; $0.value = $4; }
  : Fluorine Flow %f (Enter value in sccm) sccm
    { $0.channel = 3; $0.value = $3; }
  : Cal Flow %f (Enter value in sccm) sccm
    { $0.channel = 5; $0.value = $3; }
  : Zero Flow %f (Enter value in sccm) sccm
    { $0.channel = 6; $0.value = $3; }
  : Cal2 Flow %f (Enter value in sccm) sccm
    { $0.channel = 7; $0.value = $3; }
;
