function pGPStestgpsd_errspeed(varargin);
% pGPStestgpsd_errspeed( [...] );
% gpsd err speed
h = timeplot({'gpsd_eps'}, ...
      'gpsd err speed', ...
      'speed', ...
      {'gpsd\_eps'}, ...
      varargin{:} );
