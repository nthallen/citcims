function fig = gGPStest(varargin);
% gGPStest(...)
% gpsd
ffig = ne_group(varargin,'gpsd','pGPStestmode','pGPStesttime','pGPStestlat','pGPStestlon','pGPStestalt','pGPStesttrack','pGPStestspeed','pGPStestclimb','pGPStestsats','pGPSteststale');
if nargout > 0 fig = ffig; end
