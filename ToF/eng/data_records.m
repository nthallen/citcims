classdef data_records < handle
    properties
        records
    end
    methods
        function obj = data_records()
        end
        
        function add_record(obj,rec_name)
            % data_records.add_record(rec_name)
            % May be called redundantly without harm.
            if ~isfield(obj.records, rec_name)
                obj.records.(rec_name) = data_record(rec_name);
            end
        end
        function process_record(obj,rec_name, str)
            obj.records.(rec_name).process_record(str);
        end
    end
end