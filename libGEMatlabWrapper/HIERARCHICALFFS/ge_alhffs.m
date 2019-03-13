function individual = ge_alhf(individual, params, train_y)
%function individual = ge_alhffs(individual, params, train_y). This functions 
%performs alps like fitness evaluation. Fitness function is MSE for a
%certain initial age of an individual. After that, for a few more
%units of age, the fitness function is based on hybrid optimization. At the
%end, possibly, linear scaling can be used.
% Written by Muhammad Adil Raja.
%13th October, 2018

age=inidividual.age;

if(age<3)
    individual = ge_mseonly(individual, params, train_y);
elseif(age<10)
    individual = ge_hybrid(individual, params, train_y);
else
    individual = ge_evaluate(individual, params, train_y);
end