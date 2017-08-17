function fig = gtripleh(varargin);
% gtripleh(...)
% Horiba
ffig = ne_group(varargin,'Horiba','ptriplehd','ptriplehis','ptriplehr','ptriplehz','ptriplehs','ptriplehstale');
if nargout > 0 fig = ffig; end
