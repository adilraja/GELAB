function res=ge_exp(a)
%This is the robust version of exp that also handles logicals as inputs,
%written by Muhammad Adil Raja for libGEjava. 19 June, 2018
if(islogical(a))
    res=exp(double(a));
else
    res=exp(a);
end
end
