function fig = gGPStestgpsd_toff(varargin);
% gGPStestgpsd_toff(...)
% gpsd toff
ffig = ne_group(varargin,'gpsd toff','pGPStestgpsd_toffsec','pGPStestgpsd_toffnsec');
if nargout > 0 fig = ffig; end
