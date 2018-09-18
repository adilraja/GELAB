function multiTree =ge_computeMultipleTreeTestFitness(multiTree, params)
%function individual =ge_computeEnsembleTestFitness(individual, params), As the name
%suggests, this function computes fitness over test data. Can be used for
%other purposes too. Written by Muhammad Adil Raja, 23 August, 2018.
[nrows, ncols]=size(params.data.test_y);
multiTree.testResult=zeros(nrows, ncols);
multiTree.testFitness=0;
testFitness=0;
for(i=1:params.mimoSize)
    multiTree.ind(i) =ge_computeTestFitness(multiTree.ind(i), params, params.data.test_y(:,i));
    if(length(multiTree.ind(i).testResult)==nrows)
        multiTree.testResult(:,i)=multiTree.testResult(:,i)+multiTree.ind(i).testResult;
    else
        multiTree.testResult(:,i)=ones(nrows,1)*params.maxBadFitness;
    end
    testFitness=testFitness+multiTree.ind(i).testFitness;
end
    multiTree.testFitness=testFitness/params.ensembleSize;

end