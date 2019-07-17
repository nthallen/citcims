function handles = process_ToF_records(handles)
% Responsible for analyzing the handles.ToFdata.dat vector
% using handles.data.ToFeng_1.vars.(var) arrays
%
% Relevant variables:
%  handles.ToFdata.iBB = -1; % previous iBuf value
%  handles.ToFdata.iBuf_d = -1; % current iBuf value from TwGetDestriptor
%  handles.ToFdata.N = 0; % number of spectra processed this round
%  handles.ToFdata.iBufs = zeros(20,1); % iBuf values for the first min(N,20) spectra
%  handles.ToFdata.bufTimes = zeros(20,1); % bufTimes for the first min(N,20) spectra
%  handles.ToFdata.dat = handles.ToFdata.dat0; % sum of N spectra
%  handles.ToFdata.NbrSamples = str2double(calllib('TofDaqDll','TwGetDaqParameter','NbrSamples'));
%
%----------------------------------------------------------------------
% Perform analysis to calculate relevant output values
%   Persistent variables can be added to the handles data structure.
%----------------------------------------------------------------------
% CALCULATIONS GO HERE

%----------------------------------------------------------------------
% Reinitialize N and dat
%----------------------------------------------------------------------
handles.ToFdata.N = 0;
handles.ToFdata.dat = handles.ToFdata.dat0;

%----------------------------------------------------------------------
% Format and transmit Status Packet via handles.ToFdata.udp
% status is bit-mapped:
%  Bit  Value Meaning
%   0 -   1   Ready
%   1 -   2   Operating
%   2 -   4   Calibrating
%   3 -   8   Warning
%   4 -  16   Invalid
%   5 -  32   Failed
%----------------------------------------------------------------------
if handles.ToFdata.SendStatus
    t = datetime('now','timezone','utc','format','yyyy-MM-dd''T''HH:mm:ss.SSS');
    status = 3;
    v1 = NaN;
    v2 = NaN;
    % Note: fprintf() on a udp object apparently does not support all
    % the conversions that fprintf() on a file does, so I format the
    % string with sprintf first.
    str = sprintf('CIT-CIMS,%s,%d,%.7e,%.7e\n', string(t), status, v1, v2);
    fprintf(handles.ToFdata.udp,'%s',str);
end
