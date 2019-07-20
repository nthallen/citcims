%%
close all
clear all
%%
fig = figure;
dfs = data_fields(fig);
dfs.field('ToFeng_1','T1_Hz','%5.1f');
dfs.field('ToFeng_1','P1_Hz','%6.1f');
%%
df = dfs.fields.ToFeng_1.vars.T1_Hz{1};
%%

