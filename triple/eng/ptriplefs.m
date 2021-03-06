function ptriplefs(varargin);
% ptriplefs( [...] );
% Flows Status
h = ne_dstat({
  'Reagent_Valve_S', 'H_DIO_B', 0; ...
	'ScrubAir_Valve', 'H_DIO_C', 0; ...
	'Labelled_cal_scrub', 'H_DIO_C', 1; ...
	'Labelled_cal_bypass', 'H_DIO_C', 2; ...
	'Normal_cal_scrub', 'H_DIO_C', 3; ...
	'Normal_cal_bypass', 'H_DIO_C', 4 }, 'Status', varargin{:} );
