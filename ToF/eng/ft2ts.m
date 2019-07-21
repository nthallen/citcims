function y=ft2ts(x)

% convert 'filetime' - 100 nanosecond periods since Jan 1 1601 -- to
% 'timestamp' seconds since Jan 1 1970
% Note: Actually converts to a double first as matlab does not do math on
% 64-bit numbers.... this should work for a very long time, but not
% forever.

x=double(x);
dt=134775-1;%dt=daysact('1-jan-1601','1-jan-1970')+1;

y=(x-dt*24*60*60*1e7)*1e-7;