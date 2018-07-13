function [all_pops, all_bests, all_stats, params]=ge_inaloop(params)
%This is going to run ge for multiple runs. Muhammad Adil Raja. 20 July,
%2018

if(exist('params', 'var')==0)
    params=ge_fiddleParams;
end

all_stats=ge_statistics;
all_pops=[];
all_bests=[];


for(i=1:params.numRuns)
    [pop, best, stats2]=ge_main(params);
    all_stats.bestfithistory=[all_stats.bestfithistory, stats2.bestfithistory];
    all_stats.testfithistory=[all_stats.testfithistory, stats2.testfithistory];
    all_stats.meanfithistory=[all_stats.meanfithistory, stats2.meanfithistory];
    all_stats.timehistory=[all_stats.timehistory, stats2.timehistory];
    all_pops=[all_pops; pop];
    all_bests=[all_bests; best];
end