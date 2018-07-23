function individual =ge_computeTestFitness(individual, params)
%function individual =ge_computeTestFitness(individual, params), As the name
%suggests, this function computes fitness over test data. Can be used for
%other purposes too. Written by Muhammad Adil Raja, 22 July, 2018.

    [x, y]=size(params.data.test_x);
    for(i=1:y)
       val=strcat('params.data.test_x(:,', num2str(i),')');
       var2=strcat(var, num2str(i));
       eval([var2 '=' val ';']); 
    end
    testResult=eval(individual.string);
    individual.testResult=testResult;
    individual.testFitness=ge_mse(individual.slope*testResult+individual.intercept, params.data.test_y);
    individual.testFitness=fixdec(individual.testFitness, params.precision);
    if(isnan(individual.testFitness) || isinf(individual.testFitness))
        individual.testFitness=params.maxBadFitness;
    end