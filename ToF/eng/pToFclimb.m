function pToFclimb(varargin);
% pToFclimb( [...] );
% gpsd climb
h = timeplot({'gpsd_climb'}, ...
      'gpsd climb', ...
      'climb', ...
      {'gpsd\_climb'}, ...
      varargin{:} );
