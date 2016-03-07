function pToFhp(varargin);
% pToFhp( [...] );
% Horiba Pressure
h = timeplot({'HoribaP','HoribaPSP'}, ...
      'Horiba Pressure', ...
      'Pressure', ...
      {'HoribaP','HoribaPSP'}, ...
      varargin{:} );
