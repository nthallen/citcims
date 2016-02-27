%INTERFACE <Zeno>

&command
  : Zeno &ZENO_Command * { if_Zeno.Turf("%s\n", $2); }
  ;
&ZENO_Command <const char *>
  : Exit { $0 = "EX"; }
  ;
