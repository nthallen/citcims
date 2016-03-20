function pToFhs(varargin);
% pToFhs( [...] );
% Horiba Status
h = ne_dstat({
  'DilFlowSP_Stat', 'HoribaS', 0; ...
	'DilFlow_Stat', 'HoribaS', 1; ...
	'IonSrcFlowSP_Stat', 'HoribaS', 2; ...
	'IonSrcFlow_Stat', 'HoribaS', 3; ...
	'FFlowSP_Stat', 'HoribaS', 4; ...
	'FFlow_Stat', 'HoribaS', 5; ...
	'HoribaPSP_Stat', 'HoribaS', 6; ...
	'HoribaP_Stat', 'HoribaS', 7; ...
	'HCmd_Stat', 'HoribaS', 8 }, 'Status', varargin{:} );