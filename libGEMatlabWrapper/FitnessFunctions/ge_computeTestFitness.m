function individual =ge_computeTestFitness(individual, params, test_data_y)
%function individual =ge_computeTestFitness(individual, params), As the name
%suggests, this function computes fitness over test data. Can be used for
%other purposes too. Written by Muhammad Adil Raja, 22 July, 2018.
    if(nargin<3)
        test_data_y=params.data.test_y(:,1);
    end
    [x, y]=size(params.data.test_x);
    X=params.data.test_x;
    w=individual.constants;
     if(individual.valid==1 && individual.treeDepth<=params.maxDepth)%if this is a valid individual
        testResult=eval(individual.string);
        if(length(testResult)~=length(test_data_y))
            testResult=ones(x, 1)*params.maxBadFitness;
        end
     else
         testResult=ones(x, 1)*params.maxBadFitness;
     end
    individual.testResult=testResult;
%     disp(size(testResult));
    individual.testFitness=ge_mse(individual.slope*testResult+individual.intercept, test_data_y);
    individual.testFitness=fixdec(individual.testFitness, params.precision);
    if(isnan(individual.testFitness) || isinf(individual.testFitness))
        individual.testFitness=params.maxBadFitness;
    end