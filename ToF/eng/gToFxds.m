function fig = gToFxds(varargin);
% gToFxds(...)
% nXDS
ffig = ne_group(varargin,'nXDS','pToFxdsv','pToFxdsi','pToFxdsw','pToFxdst','pToFxdsf','pToFxdss');
if nargout > 0 fig = ffig; end
