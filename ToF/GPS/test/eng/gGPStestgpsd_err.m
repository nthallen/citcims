function fig = gGPStestgpsd_err(varargin);
% gGPStestgpsd_err(...)
% gpsd err
ffig = ne_group(varargin,'gpsd err','pGPStestgpsd_errtime','pGPStestgpsd_errdist','pGPStestgpsd_errtrack','pGPStestgpsd_errspeed','pGPStestgpsd_errclimb');
if nargout > 0 fig = ffig; end
