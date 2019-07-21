function ma=mass_cal(ma_i,av_spec)
fma=av_spec;
mass_axis=ma_i;
mz=ma_i;
x=[1:length(mz)];
dma=find(diff(mass_axis)>0,1)+1;

sfs=8980; %start sample for mass fitting (small correction)
aa=peakfinder(fma(sfs:length(fma)),1);
aa=(aa-1)+sfs;
aa(find(diff(aa)<38))=[];
aa(find(aa>length(fma)-5))=[];
ib=find((fma(aa)-fma(aa+5))<3&mass_axis(aa)'<110);
aa(ib)=[];

mmm=round(mass_axis(aa));
ib=find(diff(mass_axis(aa)-round(mass_axis(aa)))>0.5);
ib2=find(diff(mass_axis(aa)-round(mass_axis(aa)))<-0.5);

if length(ib)>0&length(ib2)==0
%    display('MASS AXIS ISSUE CEILING.') 
   mmm(ib:length(mmm))=ceil(mass_axis(aa(ib:length(aa))));
elseif length(ib)>0&length(ib2)>0&ib(1)<ib2(1)
%    display('MASS AXIS ISSUE CEILING.') 
   mmm(ib:length(mmm))=ceil(mass_axis(aa(ib:length(aa))));
elseif length(ib)==0&length(ib2)>0
%    display('MASS AXIS ISSUE FLOOR.') 
   mmm(ib2:length(mmm))=floor(mass_axis(aa(ib2:length(aa))));
elseif length(ib)>0&length(ib2)>0&ib2(1)<ib(1)
%    display('MASS AXIS ISSUE FLOOR.') 
   mmm(ib2:length(mmm))=floor(mass_axis(aa(ib2:length(aa)))); 
end

ib=find(diff(mass_axis(aa)-mmm)>0.5);
ib2=find(diff(mass_axis(aa)-mmm)<-0.5);

% if length(ib)>0||length(ib2)>0
%     display(['HELP THIS IS F_D. FN: ',fn]) 
% end

[fnew,S,mu]=polyfit(x(aa),sqrt(mmm),3);
manew=polyval(fnew,x,S,mu);
manew=manew.^2;
display(fnew);
ma=manew;
