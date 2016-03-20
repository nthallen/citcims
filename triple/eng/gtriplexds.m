function fig = gtriplexds(varargin);
% gtriplexds(...)
% nXDS
ffig = ne_group(varargin,'nXDS','ptriplexdsv','ptriplexdsi','ptriplexdsw','ptriplexdst','ptriplexdsf','ptriplexdss');
if nargout > 0 fig = ffig; end
