function fig = gToFh(varargin);
% gToFh(...)
% Horiba
ffig = ne_group(varargin,'Horiba','pToFhdf','pToFhs','pToFhisf','pToFhff','pToFhhp','pToFhstale');
if nargout > 0 fig = ffig; end
