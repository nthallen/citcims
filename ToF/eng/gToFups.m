function fig = gToFups(varargin);
% gToFups(...)
% UPS
ffig = ne_group(varargin,'UPS','pToFupsm','pToFupsv','pToFupsf','pToFupsi','pToFupsl','pToFupst','pToFupstime');
if nargout > 0 fig = ffig; end
