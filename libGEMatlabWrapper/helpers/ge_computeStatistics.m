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
    
    if(length(result)==length(params.data.train_y))
        r=corrcoef(result, params.data.train_y);
    else
        r=zeros(2,2);
    end
    rtrain=r(1,2)^2;
    if(params.data.test)
        if(length(testresult)==length(params.data.test_y))
            r=corrcoef(testresult, params.data.test_y);
        else
            r=zeros(0,0);
        end
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
        stats3.testfithistory=[stats3.testfithistory; pop(1).testFitness];
    end
    
    stats3.meanfithistory=[stats3.meanfithistory; meanf];
    
    
    stats3.diversityhistory=[stats3.diversityhistory; diversity];
    stats3.numvalidhistory=[stats3.numvalidhistory; numValid];
    stats3.dissimilarityhistory=[stats3.dissimilarityhistory; dissimilarity_index];
    
    stats3.spxoverhistory=[stats3.spxoverhistory; params.spxoverp];
    stats3.vpxoverhistory=[stats3.vpxoverhistory; params.vpxoverp];
    stats3.subtreexoverhistory=[stats3.subtreexoverhistory; params.subtreexoverp];
    
    stats3.weavehistory=[stats3.weavehistory; params.weavep];
    stats3.tweavehistory=[stats3.tweavehistory; params.tweavep];
    stats3.noxoverhistory=[stats3.noxoverhistory; params.noxoverp];
    
    stats3.pmutationhistory=[stats3.pmutationhistory; params.pmutationp];
    stats3.fpmutationhistory=[stats3.fpmutationhistory; params.fpmutationp];
    stats3.fbmutationhistory=[stats3.fbmutationhistory; params.fbmutationp];
    stats3.stmutationhistory=[stats3.stmutationhistory; params.stmutationp];
    stats3.nomutationhistory=[stats3.nomutationhistory; params.nomutationp];

    
    if(params.genotypeCaching==0)
        cache_size=0;
    else
        cache_size=params.genotypeCache.length;
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
    'The best ind is: %s\n', ...
    'Active terminals are: %s\n', ...
    '*****************************************\n'], ...
    pop(1).fitness, meanf, pop(1).testFitness, rtrain, rtest, diversity, dissimilarity_index, numValid, cache_size, pop(1).string, ge_getTerminals(params));
    %maintains the whole population in ascending order of fitness. So the
    %first element has the fittest individual.
    if(params.adaptiveProbs)
        params=ge_updateoperatorprobabilities(pop, params);
        params=ge_updatemutationoperatorprobabilities(pop, params);
    end
    params=ge_terminals_scores(pop, params);%Compute scores for terminal symbols
end