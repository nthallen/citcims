function ptriplehs(varargin);
% ptriplehs( [...] );
% Horiba Status
h = ne_dstat({
  'Dilution_SP_Stat', 'HoribaS', 0; ...
	'Dilution_Stat', 'HoribaS', 1; ...
	'Dilution_Cmd_Stat', 'HoribaS', 10; ...
	'IonSource_SP_Stat', 'HoribaS', 2; ...
	'IonSource_Stat', 'HoribaS', 3; ...
	'IonSource_Cmd_Stat', 'HoribaS', 11; ...
	'Reagent_SP_Stat', 'HoribaS', 4; ...
	'Reagent_Stat', 'HoribaS', 5; ...
	'Reagent_Cmd_Stat', 'HoribaS', 12; ...
	'Zero_SP_Stat', 'HoribaS', 6; ...
	'Zero_Stat', 'HoribaS', 7; ...
	'Zero_Cmd_Stat', 'HoribaS', 13 }, 'Status', varargin{:} );
