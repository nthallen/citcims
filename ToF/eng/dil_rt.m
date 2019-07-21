function dil=dil_rt(P,T,DF,IF,FF,C2F)
dil=1610./((P+1.4)./36.4*1990./(273.15+T./3.5+17.143).*(24+273.15)-DF-IF-FF-C2F);
end