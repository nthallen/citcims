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
% Test of datum_sim()
N = 200;
ds = datum_sim('T1_Hz',10,N,-5,30,10);
S = zeros(N,1);
for i=1:N; S(i) = ds.sample(); end
plot(S); shg;
%%
close all
clear all
clc
%%
rec = 'ToFeng_1';
N = 200;
dsim = data_sim(rec);
dsim.add_var('T1_Hz',10,N,-5,30,10);
dsim.add_var('P1_Hz',10,N,-5,30,10);
dsim.add_var('Q1_Hz',10,N,-5,30,10);
dsim.add_var('R1_Hz',10,N,-5,30,10);
dsim.add_var('S1_Hz',10,N,-5,30,10);
dsim.add_var('J1_Hz',10,N,-5,30,10);
dsim.add_var('T2_Hz',10,N,-5,30,10);
dsim.add_var('P2_Hz',10,N,-5,30,10);
dsim.add_var('Q2_Hz',10,N,-5,30,10);
dsim.add_var('R2_Hz',10,N,-5,30,10);
dsim.add_var('S2_Hz',10,N,-5,30,10);
dsim.add_var('J2_Hz',10,N,-5,30,10);
%%
str = dsim.sample();
dfs.process_record(rec,str);