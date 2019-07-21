%%
close all
clear all
clc
%
fig = figure;
dfs = data_fields(fig,'h_leading', 5, 'col_leading', 50);
%
%dfs.h_padding = 0;
dfs.start_col();
dfs.field('ToFeng_1','T1_Hz','%5.1f');
dfs.field('ToFeng_1','P1_Hz','%6.1f');
dfs.field('ToFeng_1','Q1_Hz','%6.1f');
dfs.field('ToFeng_1','R1_Hz','%8.1f');
dfs.field('ToFeng_1','S1_Hz','%6.1f');
dfs.field('ToFeng_1','J1_Hz','%6.1f');
dfs.end_col();
%
dfs.start_col();
dfs.field('ToFeng_1','T2_Hz','%5.1f');
dfs.field('ToFeng_1','P2_Hz','%6.1f');
dfs.field('ToFeng_1','Q2_Hz','%6.1f');
dfs.field('ToFeng_1','R2_Hz','%8.1f');
dfs.field('ToFeng_1','S2_Hz','%6.1f');
dfs.field('ToFeng_1','J2_Hz','%6.1f');
dfs.end_col();
%%
df = dfs.fields.ToFeng_1.vars.T1_Hz{1};
%%

