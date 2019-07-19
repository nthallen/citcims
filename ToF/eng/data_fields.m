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
        records
    end
    methods
        function obj = data_fields(fig_in)
            obj.fig = fig_in;
            % verify that fig is an object
            % record dimensions
            set(obj.fig,'units','pixels');
            d = get(obj.fig,'Position');
            obj.min_x = 0;
            obj.max_x = d(3);
            obj.min_y = 0;
            obj.max_y = d(4);
            obj.cur_x = obj.min_x;
            obj.cur_y = obj.max_y;
            obj.records = data_records();
            obj.figbgcolor = get(obj.fig,'Color');
        end
        function df = data_field(rec_name, var_name)
            obj.records.add_record(rec_name);
            lbl = [var_name ':'];
            tag = [var_name '_lbl'];
            h = uicontrol(obj.fig, 'Style', 'text', 'String', lbl, ...
                'Callback', 'lbl_selected', 'HorizontalAlignment', 'left', ...
                'BackgroundColor', obj.figbgcolor, ...
                'tag', tag);
            e = get(h, 'Extent' );
            dims = e(3:4) + [ 3 3 ];
        end
    end
end