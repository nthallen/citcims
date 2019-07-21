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
% With rec = 'ToFeng_1':
%   handles.data.(rec) has the following members:
%     n_alloc The length of each vector under vars
%     n_recd  The number of records received
%     vars    A struct with vectors for each variable
%     handles.data.(rec).vars.(varname)  n_alloc x 1 vector
%     handles.data.(rec).vars.(varname)(handles.data.(rec).n_recd) is
%       the most recent datum.
%----------------------------------------------------------------------
% Perform analysis to calculate relevant output values
%   Persistent variables can be added to the handles data structure.
%----------------------------------------------------------------------
% CALCULATIONS GO HERE
set(handles.NToF,'String',num2str(handles.ToFdata.N));
handles.ToFdata.N;
t3=handles.data.('ToFeng_1').vars.('T3_1Hz')(handles.data.('ToFeng_1').n_recd);
t4=handles.data.('ToFeng_1').vars.('T4_1Hz')(handles.data.('ToFeng_1').n_recd);
P=handles.data.('ToFeng_1').vars.('InL_P')(handles.data.('ToFeng_1').n_recd);
dil=handles.data.('ToFeng_1').vars.('InL_P')(handles.data.('ToFeng_1').n_recd);
Insl=handles.data.('ToFeng_5').vars.('Insl_Step')(handles.data.('ToFeng_5').n_recd);
if handles.ToFdata.N > 5
    tmln.time=ft2ts(handles.ToFdata.strc.TimeZero)+handles.ToFdata.bufTime;
    tmln.mass=proc_spec(handles.ToFdata.dat,handles.ToFdata.map,handles.ToFdata.bl1,handles.ToFdata.bl2,handles.ToFdata.N);
    [tmln.t3,tmln.t4]=convert_T(t3,t4,handles.ToFdata.TCal);
    handles = check_growing_vectors(handles,'tmln',tmln);
 %   plot(handles.ToFdata.ax1,time2jd(handles.data.tmln.vars.time),handles.data.tmln.vars.mass(:,86),'.-');
 display(handles.data.tmln.vars.mass(handles.data.tmln.n_recd,86));
 %   drawnow;
end
display(handles.data.tmln.n_recd)
if mod(handles.data.tmln.n_recd,60) == 0
    if sum(handles.ToFdata.dat60(9000:length(handles.ToFdata.dat60)))>10000
        handles.ToFdata.mzc=mass_cal(handles.ToFdata.mz,handles.ToFdata.dat60);
        [handles.ToFdata.map,handles.ToFdata.bl1,handles.ToFdata.bl2]=mass_map_rt(400,handles.ToFdata.mzc);

    end
    handles.ToFdata.dat60=handles.ToFdata.dat0;
end
    
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
    v3 = NaN;
    % Note: fprintf() on a udp object apparently does not support all
    % the conversions that fprintf() on a file does, so I format the
    % string with sprintf first.
    str = sprintf('CIT-CIMS,%s,%d,%.7e,%.7e,%.7e\n', char(t), status, v1, v2, v3);
    fprintf(handles.ToFdata.udp,'%s',str);
end
