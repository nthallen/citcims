function st=curr_state_rt()
%Determines the current state of the system for real time use:
%  0=dry cal
%  1=amb cal
%  2=dry zero
%  3=amb zero
%  4=amb sampling
%  5=amb sampling with cal
% 
bypass_cal=bitget(a.Herc_DS_A,1);
scrub_cal=bitget(a.Herc_DS_A,2);
eglyc_cal=bitget(a.Herc_DS_A,4);
amb_zero_bit=bitget(a.Herc_DS_A,8);
amb_zero_v=bitget(a.AII_DS0,1);
hcn_b=bitget(a.AII_DS0,5);
hcn_a=bitget(a.AII_DS0,3);

