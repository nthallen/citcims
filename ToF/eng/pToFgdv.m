function pToFgdv(varargin);
% pToFgdv( [...] );
% Gas Deck Volts
h = timeplot({'AI_SP1'}, ...
      'Gas Deck Volts', ...
      'Volts', ...
      {'AI\_SP1'}, ...
      varargin{:} );
