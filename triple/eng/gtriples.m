function fig = gtriples(varargin);
% gtriples(...)
% Status
ffig = ne_group(varargin,'Status','ptriplescpu','ptriplesd','ptriplessws','ptriplestd');
if nargout > 0 fig = ffig; end
