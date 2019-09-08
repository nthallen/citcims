classdef data_axis < handle
    properties
        lines
        recs
        dfig
        axis % axes
        label
    end
    methods
        function da = data_axis(dfig, label)
            da.dfig = dfig;
            da.recs = dfig.recs;
            da.axis = axes(dfig.fig,'visible','off');
            da.label = strrep(label,'_','\_');
        end
        function n = add_line(da, rec_name, var_name)
            % returns the line index
            da.lines{end+1} = struct('rec',rec_name,'var',var_name);
            da.redraw();
            n = length(da.lines);
        end
        function redraw(da)
            cla(da.axis);
            for i=1:length(da.lines)
                rec_name = da.lines{i}.rec;
                var_name = da.lines{i}.var;
                dr = da.dfig.drs.records.(rec_name);
                [T,V] = dr.time_vector(200);
                D = dr.data_vector(var_name,V);
                if isempty(T)
                    plot(da.axis, nan, nan);
                else
                    plot(da.axis, T-da.dfig.drs.max_time, D);
                end
                hold(da.axis,'on');
            end
            hold(da.axis,'off');
            set(da.axis,'xlim',[-200 0]);
            ylabel(da.axis,da.label);
        end
    end
end
