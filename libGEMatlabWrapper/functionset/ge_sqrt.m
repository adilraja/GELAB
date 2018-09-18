function result_sqrt=ge_sqrt(a)
%A robust version of log that can handle logicals. Written by Muhammad Adil
%Raja. 19 June, 2018
    if(islogical(a))
        a=double(a);
    end
    i=find(a>=0);
    result_sqrt=sqrt(a);
    i=find(a<0);
    result_sqrt(i)=NaN;%This is important. Otherwise a negative number could give rise to a negative number
end