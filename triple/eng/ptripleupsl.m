function ptripleupsl(varargin);
% ptripleupsl( [...] );
% UPS Load
h = timeplot({'UPS_LoadPct','UPS_Capacity'}, ...
      'UPS Load', ...
      'Load', ...
      {'UPS\_LoadPct','UPS\_Capacity'}, ...
      varargin{:} );