function multiTree=ge_createMultipleTreeIndividual(params, runSensibleInit)

multiTree=struct;
for(i=1:params.numMultipleTrees)
    multiTree.ind(i)=ge_createIndividual(params.genome_length, params.grammar, runSensibleInit);
    multiTree.fitness=params.maxBadFitness;
    multiTree.testFitness=params.maxBadFitness;
    multiTree.result=[];
    multiTree.testResult=[];
end