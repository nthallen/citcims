function fig = gToFgd(varargin);
% gToFgd(...)
% Gas Deck
ffig = ne_group(varargin,'Gas Deck','pToFgdt','pToFgdmbar','pToFgdpsi','pToFgdv');
if nargout > 0 fig = ffig; end
