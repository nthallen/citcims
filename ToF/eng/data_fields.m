classdef data_fields < handle
    % data_fields currently encompasses all the data fields in a project,
    % all assumed to be on the same page. This will need to be augmented
    % to support multiple panes or figures. Possibly a higher-level
    % class to encompass multiple pages.
    %
    % This class will keep track of the position of fields on the figure.
    properties
        fig
        figbgcolor
        opts
    %       min_y
    %       max_y
    %       min_x
    %       max_x
    %       v_padding % space at top and bottom of column
    %       v_leading % space between rows
    %       h_padding % space between edge and outer columns
    %       h_leading % space between label and text and unit
    %       col_leading % horizontal space between columns
    %       txt_padding
        cur_x
        cur_y
        records % data_records object
        fields
        % fields will be indexed like records, i.e.
        % obj.fields.(rec).vars.(var) will be an array of data_field
        % objects, allowing a variable to appear in more than one
        % location
        cur_col
        % cur_col will record fields in the current column
        % We need to keep this until the column is closed, so we can
        % adjust the column widths.
        % cur_col.fields will be a cell array of data_field objects
        % cur_col.n_rows will be a scalar count of elements in fields
        % cur_col.max_lbl_width will be the current maximum label width
        % cur_col.max_txt_width will be the current maximum text width
        graph_figs % cell array of data_fig objects
    end
    methods
        function obj = data_fields(fig_in, varargin)
            obj.fig = fig_in;
            % verify that fig is an object
            % record dimensions
            set(obj.fig,'units','pixels');
            d = get(obj.fig,'Position');
            obj.opts.min_x = 0;
            obj.opts.max_x = d(3);
            obj.opts.min_y = 0;
            obj.opts.max_y = d(4);
            obj.opts.v_padding = 10;
            obj.opts.v_leading = 3;
            obj.opts.h_padding = 20;
            obj.opts.h_leading = 0;
            obj.opts.col_leading = 15;
            obj.opts.txt_padding = 5;
            obj.opts.txt_font = 'Courier New';
            obj.opts.txt_fontsize = 10;
            for i = 1:2:length(varargin)
                fld = varargin{i};
                if isfield(obj.opts, fld)
                    obj.opts.(fld) = varargin{i+1};
                else
                    error('MATLAB:LE:badopt', 'Invalid option: "%s"', fld);
                end
            end
            obj.cur_x = obj.opts.min_x + obj.opts.h_padding;
            obj.cur_y = obj.opts.max_y;
            obj.records = data_records();
            obj.figbgcolor = get(obj.fig,'Color');
            obj.graph_figs = {};
        end
        
        function start_col(obj)
            obj.cur_col.fields = {};
            obj.cur_col.n_rows = 0;
            obj.cur_col.max_lbl_width = 0;
            obj.cur_col.max_txt_width = 0;
            obj.cur_y = obj.opts.max_y - obj.opts.v_padding;
            % obj.cur_x = obj.cur_x + obj.opts.col_leading;
        end
        
        function end_col(obj)
            % reposition txt fields according to max widths
            % txt fields are all right-justified
            %  cur_x is the left of the lbl field
            %  cur_x + max_lbl_width is the right edge of the lbl col
            %  cur_x + max_lbl_width + h_padding is left edge of txt col
            r_edge = obj.cur_x + obj.cur_col.max_lbl_width + ...
                obj.opts.h_leading + obj.cur_col.max_txt_width;
            for i=1:length(obj.cur_col.fields)
                fld = obj.cur_col.fields{i};
                pos = fld.txt.Position;
                pos(1) = r_edge - pos(3);
                fld.txt.Position = pos;
            end
            % update cur_x to the right edge of righthand fields
            % plus col_leading, so left of new column
            obj.cur_x = r_edge + obj.opts.col_leading;
        end
        
        function df = field(obj, rec_name, var_name, fmt)
            obj.records.add_record(rec_name);
            if ~isfield(obj.fields, rec_name) || ...
                    ~isfield(obj.fields.(rec_name).vars,var_name)
                obj.fields.(rec_name).vars.(var_name) = {};
            end
            df_int = data_field(rec_name, var_name, fmt, obj);
            obj.fields.(rec_name).vars.(var_name){end+1} = df_int;
            if obj.cur_y - df_int.fld_height < obj.opts.min_y + obj.opts.v_padding
                obj.end_col();
                obj.start_col();
                % we assume one row will always fit
            end
            obj.cur_col.fields{end+1} = df_int;
            obj.cur_col.n_rows = obj.cur_col.n_rows+1;
            if df_int.lbl_width > obj.cur_col.max_lbl_width
                obj.cur_col.max_lbl_width = df_int.lbl_width;
            end
            df_int.txt_width = df_int.txt_width + obj.opts.txt_padding;
            if df_int.txt_width > obj.cur_col.max_txt_width
                obj.cur_col.max_txt_width = df_int.txt_width;
            end
            obj.cur_y = obj.cur_y - df_int.fld_height;
            df_int.lbl.Position = ...
                [ obj.cur_x, obj.cur_y, df_int.lbl_width, df_int.fld_height];
            df_int.txt.Position = ...
                [ obj.cur_x + df_int.lbl_width + obj.opts.h_leading, obj.cur_y, ...
                  df_int.txt_width, ...
                  df_int.fld_height];
            obj.cur_y = obj.cur_y - obj.opts.v_leading;
            if nargout > 0; df = df_int; end
        end
        function process_record(obj,rec_name,str)
            if nargin >= 3
                obj.records.process_record(rec_name,str);
            end
            % Now go through fields and update text
            if isfield(obj.fields,rec_name)
                flds = obj.fields.(rec_name);
                vars = fieldnames(flds.vars);
                for i=1:length(vars)
                    if isfield(str,vars{i})
                        fs = flds.vars.(vars{i});
                        for j = 1:length(fs)
                            set(fs{j}.txt,'String', ...
                                fs{j}.txt_convert(str.(vars{i})));
                        end
                    end
                end
            end
            % Now go through graph_figs
            if nargin >= 3
                for i=1:length(obj.graph_figs)
                    obj.graph_figs{i}.update(rec_name);
                end
            end
        end
        function dfig = new_graph_fig(dfs)
            dfig = data_fig(dfs.records);
            dfs.graph_figs{end+1} = dfig;
        end
    end
end
