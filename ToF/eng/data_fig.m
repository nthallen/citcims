classdef data_fig < handle
    properties
        fig % figure
        axes % cell array of data_axis
        drs % data_records
        recs % identifies axes where specific vars are displayed
        axis_vec % just the axes
    end
    methods
        function df = data_fig(drs)
            df.fig = figure;
            df.drs = drs;
            df.recs = [];
            df.axes = {};
            df.axis_vec = [];
        end

        function new_graph(df, rec_name, var_name, mode, varargin)
            % use the figure's mode to decide where to put it
            % for starters, always create a new axis
            % @param mode: "new_fig", "new_axes", "cur_axes"
            if ~isfield(df.recs,rec_name)
                df.recs.(rec_name).vars = [];
            end
            if ~isfield(df.recs.(rec_name).vars, var_name)
                df.recs.(rec_name).vars.(var_name) = {};
            end
            if mode == "new_fig" || mode == "new_axes"
                the_axis = data_axis(df, varargin{1});
                df.axes{end+1} = the_axis;
                df.axis_vec(end+1) = df.axes{end}.axis;
            else
                the_axis = df.axes{end};
            end
            n = the_axis.add_line(rec_name, var_name);
            df.recs.(rec_name).vars.(var_name) = [
                df.recs.(rec_name).vars.(var_name)
                {the_axis n} ];
            df.redraw();
        end

        function redraw(df)
            % reallocate axes positions
            n_axes = length(df.axes);
            for i=1:n_axes
                pos = nsubpos(n_axes,1,i,1);
                ax = df.axes{i}.axis;
                ax.Position = pos;
                ax.Visible = 'on';
                if mod(i,2)
                    ax.YAxisLocation = 'Left';
                else
                    ax.YAxisLocation = 'Right';
                end
                if i < n_axes
                    ax.XTickLabel = [];
                end
            end
            linkaxes(df.axis_vec,'x');
        end
        
        function update(df, rec_name)
            % update data for each line of each graph
            if isfield(df.recs,rec_name) % if we are plotting any data
                dr = df.drs.records.(rec_name);
                [T,V] = dr.time_vector(200);
                % go through df.recs.(rec_name).vars
                vars = df.recs.(rec_name).vars;
                var_names = fieldnames(vars);
                for i=1:length(var_names)
                    var = var_names{i};
                    axn = vars.(var);
                    ax = axn{1};
                    n = axn{2};
                    D = dr.data_vector(var,V);
                    lns = findobj(ax.axis,'type','line','parent',ax.axis);
                    set(lns(n),'XData',T-df.drs.max_time,'YData',D);
                end
            end
        end
    end
end
