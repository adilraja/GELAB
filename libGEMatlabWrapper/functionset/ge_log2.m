function result_log=ge_log2(a)
%A robust version of log that can handle logicals. Written by Muhammad Adil
%Raja. 19 June, 2018
    if(islogical(a))
        a=double(a);
    end
    result_log=log2(a);
    i=find(a<=0);
    result_log(i)=NaN;%This is important. Otherwise a negative number could give rise to a negative number
end