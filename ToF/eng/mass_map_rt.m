function [map,bl1,bl2]=mass_map_rt(mm,ma)

r=0.25;
map=[];
bl1=[];
bl2=[];
for i=10:mm
    map{i}=find(ma<i+r&ma>i-r);
    bl1{i}=find(ma>=(i-1)+0.55&ma<=i-0.25);
    bl2{i}=find(ma>=i+0.55&ma<=(i+1)-0.25);
end

%special cases
    
    i=84;
    map{84}=find(ma<i+0.2&ma>i-0.12);
    bl1{84}=find(ma>=(i)-0.22&ma<=i-0.12);
    bl2{84}=find(ma>=i+0.2&ma<=(i)+0.3);

    
    i=83;
    map{83}=find(ma<i+0.05&ma>i-0.2);
    bl1{83}=find(ma>=(i)-0.5&ma<=i-0.22);
    bl2{83}=find(ma>=i+0.08&ma<=(i)+0.30);
    
    i=102;
    map{102}=find(ma<i+0.2&ma>i-0.2);
    bl1{102}=find(ma>=(i)-0.3&ma<=i-0.2);
    bl2{102}=find(ma>=i+0.2&ma<=(i)+0.3);

    i=118;
    map{118}=find(ma<i+0.2&ma>i-0.2);
    bl1{118}=find(ma>=(i)-0.3&ma<=i-0.2);
    bl2{118}=find(ma>=i+0.2&ma<=(i)+0.3);

    i=120;
    map{120}=find(ma<i+0.25&ma>i-0.25);
    bl1{120}=find(ma>=(i)-0.35&ma<=i-0.25);
    bl2{120}=find(ma>=i+0.25&ma<=(i)+0.35);
    
    i=126;
    map{126}=find(ma<i+0.2&ma>i-0.2);
    bl1{126}=find(ma>=(i)-0.3&ma<=i-0.2);
    bl2{126}=find(ma>=i+0.2&ma<=(i)+0.3);

    i=145;
    map{145}=find(ma<i+0.3&ma>i-0.25);
    bl1{145}=find(ma>=(i)-0.55&ma<=i-0.3);
    bl2{145}=find(ma>=i+0.35&ma<=(i)+0.5);

    %i=192;
    %map{192}=find(ma<i+0.2&ma>i-0.2);
    %bl1{192}=find(ma>=(i)-0.3&ma<=i-0.2);
    %bl2{192}=find(ma>=i+0.2&ma<=(i)+0.3);

    i=202;
    map{202}=find(ma<i+0.2&ma>i-0.2);
    bl1{202}=find(ma>=(i)-0.3&ma<=i-0.2);
    bl2{202}=find(ma>=i+0.2&ma<=(i)+0.3);
    
    %i=220;
    %map{220}=find(ma<i+0.2&ma>i-0.2);
    %bl1{220}=find(ma>=(i)-0.3&ma<=i-0.2);
    %bl2{220}=find(ma>=i+0.2&ma<=(i)+0.3);
    
    %i=232;
    %map{232}=find(ma<i+0.25&ma>i-0.05);
    %bl1{232}=find(ma>=(i)-0.3&ma<=i-0.2);
    %bl2{232}=find(ma>=(i)-0.3&ma<=i-0.2);
    
    i=272;
    map{272}=find(ma<i+0.2&ma>i-0.2);
    bl1{272}=find(ma>=(i)-0.3&ma<=i-0.2);
    bl2{272}=find(ma>=i+0.2&ma<=(i)+0.3);
    
    i=298;
    map{298}=find(ma<i+0.2&ma>i-0.2);
    bl1{298}=find(ma>=(i)-0.3&ma<=i-0.2);
    bl2{298}=find(ma>=i+0.2&ma<=(i)+0.3);
