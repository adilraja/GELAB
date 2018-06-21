function stats3=ge_computeStatistics(stats3, pop)
%This function computes statistics. Muhammad Adil Raja, 20th June, 2018
    fitness=[];
    popsize=length(pop);
    for(i=1:popsize)
        fitness=[fitness; pop(i).fitness];
    end
    stats3.bestfithistory=[stats3.bestfithistory; pop(1).fitness];%The replacement operator is such that it main
    stats3.meanfithistory=[stats3.meanfithistory; mean(fitness)];
    stats3.testfithistory=[stats3.testfithistory; pop(1).testFitness];
    %maintains the whole population in ascending order of fitness. So the
    %first element has the fittest individual.
end