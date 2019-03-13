function result_tan=ge_tanh(a)
%A robust version of log that can handle logicals. Written by Muhammad Adil
%Raja. 19 June, 2018
    if(islogical(a))
        a=double(a);
    end
    result_tan=tanh(a);
%     i=find(a<=0);
%     result_tan(i)=NaN;%This is important. Otherwise a negative number could give rise to a negative number
end