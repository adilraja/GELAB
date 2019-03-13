function params=ge_updateNumCoefs(params)
%This function updates the number of coefficients (constants) in a grammar
%depending on the dimensionality. Muhammad Adil Raja. 4th March, 2019

numVars=size(params.data.train_x,2);

if(numVars<=2)
    params.numCoefs=2;
elseif(numVars<=4)
    params.numCoefs=4;
elseif(numVars<=8)
    params.numCoefs=6;
elseif(numVars<=10)
    params.numCoefs=8;
elseif(numVars<=15)
    params.numCoefs=10;
else
    params.numCoefs=15;
end