classdef data_fig < handle
    properties(GetAccess = public)
        fig % figure
        fignum % The data_fig index in the data_fields object
        axes % cell array of data_axis
        drs % data_records
        recs % identifies axes where specific vars are displayed
        axis_vec % just the axes
        mymenu % uimenu for this figure
    end
    methods
        function df = data_fig(dfs, fignum)
            df.fig = figure;
            df.fignum = fignum;
            df.drs = dfs.records;
            df.recs = [];
            df.axes = {};
            df.axis_vec = [];
            df.mymenu = ...
              uimenu(dfs.gimenu,'Text',sprintf('Figure %d', fignum));
            uimenu(df.mymenu,'Text','New axes', ...
              'Callback', { @data_fields.context_callback, ...
              "new_axes", fignum });
        end

        function new_graph(df, rec_name, var_name, mode, axisnum)
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
                the_axis = data_axis(df, var_name);
                df.axes{end+1} = the_axis;
                df.axis_vec(end+1) = df.axes{end}.axis;
                axnum = length(df.axes);
                uimenu(df.mymenu,'Text',sprintf('Axis %d',axnum), ...
                  'Callback', { @data_fields.context_callback, ...
                  "cur_axes", df.fignum, axnum });
            else
                the_axis = df.axes{axisnum};
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
