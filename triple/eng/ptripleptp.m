function ptripleptp(varargin);
% ptripleptp( [...] );
% PT Pres
h = timeplot({'Pressure1000T','Pressure100T'}, ...
      'PT Pres', ...
      'Pres', ...
      {'Pressure1000T','Pressure100T'}, ...
      varargin{:} );
