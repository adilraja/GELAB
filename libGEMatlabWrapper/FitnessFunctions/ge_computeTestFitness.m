function individual =ge_computeTestFitness(individual, params, test_data_y)
%function individual =ge_computeTestFitness(individual, params), As the name
%suggests, this function computes fitness over test data. Can be used for
%other purposes too. Written by Muhammad Adil Raja, 22 July, 2018.

    [x, y]=size(params.data.test_x);
    var='X';
    for(i=1:y)
       val=strcat('params.data.test_x(:,', num2str(i),')');
       var2=strcat(var, num2str(i));
       eval([var2 '=' val ';']); 
    end
     if(individual.valid==1 && individual.treeDepth<=params.maxDepth)%if this is a valid individual
        testResult=eval(individual.string);
     else
         testResult=ones(x, 1)*params.maxBadFitness;
     end
    individual.testResult=testResult;
    individual.testFitness=ge_mse(individual.slope*testResult+individual.intercept, params.data.test_y);
    individual.testFitness=fixdec(individual.testFitness, params.precision);
    if(isnan(individual.testFitness) || isinf(individual.testFitness))
        individual.testFitness=params.maxBadFitness;
    end