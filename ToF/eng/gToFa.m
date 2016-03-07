function fig = gToFa(varargin);
% gToFa(...)
% Attitude
ffig = ne_group(varargin,'Attitude','pToFaa','pToFap','pToFar','pToFass','pToFad','pToFasz','pToFaaz','pToFa_az','pToFat');
if nargout > 0 fig = ffig; end
