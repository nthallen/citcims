function ptripleasz(varargin);
% ptripleasz( [...] );
% Attitude SZ
h = timeplot({'Solar_Zenith','Sun_Elev_AC','Solar_Zenith','Sun_Elev_AC'}, ...
      'Attitude SZ', ...
      'SZ', ...
      {'Solar\_Zenith','Sun\_Elev\_AC','Solar\_Zenith','Sun\_Elev\_AC'}, ...
      varargin{:} );
