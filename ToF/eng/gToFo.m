function fig = gToFo(varargin);
% gToFo(...)
% Octopole
ffig = ne_group(varargin,'Octopole','pToFoa','pToFob','pToFod');
if nargout > 0 fig = ffig; end
