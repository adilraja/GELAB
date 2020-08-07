function y=ge_sigmoid(x)
%Computes the simple sigmoid function


y=1./(1+ge_exp(-1*x));
return