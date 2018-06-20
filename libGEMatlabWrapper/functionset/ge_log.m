function res=ge_log(a)
%A robust version of log that can handle logicals. Written by Muhammad Adil
%Raja. 19 June, 2018
    if(islogical(a))
        res=log(double(a));
    else
        res=log(a);
    end
end