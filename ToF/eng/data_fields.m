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
        min_y
        max_y
        min_x
        max_x
        cur_x
        cur_y
        hspace
        vspace
        records
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
    end
    methods
        function obj = data_fields(fig_in)
            obj.fig = fig_in;
            % verify that fig is an object
            % record dimensions
            set(obj.fig,'units','pixels');
            d = get(obj.fig,'Position');
            obj.min_x = 20;
            obj.max_x = d(3);
            obj.min_y = 0;
            obj.max_y = d(4);
            obj.cur_x = obj.min_x;
            obj.cur_y = obj.max_y;
            obj.hspace = 10;
            obj.vspace = 5;
            obj.records = data_records();
            obj.figbgcolor = get(obj.fig,'Color');
            obj.start_col();
        end
        
        function start_col(obj)
            obj.cur_col.fields = {};
            obj.cur_col.n_rows = 0;
            obj.cur_col.max_lbl_width = 0;
            obj.cur_col.max_txt_width = 0;
        end
        
        function df = field(obj, rec_name, var_name, fmt)
            obj.records.add_record(rec_name);
            if ~isfield(obj.fields, rec_name) || ~isfield(obj.fields.(rec_name).vars,var_name)
                obj.fields.(rec_name).vars.(var_name) = {};
            end
            df_int = data_field(rec_name, var_name, fmt, obj);
            obj.fields.(rec_name).vars.(var_name){end+1} = df_int;
            obj.cur_col.fields{end+1} = df_int;
            obj.cur_col.n_rows = obj.cur_col.n_rows+1;
            if df_int.lbl_width > obj.cur_col.max_lbl_width
                obj.cur_col.max_lbl_width = df_int.lbl_width;
            end
            if df_int.txt_width > obj.cur_col.max_txt_width
                obj.cur_col.max_txt_width = df_int.txt_width;
            end
            obj.cur_y = obj.cur_y - df_int.fld_height;
            df_int.lbl.Position = ...
                [ obj.cur_x, obj.cur_y, df_int.lbl_width, df_int.fld_height];
            df_int.txt.Position = ...
                [ obj.cur_x + df_int.lbl_width + obj.hspace, obj.cur_y, ...
                  df_int.txt_width, df_int.fld_height];
            obj.cur_y = obj.cur_y - obj.vspace;
            if nargout > 0; df = df_int; end
        end
    end
end