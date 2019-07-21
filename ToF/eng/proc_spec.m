function pk_d=proc_spec(spec,map,bl1,bl2,N)
        pk_d=zeros(1,400)*nan;
         for i=10:400
            pk_d(i)=(sum(spec(map{i}))-(mean(spec(bl1{i}))+mean(spec(bl2{i})))./2.*length(map{i})).*sqrt(85./i).*10./N;
         end
       