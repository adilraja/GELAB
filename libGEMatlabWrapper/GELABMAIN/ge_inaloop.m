function [all_pops, all_bests, all_stats, params]=ge_inaloop(params)
%This is going to run ge for multiple runs. Muhammad Adil Raja. 20 July,
%2018



if(exist('params', 'var')==0)
    params=ge_fiddleParams;
end

libGEpath=strcat(fileparts(which('loadGrammar.m')), '/libGEjar/libGEjava.jar');
if(params.parallel)
    if(isempty(gcp('nocreate')))
        pool=parpool('IdleTimeout', 1200);
    end
    pctRunOnAll javaaddpath(strcat(fileparts(which('loadGrammar.m')), '/libGEjar/libGEjava.jar'));
else
    javaaddpath(libGEpath);
end

params.grammar=loadGrammar(params.bnfFile);
if(params.evalinws)
    ge_expandVarsinWorkSpace(params);
end

all_stats=ge_statistics;
all_pops=[];
all_bests=[];
bestfithistory=zeros(params.numGens, params.numRuns);
testfithistory=zeros(params.numGens, params.numRuns);
meanfithistory=zeros(params.numGens, params.numRuns);
timehistory=zeros(params.numGens, params.numRuns);
numvalidhistory=zeros(params.numGens, params.numRuns);
dissimilarityhistory=zeros(params.numGens, params.numRuns);
diversityhistory=zeros(params.numGens, params.numRuns);

if(params.parallel~=1)
for(i=1:params.numRuns)
    [pop, best, stats2]=feval(params.ga_fcn, params, i);
    bestfithistory(:,i)=stats2.bestfithistory;
    testfithistory(:, i)=stats2.testfithistory;
    meanfithistory(:, i)=stats2.meanfithistory;
    timehistory(:, i)=stats2.timehistory;
    numvalidhistory(:, i)=stats2.numvalidhistory;
    dissimilarityhistory(:, i)=stats2.dissimilarityhistory;
    diversityhistory(:, i)=stats2.diversityhistory;
    all_pops=[all_pops; pop];
    all_bests=[all_bests; best];
end
else
%     p=ge_createIndividual(params.genome_length, params.grammar, 0)
%     pop=repmat(p, [params.numRuns, params.popSize]);
%     best=repmat(p, [params.numRuns, 1]);
%     stats2=repmat(all_stats, [params.numRuns, 1]);
    parfor(i=1:params.numRuns, params.numcores)
        [pop, best, stats2]=feval(params.ga_fcn, params, i);
        bestfithistory(:,i)=stats2.bestfithistory;
        testfithistory(:, i)=stats2.testfithistory;
        meanfithistory(:, i)=stats2.meanfithistory;
        timehistory(:, i)=stats2.timehistory;
        numvalidhistory(:, i)=stats2.numvalidhistory;
        dissimilarityhistory(:, i)=stats2.dissimilarityhistory;
        diversityhistory(:, i)=stats2.diversityhistory;
        all_pops=[all_pops; pop];
        all_bests=[all_bests; best];
    end
    delete(pool);
end
all_stats.bestfithistory=bestfithistory;
all_stats.testfithistory=testfithistory;
all_stats.meanfithistory=meanfithistory;
all_stats.timehistory=timehistory;
all_stats.numvalidhistory=numvalidhistory;
all_stats.dissimilarityhistory=dissimilarityhistory;
all_stats.diversityhistory=diversityhistory;