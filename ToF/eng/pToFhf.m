function pToFhf(varargin);
% pToFhf( [...] );
% Horiba Fluorine
h = timeplot({'FFlow','FFlowSP'}, ...
      'Horiba Fluorine', ...
      'Fluorine', ...
      {'FFlow','FFlowSP'}, ...
      varargin{:} );