function handles = check_growing_vectors(handles, rec, data)
% handles = check_growing_vectors(handles, rec, vars, vals)
% rec is the name of the record
% data is struct of scalar elements.
%   data should include a time member 
% Each variable with get a growing column vector, each of the
% same allocated length ( handles.data.(rec).n_alloc) and each
% assumed to have the same number of valid values stored
% (handles.data.(rec).n_recd).
min_alloc = 10000;
flds = fieldnames(data);
if ~isfield(handles,'data') || ~isfield(handles.data, rec)
    % initialize variable
    handles.data.(rec).n_alloc = min_alloc;
    handles.data.(rec).n_recd = 0;
    for i = 1:length(flds)
        handles.data.(rec).vars.(flds{i}) = zeros(min_alloc,size(data.(flds{i}),2)) * NaN;
    end
end
handles.data.(rec).n_recd = handles.data.(rec).n_recd + 1;
if handles.data.(rec).n_recd > handles.data.(rec).n_alloc
    for i = 1:length(flds)
        handles.data.(rec).vars.(flds{i}) = [
            handles.data.(rec).vars.(flds{i});
            zeros(min_alloc,size(data.(flds{i}),2)) * NaN ];
    end
    handles.data.(rec).n_alloc = handles.data.(rec).n_alloc + min_alloc;
end
for i = 1:length(flds)
    if isnumeric(data.(flds{i}))
        handles.data.(rec).vars.(flds{i})(handles.data.(rec).n_recd,:) = ...
            data.(flds{i});
    end
end