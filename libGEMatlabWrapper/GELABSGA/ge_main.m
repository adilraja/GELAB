%This is the main file to run ge.
function [pop, best, stats3, params]=ge_main(params, runNumber)
    if(exist('params', 'var')==0)
        disp('The right parameters have not been specified to run GELAB in ge_main.\n')
    end
    
    %Load a statistics object. We are going to need it to keep track of
    %various things.
    stats3=ge_statistics();
    params.grammar.setMaxDepth(params.initMaxDepth);
    
    [pop, params]=ge_initUniqueValidPopUsingSensibleInit(params);
%     pop=ge_initPop(params, 1);
%     disp('i am out of here');

%     [pop, params]=ge_evalPop(pop, params);
    %pop=ge_evalPop(pop, params);
    %params.grammar.setMaxDepth(params.maxDepth);
    
    for(i=1:params.numGens)
       tic;
       if(params.hybrid)
           if(i<=10)
               params=ge_updateparams(params, 'selection', 'ge_lpptourinvert');
           else
               params=ge_updateparams(params, 'selection', 'ge_lpptour');
           end
       end
       childPopulation=ge_createChildPopulation(pop, params);
       childPopulation=ge_genotype2phenotypeWholePop(childPopulation, params);
       [childPop, params]=ge_evalPop(childPopulation, params);
        if(params.hffs==1)
           [pop, params]=ge_evalPop(pop, params);%eval the parent pop again
       end
       pop=ge_halfElitism(pop, childPop, params);
      
       %pause(3);
       fprintf('*****************************************\n');
       fprintf('Run-number: %d, Generation number: %d\n', runNumber, i);
       %fprintf('And the generation-number is: %d\n\n', i);
       %fprintf('************************************\n\n');
       [stats3, params]=ge_computeStatistics(stats3, pop, params);
       stats3.timehistory=[stats3.timehistory; toc];
       
    end
    best=pop(1);
end