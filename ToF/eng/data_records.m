classdef data_records < handle
    properties
        records
        max_time
    end
    methods
        function obj = data_records()
            max_time = [];
        end
        
        function add_record(obj,rec_name)
            % data_records.add_record(rec_name)
            % May be called redundantly without harm.
            if ~isfield(obj.records, rec_name)
                obj.records.(rec_name) = data_record(rec_name);
            end
        end
        function process_record(obj,rec_name, str)
            dr = obj.records.(rec_name);
            dr.process_record(str);
            if isempty(obj.max_time) || dr.max_time > obj.max_time
                obj.max_time = dr.max_time;
            end
        end
    end
end