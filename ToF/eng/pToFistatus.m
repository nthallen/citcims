function pToFistatus(varargin);
% pToFistatus( [...] );
% Inlet Status
h = ne_dstat({
  'Insl_Out', 'Insl_Stat', 3; ...
	'Insl_Stop', 'Insl_Stat', 2; ...
	'Insl_Limit', 'Insl_Stat', 1; ...
	'Insl_Home', 'Insl_Stat', 0 }, 'Status', varargin{:} );
