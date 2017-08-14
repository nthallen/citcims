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
  : Fluorine Flow %f (Enter value in sccm) sccm
    { $0.channel = 1; $0.value = $3; }
  : Ion Source Flow %f (Enter value in sccm) sccm
    { $0.channel = 2; $0.value = $4; }
  : Dilution Flow %f (Enter value in sccm) sccm
    { $0.channel = 3; $0.value = $3; }
;
