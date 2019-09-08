classdef data_field < handle
    % data_field represents two text objects,
    % a label and the value display, and the corresponding
    % data stream
    properties
        flds % The parent data_fields object
        rec_name
        var_name
        fmt
        lbl_name
        lbl
        txt
        lbl_width
        txt_width
        fld_height
    end
    methods
        function obj = data_field(rec_name, var_name, fmt, flds)
            obj.flds = flds;
            obj.fmt = fmt;
            obj.rec_name = rec_name;
            obj.var_name = var_name;
            obj.lbl_name = [rec_name '_lbl'];
            lbltxt = [var_name ':'];
            obj.lbl = uicontrol(flds.fig, ...
                'Style', 'text', 'String', lbltxt, ...
                'HorizontalAlignment', 'left', ...
                'BackgroundColor', flds.figbgcolor, ...
                'FontWeight', 'bold', ...
                'tag', obj.lbl_name, ...
                'uicontextmenu', flds.dfuicontextmenu, ...
                'userdata', obj);
            obj.lbl_width = obj.lbl.Extent(3);
            str = obj.txt_convert(0);
            obj.txt = uicontrol(flds.fig, ...
                'Style', 'text', 'String', str, ...
                'HorizontalAlignment', 'right', ...
                'BackgroundColor', [1 1 1], ...
                'FontName', flds.opts.txt_font, ...
                'FontSize', flds.opts.txt_fontsize, ...
                'tag', obj.var_name);
            obj.txt_width = obj.txt.Extent(3);
            obj.fld_height = max(obj.lbl.Position(4), obj.txt.Position(4));
        end
        
        function str = txt_convert(obj, val)
            if isnumeric(obj.fmt)
                str = num2str(val,obj.fmt);
            else
                str = sprintf(obj.fmt,val);
            end
        end
    end
end
