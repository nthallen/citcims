function pToFgpsd_errtime(varargin);
% pToFgpsd_errtime( [...] );
% gpsd err time
h = timeplot({'gpsd_ept'}, ...
      'gpsd err time', ...
      'time', ...
      {'gpsd\_ept'}, ...
      varargin{:} );
