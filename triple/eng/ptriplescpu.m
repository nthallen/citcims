function ptriplescpu(varargin);
% ptriplescpu( [...] );
% Status CPU
h = timeplot({'CPU_Pct'}, ...
      'Status CPU', ...
      'CPU', ...
      {'CPU\_Pct'}, ...
      varargin{:} );
