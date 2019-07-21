function varargout = rtui_ToF(varargin)
% RTUI_TOF MATLAB code for rtui_ToF.fig
%      RTUI_TOF, by itself, creates a new RTUI_TOF or raises the existing
%      singleton*.
%
%      H = RTUI_TOF returns the handle to a new RTUI_TOF or the handle to
%      the existing singleton*.
%
%      RTUI_TOF('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in RTUI_TOF.M with the given input arguments.
%
%      RTUI_TOF('Property','Value',...) creates a new RTUI_TOF or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before rtui_ToF_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to rtui_ToF_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help rtui_ToF

% Last Modified by GUIDE v2.5 08-Oct-2012 17:53:23

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @rtui_ToF_OpeningFcn, ...
                   'gui_OutputFcn',  @rtui_ToF_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before rtui_ToF is made visible.
function rtui_ToF_OpeningFcn(hObject, ~, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to rtui_ToF (see VARARGIN)

if ~libisloaded('TofDaqDll')
    disp('Load TofTAQ library')
   loadlibrary('C:\tofwerk\ADQ1600-new\TofDaq_1.98_API\bin\x64\TofDaqDll.dll', ...
       'C:\tofwerk\ADQ1600-new\TofDaq_1.98_API\include\TofDaqDll.h');
end

handles.output = hObject;
handles.ToFdata.ToF_initialized = false;
handles.ToFdata.strc = struct('NbrSamples',int32(0));
handles.ToFdata.iBB = -1; % previous iBuf value
handles.ToFdata.iBuf_d = -1; % current iBuf value from TwGetDestriptor
handles.ToFdata.N = 0; % number of spectra processed this round
handles.ToFdata.running = false;
handles.ToFdata.pause_time = 0.05;
handles.ToFdata.bufTime = 1;
handles.ToFdata.iBufs = zeros(20,1);
handles.ToFdata.bufTimes = zeros(20,1);
handles.ToFdata.SendStatus = false;
handles.ToFdata.TCal = T_cal_crv;

guidata(hObject, handles);

% --- Outputs from this function are returned to the command line.
function varargout = rtui_ToF_OutputFcn(~, ~, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

% --- Executes on button press in Run.
function Run_Callback(hObject, ~, handles)
% hObject    handle to Run (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Run
if ~handles.ToFdata.running
    %---------------------------
    % Setup for 'Run' mode
    %---------------------------
    handles.ToFdata.running = true;
    set(handles.Run,'String','Stop');
    set(handles.RunStatus,'String','Running');
    handles = setup_json_connection(handles, '10.1.1.231', 80);
    if handles.ToFdata.SendStatus
        handles.ToFdata.udp = udp('10.1.1.255',5100);
        fopen(handles.ToFdata.udp);
    end
   %handles.ToFdata.h1=figure;
   %handles.ToFdata.ax1=gca;

    guidata(hObject, handles);
    
    %---------------------------
    % 'Run' loop
    %---------------------------
       iterations=0;
    while true
     
         %fprintf(1,'111: ibb: %d, iBuf_d: %d\n', handles.ToFdata.iBB, handles.ToFdata.iBuf_d);
        handles = guidata(hObject);
         %fprintf(1,'113: ibb: %d, iBuf_d: %d\n', handles.ToFdata.iBB, handles.ToFdata.iBuf_d);
        if ~handles.ToFdata.running, break, end
        if ~handles.ToFdata.ToF_initialized
            if calllib('TofDaqDll','TwTofDaqRunning')
                handles = ToF_setup(handles);
                guidata(hObject,handles);
            end
        end
        iterations = iterations + 1;
        handles = ToF_get_descriptor(handles);
        guidata(hObject,handles);
        handles.ToFdata.pause_time = 0.05;
        % ToF_read_scan() and Read_json() Handlers here are required to
        % save handles to guidata and update handles.ToFdata.pause_time.
        
        if handles.ToFdata.iBB ~= handles.ToFdata.iBuf_d
            %display(handles.ToFdata.strc.iBuf);
            %fprintf(1,'124: iterations: %d ibb: %d, iBuf_d: %d\n', iterations, handles.ToFdata.iBB, handles.ToFdata.iBuf_d);
            iterations=0;
            handles = ToF_read_scan(handles);
            %fprintf(1,'126: ibb: %d, iBuf_d: %d\n', handles.ToFdata.iBB, handles.ToFdata.iBuf_d);
        end
       
       % if handles.data_conn.t.BytesAvailable
        %    handles = Read_json(handles);
        %end
      
        %guidata(hObject, handles);
        pause(handles.ToFdata.pause_time);
       
    end
    
    %---------------------------
    % Cleanup after Stop
    %---------------------------
    handles = close_json_connection(handles);
    if handles.ToFdata.SendStatus
        fclose(handles.ToFdata.udp);
    end
    set(handles.Run,'String','Run');
    set(handles.RunStatus,'String','Idle');
else
    handles.ToFdata.running = false;
end
guidata(hObject, handles);

function handles = setup_json_connection(handles, hostname, hostport)
handles.data_conn.n = 0;
handles.data_conn.t = tcpip(hostname, hostport,'Terminator','}', ...
    'InputBufferSize',4096);
handles.data_conn.t.BytesAvailableFcn = { @BytesAvFn, handles.Run };
fopen(handles.data_conn.t);
handles.data_conn.connected = 1;

function BytesAvFn(~,~,hObject)
handles = guidata(hObject);
handles = Read_json(handles);

function handles = close_json_connection(handles)
fclose(handles.data_conn.t);
delete(handles.data_conn.t);
handles.data_conn.connected = 0;

function handles = ToF_setup(handles)
handles.ToFdata.NbrSamples = str2double(calllib('TofDaqDll','TwGetDaqParameter','NbrSamples'));
handles.ToFdata.dat0 = zeros(handles.ToFdata.NbrSamples,1);
handles.ToFdata.dat = handles.ToFdata.dat0;
handles.ToFdata.raw = handles.ToFdata.dat0;
handles.ToFdata.dat60 = handles.ToFdata.dat0;
handles.ToFdata.iBB = -1; % Current iBuf
handles.ToFdata.strc = struct('NbrSamples',int32(0));
handles.ToFdata.mz = double(1:double(handles.ToFdata.NbrSamples));
%handles.data.tmln.mass=zeros(10000,400).*NaN;
%handles.data.tmln.time=zeros(10000,1).*NaN;
%handles.data.tmln.time=zeros(10000,1).*NaN;
%handles.data.tmln.n_alloc = 10000;
%handles.data.tmln.n_recd = 0;
%handles.ToFdata.tmln.nrec=0;

% TwGetSpecXaxisFromShMem
%   0: TwDaqRecNotRunning
%   4: TwSuccess
%   5: TwError
%   6: TwOutOfBounds
[res,handles.ToFdata.mz] = ...
    calllib('TofDaqDll','TwGetSpecXaxisFromShMem',handles.ToFdata.mz,1,[],0.0);
if ~strcmp(res,'TwSuccess')
    error('TwGetSpecXaxisFromShMem returned %d\n', res);
end
handles.ToFdata.mzc=handles.ToFdata.mz;
[handles.ToFdata.map,handles.ToFdata.bl1,handles.ToFdata.bl2]=mass_map_rt(400,handles.ToFdata.mz);
handles.ToFdata.ToF_initialized = true;

% TwGetDescriptor
%   0: TwDaqRecNotRunning
%   4: TwSuccess
%   5: TwError
function handles = ToF_get_descriptor(handles)
[res,handles.ToFdata.strc] = ...
    calllib('TofDaqDll','TwGetDescriptor',handles.ToFdata.strc);
if ~strcmp(res,'TwSuccess')
    error('TwGetDescriptor returned %s', res);
end
handles.ToFdata.iBuf_d = num2str(handles.ToFdata.strc.iBuf);

function handles = ToF_read_scan(handles)
    % TwGetBufTimeFromShMem
    %   0: TwDaqRecNotRunning
    %   4: TwSuccess
    %   5: TwError
    %   6: TwOutOfBounds
    %   7: TwNoData
    [res,handles.ToFdata.bufTime] = ...
        calllib('TofDaqDll','TwGetBufTimeFromShMem', ...
        handles.ToFdata.bufTime, handles.ToFdata.strc.iBuf, ...
        handles.ToFdata.strc.iWrite);
    if ~strcmp(res,'TwSuccess')
        error('TwGetBufTimeFromShMem returned %s', res);
    end
    handles.ToFdata.N = handles.ToFdata.N+1;
    if handles.ToFdata.N <= 20
        handles.ToFdata.iBufs(handles.ToFdata.N) = ...
            handles.ToFdata.iBuf_d;
        handles.ToFdata.bufTimes(handles.ToFdata.N) = ...
            handles.ToFdata.bufTime;
    end
    
    % TwGetTofSpectrumFromShMem
    %   0: TwDaqRecNotRunning
    %   4: TwSuccess
    %   5: TwError
    %   6: TwOutOfBounds
    %   7: TwNoData
    [res,handles.ToFdata.raw] = ...
        calllib('TofDaqDll','TwGetTofSpectrumFromShMem', ...
            handles.ToFdata.raw,0,0,handles.ToFdata.strc.iBuf,true);
    if ~strcmp(res,'TwSuccess')
        error('TwGetTofSpectrumFromShMem returned %s', res);
    end
    handles.ToFdata.iBB = handles.ToFdata.iBuf_d;
    handles.ToFdata.dat = handles.ToFdata.dat + handles.ToFdata.raw;
    handles.ToFdata.dat60 = handles.ToFdata.dat60 + handles.ToFdata.raw;
    handles.ToFdata.pause_time = 0.001;
    guidata(handles.figure1,handles);

% --- Executes when data is available.
function handles = Read_json(handles)
%tic
if handles.data_conn.connected == 0
    return;
end
%toc
%tic
s = fgets(handles.data_conn.t);
%toc
if isempty(s)
    % Run_Callback(handles.Run, 0, handles);
    handles.ToFdata.running = false;
    guidata(handles.Run,handles);
else
    dp = loadjson(s);
    handles.data_conn.n = handles.data_conn.n+1;
    set(handles.Nrecs,'String',num2str(handles.data_conn.n));
    [handles,rec] = process_json_record(handles, dp);
    if strcmp(rec,'ToFeng_1')
        handles = process_ToF_records(handles);
    %else
    %    fprintf(1,'Received rec %s\n', rec);
    end
end
handles.ToFdata.pause_time = 0.001;
guidata(handles.Run, handles);

%function handles = process_ToF_records(handles)
% Responsible for analyzing the handles.ToFdata.dat vector
% using handles.data.ToFeng_1.vars.(var) arrays

% process_json_record should be generic based on the conventions
% I am using for received JSON data. This should build up
% structures within handles.data.(rec):
%   n_alloc The length of each vector under vars
%   n_recd  The number of records received
%   vars    A struct with vectors for each variable
%   handles.data.(rec).vars.(varname)  n_alloc x 1 vector
%   handles.data.(rec).vars.(varname)(handles.data.(rec).n_recd) is
%      the most recent datum.
function [handles,rec] = process_json_record(handles, dp)
rec = dp.Record;
dp = rmfield(dp,'Record');
handles = check_growing_vectors(handles, rec, dp);
% guidata(hObject,handles);
% update_graphics(handles, rec);

function handles = check_growing_vectors(handles, rec, data)
% handles = check_growing_vectors(handles, rec, vars, vals)
% rec is the name of the record
% data is struct of scalar elements.
%   data should include a time member 
% Each variable with get a growing column vector, each of the
% same allocated length ( handles.data.(rec).n_alloc) and each
% assumed to have the same number of valid values stored
% (handles.data.(rec).n_recd).
min_alloc = 10000;
flds = fieldnames(data);
if ~isfield(handles,'data') || ~isfield(handles.data, rec)
    % initialize variable
    handles.data.(rec).n_alloc = min_alloc;
    handles.data.(rec).n_recd = 0;
    for i = 1:length(flds)
        handles.data.(rec).vars.(flds{i}) = zeros(min_alloc,size(data.(flds{i}),2)) * NaN;
    end
end
handles.data.(rec).n_recd = handles.data.(rec).n_recd + 1;
if handles.data.(rec).n_recd > handles.data.(rec).n_alloc
    for i = 1:length(flds)
        handles.data.(rec).vars.(flds{i}) = [
            handles.data.(rec).vars.(flds{i});
            zeros(min_alloc,size(data.(flds{i}),2)) * NaN ];
    end
    handles.data.(rec).n_alloc = handles.data.(rec).n_alloc + min_alloc;
end
for i = 1:length(flds)
    if isnumeric(data.(flds{i}))
        handles.data.(rec).vars.(flds{i})(handles.data.(rec).n_recd) = ...
            data.(flds{i});
    end
end

%
function handles = update_graphics(handles, rec)
if strcmp(rec,'ToFeng_1')
    % x = 1:handles.data.ToFeng_1.n_recd;
    % T = handles.data.ToFeng_1.vars.TToFeng_1(x);
    % v = T > (T(end)-200);
    % x = x(v);
    % T = T(x);
    % T = T - T(1);
    % TPA_Cmon = handles.data.ToFeng_1.vars.TPA_Cmon(x);
    % TPB_Cmon = handles.data.ToFeng_1.vars.TPB_Cmon(x);
    %plot(handles.axes1, T, TPA_Cmon, T, TPB_Cmon);
    %title(handles.axes1, 'TPA\_Cmon, TPB\_Cmon');
    %xlim(handles.axes1, [0 200]);
end

% --- Executes on button press in Export.
function Export_Callback(~, ~, handles)
% hObject    handle to Export (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
recs = fieldnames(handles.data);
for i = 1:length(recs)
    rec = recs{i};
    x = 1:handles.data.(rec).n_recd;
    flds = fieldnames(handles.data.(rec).vars);
    for j = 1:length(flds)
        fld = flds{j};
        rec_copy.(fld) = handles.data.(rec).vars.(fld)(x);
    end
    assignin('base', rec, rec_copy);
    clear rec_copy;
end
