function fig = gToFfv(varargin);
% gToFfv(...)
% Fly Valve
ffig = ne_group(varargin,'Fly Valve','pToFfvs','pToFfvp','pToFfv_p','pToFfvstatus');
if nargout > 0 fig = ffig; end
