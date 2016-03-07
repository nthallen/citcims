function fig = gToFsws(varargin);
% gToFsws(...)
% SW Status
ffig = ne_group(varargin,'SW Status','pToFswsaii','pToFswsswf','pToFswsip','pToFswssws');
if nargout > 0 fig = ffig; end
