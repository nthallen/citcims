function fig = gToFi(varargin);
% gToFi(...)
% Inlet
ffig = ne_group(varargin,'Inlet','pToFip','pToFitv','pToFis','pToFistale','pToFistatus');
if nargout > 0 fig = ffig; end
