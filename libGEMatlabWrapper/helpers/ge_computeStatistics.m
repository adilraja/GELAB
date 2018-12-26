function [stats3, params]=ge_computeStatistics(stats3, pop, params)
%function stats3=ge_computeStatistics(stats3, pop)
%This function computes statistics. Muhammad Adil Raja, 20th June, 2018
%Please always apply this function after replacement.

    fitness=[];
    result=[];
    rtest=-1;
    if(params.data.test)
        testresult=[];
    end
    numValid=0;
    popsize=length(pop);
    for(i=1:popsize)
        
        if(pop(i).valid>0)
            numValid=numValid+1;
            fitness=[fitness; pop(i).fitness];
        end
    end
    
    result=pop(1).result;
    if(params.data.test)
        pop(1) =feval(params.testFitnessFunction, pop(1), params);
        testresult=pop(1).testResult;
    end
    
    r=corrcoef(result, params.data.train_y);
    rtrain=r(1,2)^2;
    if(params.data.test)
        r=corrcoef(testresult, params.data.test_y);
        rtest=r(1,2)^2;
    end
    I=find(fitness<params.maxBadFitness);
    fitness=fitness(I);%Exclude outliers
    
    meanf=mean(fitness);
    diversity=std(fitness);
    dissimilarity_index=length(unique(fitness))/popsize;
    
    stats3.bestfithistory=[stats3.bestfithistory; pop(1).fitness];%The replacement operator is such that it main
    stats3.bestrsquaretrainhistory=[stats3.bestrsquaretrainhistory; rtrain];
    if(params.data.test)
        stats3.bestrsquaretesthistory=[stats3.bestrsquaretesthistory; rtest];
    end
    
    stats3.meanfithistory=[stats3.meanfithistory; meanf];
    
    stats3.testfithistory=[stats3.testfithistory; pop(1).testFitness];
    stats3.diversityhistory=[stats3.diversityhistory; diversity];
    stats3.numvalidhistory=[stats3.numvalidhistory; numValid];
    stats3.dissimilarityhistory=[stats3.dissimilarityhistory; dissimilarity_index];
    
    stats3.spxoverhistory=[stats3.spxoverhistory; params.spxoverp];
    stats3.vpxoverhistory=[stats3.vpxoverhistory; params.vpxoverp];
    
    stats3.weavehistory=[stats3.weavehistory; params.weavep];
    stats3.tweavehistory=[stats3.tweavehistory; params.tweavep];
    
    stats3.pmutationhistory=[stats3.pmutationhistory; params.pmutationp];
    stats3.fpmutationhistory=[stats3.fpmutationhistory; params.fpmutationp];
    stats3.fbmutationhistory=[stats3.fbmutationhistory; params.fbmutationp];

    
    if(params.genotypeCaching==0)
        params.genotypeCache.length=0;
    end
    
    fprintf(['*****************************************\n', ...
    'Best fitness: %d\n', ...
    'Mean fitness: %d\n', ...
    'Test fitness: %d\n', ...
    'R-square train: %f, Test: %f\n', ...
    'Diversity score: %d\n' ...
    'Dissimilarity index: %f\n' ...
    'Number of valid individuals is: %d\n', ...
    'The cache size is: %d\n', ...
    '*****************************************\n'], ...
    pop(1).fitness, meanf, pop(1).testFitness, rtrain, rtest, diversity, dissimilarity_index, numValid, params.genotypeCache.length);
    %maintains the whole population in ascending order of fitness. So the
    %first element has the fittest individual.
    if(params.adaptiveProbs)
        params=ge_updateoperatorprobabilities(pop, params);
        params=ge_updatemutationoperatorprobabilities(pop, params);
    end
end