function fig = gToFiwg(varargin);
% gToFiwg(...)
% IWG1
ffig = ne_group(varargin,'IWG1','pToFiwgl','pToFiwglon','pToFiwgt','pToFiwgp','pToFiwgs','pToFiwgm','pToFiwga');
if nargout > 0 fig = ffig; end
