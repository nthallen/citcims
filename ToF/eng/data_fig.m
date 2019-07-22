classdef data_fig < handle
    properties
        fig
        axes
        recs
    end
    methods
        function df = data_fig(drecs)
            df.fig = figure;
            df.recs = drecs;
        end
        function new_graph(rec_name,var_name)
            % use the figures mode to decide where to put it
            % for starters, always create a new axis
        end
        function redraw(df)
        end
        function update(rec_name)
        end
    end
end
