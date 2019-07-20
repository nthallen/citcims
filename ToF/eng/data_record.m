classdef data_record < handle
    properties
        record_name
        time_name
        data
        n_alloc
        n_recd
        min_alloc
        n_flds
    end
    methods
        function obj = data_record(rec_name)
            obj.record_name = rec_name;
            obj.time_name = ['T' rec_name];
            obj.n_alloc = 0;
            obj.n_recd = 0;
            obj.min_alloc = 10000;
            obj.n_flds = 0;
        end
        
        function process_record(obj, str)
            flds = fieldnames(str);
            if obj.n_flds == 0
                obj.n_alloc = obj.min_alloc;
                obj.n_flds = length(flds);
                for i = 1:obj.n_flds
                    obj.data.(flds{i}) = zeros(obj.min_alloc,1) * NaN;
                end
                if ~isfield(obj.data, obj.time_name)
                    error('Structure for record %s missing time var %s', ...
                        obj.record_name, obj.time_name);
                end
            end
            if obj.n_flds ~= length(flds)
                error('Change in size of record %s', obj.record_name);
            end
            for i = 1:obj.n_flds
                if ~isfield(obj.data, flds{i})
                    error('Structure for record %s changed: %s is new', ...
                        obj.record_name, flds{i});
                end
            end
            obj.n_recd = obj.n_recd+1;
            if obj.n_recd > obj.n_alloc
                for i = 1:length(flds)
                    obj.data.(flds{i}) = [
                        obj.data.(flds{i});
                        zeros(obj.min_alloc,1) * NaN ];
                end
                obj.n_alloc = obj.n_alloc + obj.min_alloc;
            end
            for i = 1:obj.n_flds
                obj.data.(flds{i})(obj.n_recd) = str.(flds{i});
            end
        end
    end
end