%This is the main file to run ge.
function [pop, best, stats3, params]=ge_multipleTreesMain(params, runNumber)
    if(exist('params', 'var')==0)
        disp('The right parameters have not been specified to run GELAB in ge_main.\n')
    end
    
    %Load a statistics object. We are going to need it to keep track of
    %various things.
    stats3=ge_statistics();
    params.grammar.setMaxDepth(params.initMaxDepth);
    
%     [pop, params]=ge_initUniqueValidPopUsingSensibleInit(params);
        pop=ge_initMultipleTreePop(params, 1);
        pop=ge_evalMultipleTreePop(pop, params);
%     pop=ge_initPop(params, 1);
%     disp('i am out of here');

%     [pop, params]=ge_evalPop(pop, params);
    
    %params.grammar.setMaxDepth(params.maxDepth);
    
    for(i=1:params.numGens)
       tic;
       childPopulation=ge_createChildMultipleTreePopulation(pop, params);
       childPopulation=ge_genotype2phenotypeWholeMultipleTreePop(childPopulation, params);
       [childPop, params]=ge_evalMultipleTreePop(childPopulation, params);
       pop=ge_halfElitism(pop, childPop, params);
       %pause(3);
       fprintf('*****************************************\n');
       fprintf('Run-number: %d, Generation number: %d\n', runNumber, i);
       %fprintf('And the generation-number is: %d\n\n', i);
       %fprintf('************************************\n\n');
       stats3=ge_computeStatistics(stats3, pop, params);
       stats3.timehistory=[stats3.timehistory; toc];
       
    end
    best=pop(1);
end