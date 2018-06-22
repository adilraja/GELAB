function [pop, best, stats3]=ge_inaloop(numRuns, popsize, numgens)
%This is going to run ge for multiple runs. Muhammad Adil Raja. 20 July,
%2018
if(exist('numRuns', 'var')==0)
    numRuns=50;
end
if(exist('popsize', 'var')==0)
    popsize=100;
end
if(exist('numgens', 'var')==0)
    numgens=150;
end
stats3=ge_statistics;
data=ge_load_dataset('trainingDataX.txt', 'trainingDataY.txt', 'testingDataX.txt', 'testingDataY.txt');

for(i=1:numRuns)
    [pop, best, stats2]=ge_main(numgens, popsize, data);
    stats3.bestfithistory=[stats3.bestfithistory, stats2.bestfithistory];
    stats3.testfithistory=[stats3.testfithistory, stats2.testfithistory];
    stats3.meanfithistory=[stats3.meanfithistory, stats2.meanfithistory];
    stats3.timehistory=[stats3.timehistory, stats2.timehistory];
end