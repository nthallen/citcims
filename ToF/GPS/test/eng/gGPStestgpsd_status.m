function fig = gGPStestgpsd_status(varargin);
% gGPStestgpsd_status(...)
% gpsd status
ffig = ne_group(varargin,'gpsd status','pGPStestgpsd_statusdata','pGPStestgpsd_statuserror');
if nargout > 0 fig = ffig; end
