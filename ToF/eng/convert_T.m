function [T3c,T4c]=convert_T(T3,T4,cal)
T4c=interp1(cal.T4_c(:,2),cal.T4_c(:,1),T4.*49.99./(5-T4)./10.2);
t32t4=T3.*0.88317+0.0013051;
T3c=interp1(cal.T4_c(:,2),cal.T4_c(:,1),t32t4.*49.99./(5-t32t4)./10.2);
end
