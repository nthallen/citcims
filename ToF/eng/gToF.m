function fig = gToF(varargin);
% gToF(...)
% gpsd
ffig = ne_group(varargin,'gpsd','pToFmode','pToFtime','pToFlat','pToFlon','pToFalt','pToFtrack','pToFspeed','pToFclimb','pToFsats','pToFstale');
if nargout > 0 fig = ffig; end
