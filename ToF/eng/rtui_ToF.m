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
   loadlibrary(['C:\tofwerk\TofDaq_1.98_API\bin\x64\TofDaqDll.dll'],['C:\tofwerk\TofDaq_1.98_API\include\TofDaqDll.h']);
end

handles.output = hObject;
handles.ToFdata.ToF_initialized = false;
handles.ToFdata.strc = struct('NbrSamples',int32(0));
handles.ToFdata.iBB = -1; % previous iBuf value
handles.ToFdata.N = 0; % number of spectra processed this round
handles.ToFdata.running = false;
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
    handles.ToFdata.running = true;
    set(handles.RunStatus,'String','Running');
    handles = setup_json_connection(handles, '10.0.0.155', 80);
    guidata(hObject, handles);
    while true
        handles = guidata(hObject);
        if ~handles.ToFdata.running
            break;
        end
        if ~handles.ToFdata.ToF_initialized
            if calllib('TofDaqDll','TwTofDaqRunning')
                handles = ToF_setup(handles);
                guidata(hObject,handles);
            end
        end
        if handles.data_conn.t.BytesAvailable
        end
        j = j + 1;
        pause(0.05);
    end
    handles = close_json_connection(handles);
    set(handles.RunStatus,'String','Idle');
else
    handles.ToFdata.running = false;
end
guidata(hObject, handles);

function handles = setup_json_connection(handles, hostname, hostport)
handles.data_conn.n = 0;
handles.data_conn.t = tcpip(hostname, hostport,'Terminator','}', ...
    'InputBufferSize',4096);
% handles.data_conn.t.BytesAvailableFcn = { @BytesAvailable, hObject };
fopen(handles.data_conn.t);
handles.data_conn.connected = 1;

function handles = close_json_connection(handles)
fclose(handles.data_conn.t);
delete(handles.data_conn.t);
handles.data_conn.connected = 0;

function handles = ToF_setup(handles)
handles.ToFdata.NbrSamples = str2num(calllib('TofDaqDll','TwGetDaqParameter','NbrSamples'));
handles.ToFdata.dat0 = zeros(handles.ToFdata.NbrSamples,1);
handles.ToFdata.dat = handles.ToFdata.dat0;
handles.ToFdata.raw = handles.ToFdata.dat0;
handles.ToFdata.iBB = -1; % Current iBuf
handles.ToFdata.strc = struct('NbrSamples',int32(0));
handles.ToFdata.mz = double([1:double(handles.ToFdata.NbrSamples)]);

% TwGetSpecXaxisFromShMem
%   0: TwDaqRecNotRunning
%   4: TwSuccess
%   5: TwError
%   6: TwOutOfBounds
[res,handles.ToFdata.mz] = calllib('TofDaqDll','TwGetSpecXaxisFromShMem',mz,1,[],0.0);
if res ~= 4
    error('TwGetSpecXaxisFromShMem returned %d\n', res);
end

% --- Executes when data is available.
function BytesAvailable(obj, event, hObject)
handles = guidata(hObject);
if handles.data_conn.connected == 0
    return;
end
s = fgets(obj);
if isempty(s)
    Run_Callback(hObject, event, handles);
end
dp = loadjson(s);
handles.data_conn.n = handles.data_conn.n+1;
set(handles.Nrecs,'String',num2str(handles.data_conn.n));
guidata(hObject,handles);
process_record(hObject, handles, dp);
drawnow;

% process_record should be generic based on the conventions
% I am using for received JSON data. This should build up
% structures within handles.data.(rec):
%   n_alloc The length of each vector under vars
%   n_recd  The number of records received
%   vars    A struct with vectors for each variable
%   vars.(varname)  n_alloc x 1 vector
function process_record(hObject, handles, dp)
min_alloc = 10000;
rec = dp.Record;
dp = rmfield(dp,'Record');
flds = fieldnames(dp);
if ~isfield(handles,'data') || ~isfield(handles.data, rec)
    % initialize variable
    handles.data.(rec).n_alloc = min_alloc;
    handles.data.(rec).n_recd = 0;
    for i = 1:length(flds)
        handles.data.(rec).vars.(flds{i}) = zeros(min_alloc,1) * NaN;
    end
end
handles.data.(rec).n_recd = handles.data.(rec).n_recd + 1;
if handles.data.(rec).n_recd > handles.data.(rec).n_alloc
    for i = 1:length(flds)
        handles.data.(rec).vars.(flds{i}) = [
            handles.data.(rec).vars.(flds{i});
            zeros(min_alloc,1) * NaN ];
    end
    handles.data.(rec).n_alloc = handles.data.(rec).n_alloc + min_alloc;
end
for i = 1:length(flds)
    if isnumeric(dp.(flds{i}))
        handles.data.(rec).vars.(flds{i})(handles.data.(rec).n_recd) = ...
            dp.(flds{i});
    end
end
guidata(hObject,handles);
update_graphics(handles, rec);

%
function update_graphics(handles, rec)
if strcmp(rec,'ToFeng_1')
    x = 1:handles.data.ToFeng_1.n_recd;
    T = handles.data.ToFeng_1.vars.TToFeng_1(x);
    v = T > (T(end)-200);
    x = x(v);
    T = T(x);
    T = T - T(1);
    TPA_Cmon = handles.data.ToFeng_1.vars.TPA_Cmon(x);
    TPB_Cmon = handles.data.ToFeng_1.vars.TPB_Cmon(x);
    plot(handles.axes1, T, TPA_Cmon, T, TPB_Cmon);
    title(handles.axes1, 'TPA\_Cmon, TPB\_Cmon');
    xlim(handles.axes1, [0 200]);
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
