function rsq=pcorcoeff(x, y)
%function c=pcorcoeff(x, y) computes the Pearson's product moment
%correlation coefficient for two vectors. Source: https://en.wikipedia.org/wiki/Pearson_correlation_coefficient#For_a_sample
%Written by Muhammad Adil Raja, 23rd July, 2018

if(length(x)~=length(y))
    c=0;
    return;
end
n=length(x);

sx=sqrt(std(x)/(n-1));
sy=sqrt(std(y)/n-1);
numerator=sum(x.*y)-n*mean(x)*mean(y);
denominator=(n-1)*sx*sy;
r=numerator/denominator;
rsq=r^2;