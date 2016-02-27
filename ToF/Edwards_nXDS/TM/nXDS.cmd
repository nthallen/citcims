%INTERFACE <nXDS>
&command
  : nXDS &nxds_drive start * { if_nXDS.Turf("%d:802:1\n", $2); }
  : nXDS &nxds_drive stop * { if_nXDS.Turf("%d:802:0\n", $2); }
  : nXDS &nxds_drive full speed * { if_nXDS.Turf("%d:803:0\n", $2); }
  : nXDS &nxds_drive standby speed * { if_nXDS.Turf("%d:803:1\n", $2); }
  : nXDS &nxds_drive set standby speed %d (Enter speed as percent of full speed) * {
      if_nXDS.Turf("%d:805:%d\n", $2, $6);
    }
  ;

&nxds_drive <int>
  : A { $0 = 0; }
  : B { $0 = 1; }
  ;

