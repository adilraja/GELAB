function individual = ge_hybridTest(individual, params, test_y)
%function individual = ge_hybridTest(individual, params, train_y). This
%function performs hybrid optimization. To this end, it tunes values of
%coefficients of the models produced by GE. Written by Muhammad Adil Raja.
%9th October, 2018

X=params.data.test_x;
if(nargin<3)
    T=params.data.test_y;
else
    T=test_y;
end
% w=rand(1,params.numCoefs);
str1=char(individual.string);
w=individual.weights;
individual.testResult=eval(str1);
individual.testFitness=ge_mse(individual.testResult, T);

if(length(individual.testResult)~=length(T))
    individual.testFitness=params.maxBadFitness;%really bad fitness
    individual.testResult=ones(length(T), 1)*params.maxBadFitness;
    %individual.valid=0;
    return;
end