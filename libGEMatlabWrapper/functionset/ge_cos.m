function res=ge_cos(a)
%A robust version of cos that can handle logicals. Written by Muhammad Adil
%Raja. 19 June, 2018
    if(islogical(a))
        res=cos(double(a));
    else
        res=cos(a);
    end
end