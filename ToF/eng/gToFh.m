function fig = gToFh(varargin);
% gToFh(...)
% Horiba
ffig = ne_group(varargin,'Horiba','pToFhff','pToFhs','pToFhisf','pToFhdf','pToFhhp','pToFhstale');
if nargout > 0 fig = ffig; end
