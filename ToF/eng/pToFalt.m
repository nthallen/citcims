function pToFalt(varargin);
% pToFalt( [...] );
% gpsd alt
h = timeplot({'gpsd_alt'}, ...
      'gpsd alt', ...
      'alt', ...
      {'gpsd\_alt'}, ...
      varargin{:} );
