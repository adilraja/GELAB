function individual = ge_alhf(individual, params, train_y)
%function individual = ge_alhf(individual, params, train_y). This functions 
%performs alps like fitness evaluation. Fitness function is MSE for a
%certain initial age of an individual. After that, for a few more
%units of age, the fitness function is based on hybrid optimization. At the
%end, possibly, linear scaling can be used.
% Written by Muhammad Adil Raja.
%13th October, 2018

age=individual.age;

 if(age<=params.criticalAge1)
     individual = ge_mseonly(individual, params, train_y);
 elseif(age<=params.criticalAge2 && age>params.criticalAge1)
    r=rand(1,1);
    if(r<0.25)
        individual = ge_hybrid(individual, params, train_y);
    end
elseif(age<=10 && age>params.criticalAge2)
    r=rand(1,1);
    if(r<0.25)
        individual = ge_numerical(individual, params, train_y, 'sa');
    end
else
    individual = ge_evaluate(individual, params, train_y);
    individual.isEvaluated=1;
end