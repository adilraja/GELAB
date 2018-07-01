function result_log=ge_log10(a)
%A robust version of log that can handle logicals. Written by Muhammad Adil
%Raja. 19 June, 2018
    if(islogical(a))
        a=double(a);
    end
    result_log=log10(a);%I changed this initially it was taking the log(abs(x(i)));Adil
%fill the remaining negative positions with NaNs
    i=find(a<=0);
    result_log(i)=NaN;%This is important. Otherwise a negative number could give rise to a negative number
end