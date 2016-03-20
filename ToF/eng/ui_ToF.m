function ui_ToF
f = ne_dialg('Time of Flight Instrument',1);
f = ne_dialg(f, 'add', 0, 1, 'gToFf', 'Flows' );
f = ne_dialg(f, 'add', 1, 0, 'pToFfs', 'S1' );
f = ne_dialg(f, 'add', 1, 0, 'pToFfs2', 'S2' );
f = ne_dialg(f, 'add', 1, 0, 'pToFfzf', 'ZF2' );
f = ne_dialg(f, 'add', 1, 0, 'pToFft', 'Total' );
f = ne_dialg(f, 'add', 0, 1, 'gToFgd', 'Gas Deck' );
f = ne_dialg(f, 'add', 1, 0, 'pToFgdt', 'Temp' );
f = ne_dialg(f, 'add', 1, 0, 'pToFgdmbar', 'mbar' );
f = ne_dialg(f, 'add', 1, 0, 'pToFgdpsi', 'psi' );
f = ne_dialg(f, 'add', 1, 0, 'pToFgdv', 'Volts' );
f = ne_dialg(f, 'add', 0, 1, 'gToFi', 'Inlet' );
f = ne_dialg(f, 'add', 1, 0, 'pToFip', 'P' );
f = ne_dialg(f, 'add', 1, 0, 'pToFitv', 'TV' );
f = ne_dialg(f, 'add', 1, 0, 'pToFis', 'Step' );
f = ne_dialg(f, 'add', 1, 0, 'pToFistale', 'Stale' );
f = ne_dialg(f, 'add', 1, 0, 'pToFistatus', 'Status' );
f = ne_dialg(f, 'add', 0, 1, 'gToFgc', 'Gas Cmds' );
f = ne_dialg(f, 'add', 1, 0, 'pToFgcs', 'Status' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'add', 0, 1, 'gToFt', 'Turbos' );
f = ne_dialg(f, 'add', 1, 0, 'pToFtt', 'Temp' );
f = ne_dialg(f, 'add', 1, 0, 'pToFtc', 'Current' );
f = ne_dialg(f, 'add', 1, 0, 'pToFtok', 'OK' );
f = ne_dialg(f, 'add', 1, 0, 'pToFts', 'Speed' );
f = ne_dialg(f, 'add', 1, 0, 'pToFttv', 'TV' );
f = ne_dialg(f, 'add', 1, 0, 'pToFtstatus', 'Status' );
f = ne_dialg(f, 'add', 0, 1, 'gToFo', 'Octopole' );
f = ne_dialg(f, 'add', 1, 0, 'pToFoa', 'Amp' );
f = ne_dialg(f, 'add', 1, 0, 'pToFob', 'Bias' );
f = ne_dialg(f, 'add', 1, 0, 'pToFod', 'Drive' );
f = ne_dialg(f, 'add', 0, 1, 'gToFfv', 'Fly Valve' );
f = ne_dialg(f, 'add', 1, 0, 'pToFfvs', 'Set' );
f = ne_dialg(f, 'add', 1, 0, 'pToFfvp', 'Pos' );
f = ne_dialg(f, 'add', 1, 0, 'pToFfv_p', 'P' );
f = ne_dialg(f, 'add', 1, 0, 'pToFfvstatus', 'Status' );
f = ne_dialg(f, 'add', 0, 1, 'gToFm', 'Misc' );
f = ne_dialg(f, 'add', 1, 0, 'pToFms', 'Status' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'add', 0, 1, 'gToFsws', 'SW Status' );
f = ne_dialg(f, 'add', 1, 0, 'pToFswsaii', 'AII' );
f = ne_dialg(f, 'add', 1, 0, 'pToFswsswf', 'SW Flow' );
f = ne_dialg(f, 'add', 1, 0, 'pToFswsip', 'In P' );
f = ne_dialg(f, 'add', 1, 0, 'pToFswssws', 'SW Stat' );
f = ne_dialg(f, 'add', 0, 1, 'gToFs', 'System' );
f = ne_dialg(f, 'add', 1, 0, 'pToFscpu', 'CPU' );
f = ne_dialg(f, 'add', 1, 0, 'pToFsd', 'Disk' );
f = ne_dialg(f, 'add', 1, 0, 'pToFstd', 'T Drift' );
f = ne_dialg(f, 'add', 0, 1, 'gToFh', 'Horiba' );
f = ne_dialg(f, 'add', 1, 0, 'pToFhd', 'Dilution' );
f = ne_dialg(f, 'add', 1, 0, 'pToFhis', 'Ion Src' );
f = ne_dialg(f, 'add', 1, 0, 'pToFhf', 'Fluorine' );
f = ne_dialg(f, 'add', 1, 0, 'pToFhp', 'Pressure' );
f = ne_dialg(f, 'add', 1, 0, 'pToFhs', 'Status' );
f = ne_dialg(f, 'add', 1, 0, 'pToFhstale', 'Stale' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'add', 0, 1, 'gToFig', 'Ion Gauge' );
f = ne_dialg(f, 'add', 1, 0, 'pToFigp', 'P' );
f = ne_dialg(f, 'add', 1, 0, 'pToFigs', 'Stale' );
f = ne_dialg(f, 'add', 1, 0, 'pToFigstat', 'Stat' );
f = ne_dialg(f, 'add', 0, 1, 'gToFxds', 'nXDS' );
f = ne_dialg(f, 'add', 1, 0, 'pToFxdsv', 'V' );
f = ne_dialg(f, 'add', 1, 0, 'pToFxdsi', 'I' );
f = ne_dialg(f, 'add', 1, 0, 'pToFxdsw', 'W' );
f = ne_dialg(f, 'add', 1, 0, 'pToFxdst', 'T' );
f = ne_dialg(f, 'add', 1, 0, 'pToFxdsf', 'Freq' );
f = ne_dialg(f, 'add', 1, 0, 'pToFxdss', 'Stale' );
f = ne_dialg(f, 'add', 0, 1, 'gToFnxds0', 'nXDS0' );
f = ne_dialg(f, 'add', 1, 0, 'pToFnxds0s', 'Stat' );
f = ne_dialg(f, 'add', 0, 1, 'gToFnxds1', 'nXDS1' );
f = ne_dialg(f, 'add', 1, 0, 'pToFnxds1s', 'Stat' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'add', 0, 1, 'gToFups', 'UPS' );
f = ne_dialg(f, 'add', 1, 0, 'pToFupsm', 'Mode' );
f = ne_dialg(f, 'add', 1, 0, 'pToFupsv', 'V' );
f = ne_dialg(f, 'add', 1, 0, 'pToFupsf', 'F' );
f = ne_dialg(f, 'add', 1, 0, 'pToFupsi', 'I' );
f = ne_dialg(f, 'add', 1, 0, 'pToFupsl', 'Load' );
f = ne_dialg(f, 'add', 1, 0, 'pToFupst', 'T' );
f = ne_dialg(f, 'add', 1, 0, 'pToFupstime', 'Time' );
f = ne_dialg(f, 'add', 0, 1, 'gToFupsstat', 'UP Sstat' );
f = ne_dialg(f, 'add', 1, 0, 'pToFupsstatp', 'Pc' );
f = ne_dialg(f, 'add', 1, 0, 'pToFupsstatg', 'Grp' );
f = ne_dialg(f, 'add', 1, 0, 'pToFupsstats', 'Status' );
f = ne_dialg(f, 'add', 1, 0, 'pToFupsstatw', 'Warn' );
f = ne_dialg(f, 'add', 1, 0, 'pToFupsstatr', 'Response' );
f = ne_dialg(f, 'add', 1, 0, 'pToFupsstatstale', 'Stale' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'add', 0, 1, 'gToF', 'gpsd' );
f = ne_dialg(f, 'add', 1, 0, 'pToFmode', 'mode' );
f = ne_dialg(f, 'add', 1, 0, 'pToFtime', 'time' );
f = ne_dialg(f, 'add', 1, 0, 'pToFlat', 'lat' );
f = ne_dialg(f, 'add', 1, 0, 'pToFlon', 'lon' );
f = ne_dialg(f, 'add', 1, 0, 'pToFalt', 'alt' );
f = ne_dialg(f, 'add', 1, 0, 'pToFtrack', 'track' );
f = ne_dialg(f, 'add', 1, 0, 'pToFspeed', 'speed' );
f = ne_dialg(f, 'add', 1, 0, 'pToFclimb', 'climb' );
f = ne_dialg(f, 'add', 1, 0, 'pToFsats', 'sats' );
f = ne_dialg(f, 'add', 1, 0, 'pToFstale', 'stale' );
f = ne_dialg(f, 'add', 0, 1, 'gToFgpsd_err', 'gpsd err' );
f = ne_dialg(f, 'add', 1, 0, 'pToFgpsd_errtime', 'time' );
f = ne_dialg(f, 'add', 1, 0, 'pToFgpsd_errdist', 'dist' );
f = ne_dialg(f, 'add', 1, 0, 'pToFgpsd_errtrack', 'track' );
f = ne_dialg(f, 'add', 1, 0, 'pToFgpsd_errspeed', 'speed' );
f = ne_dialg(f, 'add', 1, 0, 'pToFgpsd_errclimb', 'climb' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'add', 0, 1, 'gToFgpsd_toff', 'gpsd toff' );
f = ne_dialg(f, 'add', 1, 0, 'pToFgpsd_toffsec', 'sec' );
f = ne_dialg(f, 'add', 1, 0, 'pToFgpsd_toffnsec', 'nsec' );
f = ne_dialg(f, 'add', 0, 1, 'gToFgpsd_status', 'gpsd status' );
f = ne_dialg(f, 'add', 1, 0, 'pToFgpsd_statusdata', 'data' );
f = ne_dialg(f, 'add', 1, 0, 'pToFgpsd_statuserror', 'error' );
f = ne_dialg(f, 'add', 0, 1, 'gToFiwg', 'IWG1' );
f = ne_dialg(f, 'add', 1, 0, 'pToFiwgl', 'Lat' );
f = ne_dialg(f, 'add', 1, 0, 'pToFiwglon', 'Lon' );
f = ne_dialg(f, 'add', 1, 0, 'pToFiwgt', 'Temp' );
f = ne_dialg(f, 'add', 1, 0, 'pToFiwgp', 'Pres' );
f = ne_dialg(f, 'add', 1, 0, 'pToFiwgs', 'Speed' );
f = ne_dialg(f, 'add', 1, 0, 'pToFiwgm', 'Mach' );
f = ne_dialg(f, 'add', 1, 0, 'pToFiwga', 'Alt' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'add', 0, 1, 'gToFa', 'Attitude' );
f = ne_dialg(f, 'add', 1, 0, 'pToFaa', 'Attack' );
f = ne_dialg(f, 'add', 1, 0, 'pToFap', 'Pitch' );
f = ne_dialg(f, 'add', 1, 0, 'pToFar', 'Roll' );
f = ne_dialg(f, 'add', 1, 0, 'pToFass', 'Side Slip' );
f = ne_dialg(f, 'add', 1, 0, 'pToFad', 'Drift' );
f = ne_dialg(f, 'add', 1, 0, 'pToFasz', 'SZ' );
f = ne_dialg(f, 'add', 1, 0, 'pToFaaz', 'AZ' );
f = ne_dialg(f, 'add', 1, 0, 'pToFa_az', 'Az' );
f = ne_dialg(f, 'add', 1, 0, 'pToFat', 'Track' );
f = ne_dialg(f, 'add', 0, 1, 'gToFw', 'Wind' );
f = ne_dialg(f, 'add', 1, 0, 'pToFwvv', 'Vert Vel' );
f = ne_dialg(f, 'add', 1, 0, 'pToFwvs', 'Vert Speed' );
f = ne_dialg(f, 'add', 1, 0, 'pToFwd', 'Dir' );
f = ne_dialg(f, 'add', 1, 0, 'pToFws', 'Speed' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'add', 0, 1, 'gToFiwg1_stat', 'IWG1 Stat' );
f = ne_dialg(f, 'add', 1, 0, 'pToFiwg1_statcp', 'Cabin Press' );
f = ne_dialg(f, 'add', 1, 0, 'pToFiwg1_stattd', 'T Drift' );
f = ne_dialg(f, 'add', 1, 0, 'pToFiwg1_stats', 'Stale' );
f = ne_dialg(f, 'add', 0, 1, 'gToFiris', 'Iris' );
f = ne_dialg(f, 'add', 1, 0, 'pToFirisv', 'V' );
f = ne_dialg(f, 'add', 1, 0, 'pToFiriss', 'Step' );
f = ne_dialg(f, 'add', 1, 0, 'pToFirisstale', 'Stale' );
f = ne_listdirs(f, 'ToF_Data_Dir', 13);
f = ne_dialg(f, 'newcol');
ne_dialg(f, 'resize');