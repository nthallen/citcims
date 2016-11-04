%INTERFACE <TwisTorr>
&command
  : TwisTorr &TTdev Start * { if_TwisTorr.Turf("W:%d:0:1\n", $2); }
  : TwisTorr &TTdev Stop  * { if_TwisTorr.Turf("W:%d:0:0\n", $2); }
  : TwisTorr &TTdev Low Speed On * { if_TwisTorr.Turf("W:%d:1:1\n", $2); }
  : TwisTorr &TTdev Low Speed Off * { if_TwisTorr.Turf("W:%d:1:0\n", $2); }
  : TwisTorr &TTdev Vent Open * { if_TwisTorr.Turf("W:%d:122:0\n", $2); }
  : TwisTorr &TTdev Vent Closed * { if_TwisTorr.Turf("W:%d:122:1\n", $2); }
  : TwisTorr &TTdev Vent Auto * { if_TwisTorr.Turf("W:%d:125:0\n", $2); }
  : TwisTorr &TTdev Vent Manual * { if_TwisTorr.Turf("W:%d:125:1\n", $2); }
  : TwisTorr &TTdev Soft Start Yes * { if_TwisTorr.Turf("W:%d:100:1\n", $2); }
  : TwisTorr &TTdev Soft Start No * { if_TwisTorr.Turf("W:%d:100:0\n", $2); }
  : TwisTorr &TTdev Soft Start Auto * { if_TwisTorr.Turf("W:%d:100:2\n", $2); }
  : TwisTorr &TTdev Active Stop Yes * { if_TwisTorr.Turf("W:%d:107:1\n", $2); }
  : TwisTorr &TTdev Active Stop No * { if_TwisTorr.Turf("W:%d:107:0\n", $2); }
  ;
&TTdev <int>
  : A { $0 = 0; }
  : B { $0 = 1; }
  ;
