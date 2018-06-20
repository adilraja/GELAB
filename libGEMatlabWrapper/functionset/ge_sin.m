function res=ge_sin(a)
%A robust version of sin that can handle logicals. Written by Muhammad Adil
%Raja. 19 June, 2018
    if(islogical(a))
        res=sin(double(a));
    else
        res=sin(a);
    end
end