function pToFts(varargin);
% pToFts( [...] );
% Turbos Speed
h = timeplot({'TPA_Spd','TPB_Spd'}, ...
      'Turbos Speed', ...
      'Speed', ...
      {'TPA\_Spd','TPB\_Spd'}, ...
      varargin{:} );