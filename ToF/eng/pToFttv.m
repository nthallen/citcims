function pToFttv(varargin);
% pToFttv( [...] );
% Turbos TV
h = timeplot({'TPA_TV','TPB_TV','TPBx_TV'}, ...
      'Turbos TV', ...
      'TV', ...
      {'TPA\_TV','TPB\_TV','TPBx\_TV'}, ...
      varargin{:} );
