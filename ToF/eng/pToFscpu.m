function pToFscpu(varargin);
% pToFscpu( [...] );
% System CPU
h = timeplot({'CPU_Pct'}, ...
      'System CPU', ...
      'CPU', ...
      {'CPU\_Pct'}, ...
      varargin{:} );