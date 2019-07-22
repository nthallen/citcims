classdef data_axis < handle
    properties
        lines
        recs
        dfig
        axis
    end
    methods
        function da = data_axis(recs, dfig)
            da.recs = recs;
            da.dfig = dfig;
        end
        function add_line(da, rec_name, var_name)
            lines{end+1} = struct('rec',rec_name,'var',var_name);
            da.redraw();
        end
        function redraw(da)
            for i=1:length(da.lines)
            end
        end
    end
end
