function [all_pops, all_bests, all_stats, params]=ge_inaloopParallel(params)
%This is going to run ge for multiple runs. Muhammad Adil Raja. 20 July,
%2018

if(exist('params', 'var')==0)
    params=ge_fiddleParams;
end

all_stats=ge_statistics;
all_pops=[];
all_bests=[];
bestfithistory=zeros(params.numGens, params.numRuns);
testfithistory=zeros(params.numGens, params.numRuns);
meanfithistory=zeros(params.numGens, params.numRuns);
timehistory=zeros(params.numGens, params.numRuns);
numvalidhistory=zeros(params.numGens, params.numRuns);
diversityhistory=zeros(params.numGens, params.numRuns);

parfor(i=1:params.numRuns, 3)
    [pop(i), best(i), stats2(i)]=feval(params.ga_fcn, params);
    bestfithistory(:,i)=stats2(i).bestfithistory;
    testfithistory(:, i)=stats2(i).testfithistory;
    meanfithistory(:, i)=stats2(i).meanfithistory;
    timehistory(:, i)=stats2(i).timehistory;
    numvalidhistory=stats2(i).numvalidhistory;
    diversityhistory=stats2(i).numvalidhistory;
     all_pops=[all_pops; pop(i)];
     all_bests=[all_bests; best(i)];
end
all_stats.bestfithistory=bestfithistory;
all_stats.testfithistory=testfithistory;
all_stats.meanfithistory=meanfithistory;
all_stats.timehistory=timefithistory;
all_stats.numvalidhistory=numvalidhistory;
all_stats.diversityhistory=diversityhistory;