function pToFtwistorrstatus(varargin);
% pToFtwistorrstatus( [...] );
% Twis Torr Status
h = timeplot({'TTA_Status','TTB_Status'}, ...
      'Twis Torr Status', ...
      'Status', ...
      {'TTA\_Status','TTB\_Status'}, ...
      varargin{:} );
