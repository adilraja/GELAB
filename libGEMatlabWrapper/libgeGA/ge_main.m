%This is the main file to run ge.
function [pop, best, stats3]=ge_main(params)
    if(exist('params', 'var')==0)
        disp('The right parameters have not been specified to run GELAB in ge_main.\n')
    end
    
    %Load a statistics object. We are going to need it to keep track of
    %various things.
    stats3=ge_statistics();
    
    genome_length=3200;
    
    pop=ge_initPop(params.popSize, genome_length, params.grammar, 1);
    pop=ge_evalPop(pop, params);
    
    for(i=1:params.numGens)
       tic;
       childPopulation=ge_createChildPopulation(pop, genome_length, params.grammar);
       [childPopulation, grammar]=ge_genotype2phenotypeWholePop(childPopulation, params.grammar);
       childPop=ge_evalPop(childPopulation, params);
       pop=ge_replacement(pop, childPop, params);
       stats3=ge_computeStatistics(stats3, pop);
       stats3.timehistory=[stats3.timehistory; toc];
    end
    best=pop(1);
end