function y=ge_quart(x1)
%MYPOWER    Protected square function.
%   MYPOWER(X1,X2) returns 0 if X1^X2 is NaN or Inf, 
%   or has imaginary part, otherwise returns X1^X2.
%
%   Input arguments:
%      X1 - the base of the power function (double)
%      X2 - the exponent of the power function (double)
%   Output arguments:
%      Y - the power X1^X2, or 0 (double)
%
%   See also MYDIVIDE, MYSQRT, MYLOG, MYLOG2, MYLOG10
%
%   Copyright (C) 2003-2004 Sara Silva (sara@dei.uc.pt)
%   Acknowledgement: Mehrashk Meidani, Shiraz University, (mehrashk@yahoo.com)
%   This file is part of the GPLAB Toolbox

if(islogical(x1))
        x1=double(x1);
end

y=x1.^4;
%y(find(isinf(y)))=0;
%y(find(imag(y)))=0;
%y(find(isnan(y)))=0;

y(find(isinf(y)))=NaN;%Adil
y(find(imag(y)))=NaN;
