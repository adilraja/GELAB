function [all_pops, all_bests, all_stats]=ge_inaloop(numRuns, popsize, numgens)
%This is going to run ge for multiple runs. Muhammad Adil Raja. 20 July,
%2018
if(exist('numRuns', 'var')==0)
    numRuns=5;
end
if(exist('popsize', 'var')==0)
    popsize=100;
end
if(exist('numgens', 'var')==0)
    numgens=50;
end
all_stats=ge_statistics;
all_pops=[];
all_bests=[];
data=ge_load_dataset('trainingDataX.txt', 'trainingDataY.txt', 'testingDataX.txt', 'testingDataY.txt');

for(i=1:numRuns)
    [pop, best, stats2]=ge_main(numgens, popsize, data);
    all_stats.bestfithistory=[all_stats.bestfithistory, stats2.bestfithistory];
    all_stats.testfithistory=[all_stats.testfithistory, stats2.testfithistory];
    all_stats.meanfithistory=[all_stats.meanfithistory, stats2.meanfithistory];
    all_stats.timehistory=[all_stats.timehistory, stats2.timehistory];
    all_pops=[all_pops; pop];
    all_bests=[all_bests; best];
end