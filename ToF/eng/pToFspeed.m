function pToFspeed(varargin);
% pToFspeed( [...] );
% gpsd speed
h = timeplot({'gpsd_speed'}, ...
      'gpsd speed', ...
      'speed', ...
      {'gpsd\_speed'}, ...
      varargin{:} );
