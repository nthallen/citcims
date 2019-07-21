classdef data_sim < handle
    properties
        name
        Tname
        vars
        n
    end
    methods
        function obj = data_sim(name)
            obj.name = name;
            obj.Tname = ['T' name];
            obj.n = 0;
        end
        function add_var(obj, varargin)
            var = datum_sim(varargin{:});
            obj.vars.(var.name) = var;
        end
        function str = sample(obj)
            str.(obj.Tname) = obj.n;
            obj.n = obj.n + 1;
            flds = fieldnames(obj.vars);
            for i = 1:length(flds)
                fld = flds{i};
                str.(fld) = obj.vars.(fld).sample();
            end
        end
    end
end