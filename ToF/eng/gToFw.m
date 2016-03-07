function fig = gToFw(varargin);
% gToFw(...)
% Wind
ffig = ne_group(varargin,'Wind','pToFwvv','pToFwvs','pToFwd','pToFws');
if nargout > 0 fig = ffig; end
