function y=ge_scaledsigmoid(x, a)
%A scaled up/down version of the sigmoid function
y=ge_sigmoid(x);
y=y.*a;
return;