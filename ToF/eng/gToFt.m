function fig = gToFt(varargin);
% gToFt(...)
% Turbos
ffig = ne_group(varargin,'Turbos','pToFtt','pToFtc','pToFtok','pToFts','pToFttv','pToFtstatus');
if nargout > 0 fig = ffig; end
