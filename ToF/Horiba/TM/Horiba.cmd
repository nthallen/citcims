%INTERFACE <Horiba>

&command
  : Set &HoribaChan Flow %f (Enter Flow in SCCM) sccm * {
      if_Horiba.Turf( "W%d:%.2f\n", $2, $4 );
    }
  ;
&HoribaChan <int>
  : Dilution { $0 = 1; }
  : Ion Source { $0 = 2; }
  : Fluorine { $0 = 3; }
  ;

