%{
  #include <math.h>
%}

%INTERFACE <modbus>

&command
  : Watlow PM Set &watlow_sp %f (Enter Temperature in Celcius) * {
      if_modbus.Turf("S%d:%.1f\n", $4, $5);
    }
  : Watlow F4 Set &watlow_sp %f (Enter Temperature in Celcius) * {
      if_modbus.Turf("F%d:%d\n", $4, (int)floor($5*10 + 0.5));
    }
  : Watlow F4 Resume Profile * {
      if_modbus.Turf("F3:1\n");
    }
  : Watlow F4 Terminate Profile * {
      if_modbus.Turf("F4:1\n");
    }
  ;

&watlow_sp <int>
  : Channel 1 { $0 = 1; }
  : Channel 2 { $0 = 2; }
  ;
