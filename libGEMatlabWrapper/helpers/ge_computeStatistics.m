function stats3=ge_computeStatistics(stats3, pop, params)
%function stats3=ge_computeStatistics(stats3, pop)
%This function computes statistics. Muhammad Adil Raja, 20th June, 2018
%Please always apply this function after replacement.

    fitness=[];
    numValid=0;
    popsize=length(pop);
    for(i=1:popsize)
        
        if(pop(i).valid==1)
            numValid=numValid+1;
            fitness=[fitness; pop(i).fitness];
        end
    end
    
    I=find(fitness<params.maxBadFitness);
    fitness=fitness(I);%Exclude outliers
    
    meanf=mean(fitness);
    diversity=std(fitness);
    dissimilarity_index=length(unique(fitness))/popsize;
    
    stats3.bestfithistory=[stats3.bestfithistory; pop(1).fitness];%The replacement operator is such that it main
    stats3.meanfithistory=[stats3.meanfithistory; meanf];
    
    stats3.testfithistory=[stats3.testfithistory; pop(1).testFitness];
    stats3.diversityhistory=[stats3.diversityhistory; diversity];
    stats3.numvalidhistory=[stats3.numvalidhistory; numValid];
    stats3.dissimilarityhistory=[stats3.dissimilarityhistory; dissimilarity_index];
    
    fprintf(['*****************************************\n', ...
    'Best fitness: %d\n', ...
    'Mean fitness: %d\n', ...
    'Test fitness: %d\n', ...
    'Diversity score: %d\n' ...
    'Dissimilarity index: %f\n' ...
    'Number of valid individuals is: %d\n', ...
    '*****************************************\n\n'], ...
    pop(1).fitness, meanf, pop(1).testFitness, diversity, dissimilarity_index, numValid);
    %maintains the whole population in ascending order of fitness. So the
    %first element has the fittest individual.
end