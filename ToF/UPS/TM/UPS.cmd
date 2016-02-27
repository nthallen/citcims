%INTERFACE <UPS>

&command
  : UPS Test for &minutes *
      { int mins = $4;
	if (mins < 1) mins = 1;
	if (mins > 99) mins = 99;
	if_UPS.Turf("T%02d\n", mins);
      }
  : UPS Test for &seconds *
      { int tens = $4/6;
	if (tens < 2) tens = 2;
	if (tens > 9) {
	  int mins = $4/60;
	  if (mins < 1) mins = 1;
	  if (mins > 99) mins = 00;
	  if_UPS.Turf("T%02d\n", mins);
	} else {
	  if_UPS.Turf("T.%d\n", tens);
	}
      }
  : UPS &shutdown * { if_UPS.Turf("S%02d\n", $2); }
  : UPS &shutdown and Restore after %d (Enter time in minutes) minutes *
      { if_UPS.Turf("S%02dR%04d\n", $2, $6); }
  : UPS Cancel Shutdown * { if_UPS.Turf("CS\n"); }
  : UPS Cancel Test * { if_UPS.Turf("CT\n"); }
  : UPS Socket 1 On * { if_UPS.Turf("KN\n"); }
  : UPS Socket 1 Off * { if_UPS.Turf("KF\n"); }
  : UPS Query Protocol ID * { if_UPS.Turf("Q0\n"); }
  : UPS Query Model * { if_UPS.Turf("Q1\n"); }
  : UPS Query UPS ID * { if_UPS.Turf("Q2\n"); }
  : UPS Query Main CPU Firmware Version * { if_UPS.Turf("Q3\n"); }
  : UPS Query Bypass Voltage Range * { if_UPS.Turf("Q4\n"); }
  : UPS Query Bypass Frequency Range * { if_UPS.Turf("Q5\n"); }
  : UPS Query Rating Information * { if_UPS.Turf("Q6\n"); }
  : UPS Query Setting Flag Status * { if_UPS.Turf("Q7\n"); }
  : UPS Query High Efficiency Mode Voltage Range * { if_UPS.Turf("Q8\n"); }
  : UPS Query Fault status * { if_UPS.Turf("Q9\n"); }
  : UPS Quit * { if_UPS.Turf("X\n"); }
  ;

&minutes <int>
  : minutes %d (Enter time in minutes) { $0 = $2; }
  ;
&seconds <int>
  : seconds %d (Enter time in seconds) { $0 = $2; }
  ;
&shutdown <int>
  : Shutdown in %d (Enter time in minutes) minutes { $0 = $3; }
  ;

