function varargout = tgui(varargin)
% TGUI MATLAB code for tgui.fig
%      TGUI, by itself, creates a new TGUI or raises the existing
%      singleton*.
%
%      H = TGUI returns the handle to a new TGUI or the handle to
%      the existing singleton*.
%
%      TGUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in TGUI.M with the given input arguments.
%
%      TGUI('Property','Value',...) creates a new TGUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before tgui_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to tgui_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help tgui

% Last Modified by GUIDE v2.5 18-Jul-2019 11:59:28

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @tgui_OpeningFcn, ...
                   'gui_OutputFcn',  @tgui_OutputFcn, ...
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


% --- Executes just before tgui is made visible.
function tgui_OpeningFcn(hObject, ~, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to tgui (see VARARGIN)

% Choose default command line output for tgui
handles.output = hObject;
handles.ToFdata.running = false;
handles.ToFdata.othercounter = 0;
val = get(handles.Run_Button,'value');
fprintf(1,'Original value is %d\n', val);

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes tgui wait for user response (see UIRESUME)
% uiwait(handles.tgui_fig);


% --- Outputs from this function are returned to the command line.
function varargout = tgui_OutputFcn(~, ~, handles) 
varargout{1} = handles.output;


% --- Executes on button press in Run_Button.
function Run_Button_Callback(hObject, ~, handles)
% hObject    handle to Run_Button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if handles.ToFdata.running
    set(hObject,'string','Run');
    set(hObject,'value',0); % This is not how the button value works
    handles.ToFdata.running = false;
    guidata(hObject,handles);
    add_data_field(handles,handles.tgui_fig,'MyVar');
else
    set(hObject,'string','Stop');
    % set(hObject,'value',1); % This is not how the button value works
    handles.ToFdata.running = true;
    guidata(hObject,handles);
    octr = handles.ToFdata.othercounter;
    j = 0;
    % Now running
    while true
        handles = guidata(hObject);
        if handles.ToFdata.othercounter ~= octr
            fprintf(1,'othercounter = %d\n', handles.ToFdata.othercounter);
            octr = handles.ToFdata.othercounter;
        end
        if ~handles.ToFdata.running
            break;
        end
        j = j + 1;
        pause(0.05);
    end
    fprintf(1,'j = %d\n', j);
end


% --- Executes on button press in Other_Button.
function Other_Button_Callback(hObject, ~, handles)
% hObject    handle to Other_Button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
val = get(handles.Run_Button,'value');
fprintf(1,'Run_Button value is %d\n', val);
handles.ToFdata.othercounter = handles.ToFdata.othercounter+1;
guidata(hObject, handles);
% NOTE: Is is indeed necessary to write handles back to the object
% and retrieve it from the object on each iteration, or the changes
% will not propagate correctly. Also, the Run_Button must be set
% as Interruptable so the Other_Button_Callback can occur during
% pauses.
