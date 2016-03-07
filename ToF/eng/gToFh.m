function fig = gToFh(varargin);
% gToFh(...)
% Horiba
ffig = ne_group(varargin,'Horiba','pToFhd','pToFhis','pToFhf','pToFhp','pToFhs','pToFhstale');
if nargout > 0 fig = ffig; end
