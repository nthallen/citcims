function pToFxdst(varargin);
% pToFxdst( [...] );
% nXDS T
h = timeplot({'nX0CtrlrT','nX1CtrlrT'}, ...
      'nXDS T', ...
      'T', ...
      {'nX0CtrlrT','nX1CtrlrT'}, ...
      varargin{:} );
