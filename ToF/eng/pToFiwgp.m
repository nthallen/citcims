function pToFiwgp(varargin);
% pToFiwgp( [...] );
% IWG1 Pres
h = timeplot({'Dynamic_Press','Static_Press'}, ...
      'IWG1 Pres', ...
      'Pres', ...
      {'Dynamic\_Press','Static\_Press'}, ...
      varargin{:} );
