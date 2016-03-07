function fig = gToFs(varargin);
% gToFs(...)
% System
ffig = ne_group(varargin,'System','pToFscpu','pToFsd','pToFstd');
if nargout > 0 fig = ffig; end
