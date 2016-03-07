function fig = gToFf(varargin);
% gToFf(...)
% Flows
ffig = ne_group(varargin,'Flows','pToFfs','pToFfs2','pToFfzf','pToFft');
if nargout > 0 fig = ffig; end
