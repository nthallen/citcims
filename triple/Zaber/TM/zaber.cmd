%INTERFACE <Zaber>

&command
  : Zaber Move &zaber_drive Absolute %ld * {
      if_Zaber.Turf("W%d:%d:%ld\n", $3, 20, $5 );
    }
  : Zaber Move &zaber_drive Relative %ld * {
      if_Zaber.Turf("W%d:%d:%ld\n", $3, 21, $5 );
    }
  : Zaber Home &zaber_drive * {
      if_Zaber.Turf("W%d:%d:%ld\n", $3, 1, 0L );
    }
  : Zaber Stop &zaber_drive * {
      if_Zaber.Turf("W%d:%d:%ld\n", $3, 23, 0L );
    }
  : Zaber Command &zaber_drive %d (Enter Zaber Command Number)
          %ld (Enter Value) * {
      if_Zaber.Turf("W%d:%d:%ld\n", $3, $4, $5 );
    }
  : Zaber quit * { if_Zaber.Turf("Q\n"); }
  ;

&zaber_drive <int>
  : All Drives { $0 = 0; }
  : Drive 1 { $0 = 1; }
  : Drive 2 { $0 = 2; }
  ;
