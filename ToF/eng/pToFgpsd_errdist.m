function pToFgpsd_errdist(varargin);
% pToFgpsd_errdist( [...] );
% gpsd err dist
h = timeplot({'gpsd_epy','gpsd_epx','gpsd_epv'}, ...
      'gpsd err dist', ...
      'dist', ...
      {'gpsd\_epy','gpsd\_epx','gpsd\_epv'}, ...
      varargin{:} );
