function fig = gToFig(varargin);
% gToFig(...)
% Ion Gauge
ffig = ne_group(varargin,'Ion Gauge','pToFigp','pToFigs','pToFigstat');
if nargout > 0 fig = ffig; end
