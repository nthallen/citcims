function pToFhs(varargin);
% pToFhs( [...] );
% Horiba Status
h = ne_dstat({
  'DilFlow_SP_Stat', 'HoribaS', 0; ...
	'DilFlow_Stat', 'HoribaS', 1; ...
	'IonSrcFlow_SP_Stat', 'HoribaS', 2; ...
	'IonSrcFlow_Stat', 'HoribaS', 3; ...
	'FFlow_SP_Stat', 'HoribaS', 4; ...
	'FFlow_Stat', 'HoribaS', 5; ...
	'HoribaP_SP_Stat', 'HoribaS', 6; ...
	'HoribaP_Stat', 'HoribaS', 7; ...
	'Horiba_CS', 'HoribaS', 10 }, 'Status', varargin{:} );
