function fig = gToFgpsd_err(varargin);
% gToFgpsd_err(...)
% gpsd err
ffig = ne_group(varargin,'gpsd err','pToFgpsd_errtime','pToFgpsd_errdist','pToFgpsd_errtrack','pToFgpsd_errspeed','pToFgpsd_errclimb');
if nargout > 0 fig = ffig; end
