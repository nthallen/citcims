function ptripleiwga(varargin);
% ptripleiwga( [...] );
% IWG1 Alt
h = timeplot({'GPS_MSL_Alt','Press_Alt','Radar_Alt','WGS_84_Alt','GPS_MSL_Alt','Press_Alt','Radar_Alt','WGS_84_Alt'}, ...
      'IWG1 Alt', ...
      'Alt', ...
      {'GPS\_MSL\_Alt','Press\_Alt','Radar\_Alt','WGS\_84\_Alt','GPS\_MSL\_Alt','Press\_Alt','Radar\_Alt','WGS\_84\_Alt'}, ...
      varargin{:} );
