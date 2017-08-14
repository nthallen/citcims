function fig = gToFh(varargin);
% gToFh(...)
% Horiba
ffig = ne_group(varargin,'Horiba','pToFhdf','pToFhisf','pToFhff','pToFhhp','pToFhs','pToFhstale');
if nargout > 0 fig = ffig; end
