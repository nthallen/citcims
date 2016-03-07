function fig = gToFgpsd_status(varargin);
% gToFgpsd_status(...)
% gpsd status
ffig = ne_group(varargin,'gpsd status','pToFgpsd_statusdata','pToFgpsd_statuserror');
if nargout > 0 fig = ffig; end
