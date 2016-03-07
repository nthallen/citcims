function fig = gToFgpsd_toff(varargin);
% gToFgpsd_toff(...)
% gpsd toff
ffig = ne_group(varargin,'gpsd toff','pToFgpsd_toffsec','pToFgpsd_toffnsec');
if nargout > 0 fig = ffig; end
