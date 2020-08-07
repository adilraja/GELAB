function y=ge_subtract(x1,x2)


% first make both matrices the same size:
%m=max([length(x1) length(x2)]);
%if length(x1)<m
%   x1=repmat(x1,m,1);
%end
%if length(x2)<m
%   x2=repmat(x2,m,1);
%end

% fill the cells where x2=0 (make them x1):
%y=x1.*ones(size(x1));

% fill the remaining cells with the result of the division:
%i=find(x2~=0);
%y(i)=rdivide(x1(i),x2(i));
% x1=double(x1);
% x2=double(x2);
y=x1-x2;%Adil