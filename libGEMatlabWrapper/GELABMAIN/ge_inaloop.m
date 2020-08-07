function [all_pops, all_bests, all_stats, params]=ge_inaloop(params, results_file_name, called_external, varargin)
%This is going to run ge for multiple runs. Muhammad Adil Raja. 20 July,
%2018.
%Input: -
%   called_external: If an external program has called it then they should
%   also have set up parpool if parallel processing is being used.

clear JAVA;

if(contains(ctfroot, 'MATLAB'))
  % MATLAB is running.
  rng('shuffle', 'twister');
end


if(exist('params', 'var')==0)
    params=ge_fiddleParams;
end

libGEpath=strcat(fileparts(which('loadGrammar.m')), '/libGEjar/libGEjava.jar');

if(~called_external)
    if(params.parallel)
        if(isempty(gcp('nocreate')))
            pool=parpool(params.numcores, 'IdleTimeout', 9600);
        else
            delete(gcp);
    %         pool = gcp('nocreate');
            pool=parpool(params.numcores, 'IdleTimeout', 9600);
        end
        pctRunOnAll javaaddpath(strcat(fileparts(which('loadGrammar.m')), '/libGEjar/libGEjava.jar'));
    else
        javaaddpath(libGEpath);
    end
end

params.grammar=loadGrammar(params);
params=ge_updateGrammarVars(params);
params=ge_updateNumCoefs(params);
params=ge_updateGrammarConsts(params);

if(params.evalinws)
    ge_expandVarsinWorkSpace(params);
end

all_stats=ge_statistics;
all_pops=[];
all_bests=[];
bestfithistory=zeros(params.numGens, params.numRuns);
bestrsquaretrainhistory=zeros(params.numGens, params.numRuns);
bestrsquaretesthistory=zeros(params.numGens, params.numRuns);
testfithistory=zeros(params.numGens, params.numRuns);
meanfithistory=zeros(params.numGens, params.numRuns);

timehistory=zeros(params.numGens, params.numRuns);
numvalidhistory=zeros(params.numGens, params.numRuns);
dissimilarityhistory=zeros(params.numGens, params.numRuns);
diversityhistory=zeros(params.numGens, params.numRuns);

spxoverhistory=zeros(params.numGens, params.numRuns);
vpxoverhistory=zeros(params.numGens, params.numRuns);
subtreexoverhistory=zeros(params.numGens, params.numRuns);
weavehistory=zeros(params.numGens, params.numRuns);
tweavehistory=zeros(params.numGens, params.numRuns);

pmutationhistory=zeros(params.numGens, params.numRuns);
fpmutationhistory=zeros(params.numGens, params.numRuns);
fbmutationhistory=zeros(params.numGens, params.numRuns);



if(params.parallel~=1)
    for(i=1:params.numRuns)
        params=ge_updateParamsTerminalsScores(params);%Do a fresh load on grammar
        [pop, best, stats2, params2]=feval(params.ga_fcn, params, i);
        bestfithistory(:,i)=stats2.bestfithistory;
        testfithistory(:, i)=stats2.testfithistory;
        meanfithistory(:, i)=stats2.meanfithistory;
        bestrsquaretrainhistory(:, i)=stats2.bestrsquaretrainhistory;
        bestrsquaretesthistory(:, i)=stats2.bestrsquaretrainhistory;
        
        timehistory(:, i)=stats2.timehistory;
        numvalidhistory(:, i)=stats2.numvalidhistory;
        dissimilarityhistory(:, i)=stats2.dissimilarityhistory;
        diversityhistory(:, i)=stats2.diversityhistory;
        
        spxoverhistory(:, i)=stats2.spxoverhistory;
        vpxoverhistory(:, i)=stats2.vpxoverhistory;
        subtreexoverhistory(:, i)=stats2.subtreexoverhistory;
        weavehistory(:, i)=stats2.weavehistory;
        tweavehistory(:, i)=stats2.tweavehistory;
        pmutationhistory(:, i)=stats2.pmutationhistory;
        fpmutationhistory(:, i)=stats2.fpmutationhistory;
        fbmutationhistory(:, i)=stats2.fbmutationhistory;

        all_pops=[all_pops; pop];
        all_bests=[all_bests; best];
        params=ge_updateGenotypeCache(params, params2);
        %clc;
    end
else
%     p=ge_createIndividual(params.genome_length, params.grammar, 0)
%     pop=repmat(p, [params.numRuns, params.popSize]);
%     best=repmat(p, [params.numRuns, 1]);
%     stats2=repmat(all_stats, [params.numRuns, 1]);
    params=ge_updateParamsTerminalsScores(params);%Do a fresh load on grammar
    parfor(i=1:params.numRuns, params.numcores)
        %params=params2;
        % 
        disp(i);
        seed=floor(now);
        seed1=rem(now,1)*1e6;
        seed2=rem(seed1, 1)*1e9;
        seed3=floor(seed2)+(53*i)+seed;
        rng(seed3, 'multFibonacci');%'combRecursive');%
        [pop, best, stats2]=feval(params.ga_fcn, params, i);
        %params=ge_updateGenotypeCache(params3, params2);
        %params=params2(i);
        %params2=params3;
        bestfithistory(:,i)=stats2.bestfithistory;
        testfithistory(:, i)=stats2.testfithistory;
        meanfithistory(:, i)=stats2.meanfithistory;
        bestrsquaretrainhistory(:, i)=stats2.bestrsquaretrainhistory;
        bestrsquaretesthistory(:, i)=stats2.bestrsquaretrainhistory;
        
        timehistory(:, i)=stats2.timehistory;
        numvalidhistory(:, i)=stats2.numvalidhistory;
        dissimilarityhistory(:, i)=stats2.dissimilarityhistory;
        diversityhistory(:, i)=stats2.diversityhistory;
        
        spxoverhistory(:, i)=stats2.spxoverhistory;
        vpxoverhistory(:, i)=stats2.vpxoverhistory;
        subtreexoverhistory(:, i)=stats2.subtreexoverhistory;
        weavehistory(:, i)=stats2.weavehistory;
        tweavehistory(:, i)=stats2.tweavehistory;
        pmutationhistory(:, i)=stats2.pmutationhistory;
        fpmutationhistory(:, i)=stats2.fpmutationhistory;
        fbmutationhistory(:, i)=stats2.fbmutationhistory;
        
        all_pops=[all_pops; pop];
        all_bests=[all_bests; best];
%         params=params2;
    end
    if(~called_external)
        delete(pool);
        pause(5);
    end
end
all_stats.bestfithistory=bestfithistory;
all_stats.testfithistory=testfithistory;
all_stats.meanfithistory=meanfithistory;
all_stats.bestrsquaretrainhistory=bestrsquaretrainhistory;
all_stats.bestrsquaretesthistory=bestrsquaretesthistory;


all_stats.timehistory=timehistory;
all_stats.numvalidhistory=numvalidhistory;
all_stats.dissimilarityhistory=dissimilarityhistory;
all_stats.diversityhistory=diversityhistory;

all_stats.spxoverhistory=spxoverhistory;
all_stats.subtreexoverhistory=subtreexoverhistory;
all_stats.vpxoverhistory=vpxoverhistory;
all_stats.weavehistory=weavehistory;
all_stats.tweavehistory=tweavehistory;
all_stats.pmutationhistory=pmutationhistory;
all_stats.fpmutationhistory=fpmutationhistory;
all_stats.fbmutationhistory=fbmutationhistory;

disp('The simulation completed! Bye Bye!!');

if(~endsWith(results_file_name, '.mat'))
    fname=strcat(results_file_name, '.mat');
else
    fname=results_file_name;
end

for(i=1:params.numRuns)
    for(j=1:params.popSize)
        all_pops(i,j).result=[];
    end
end
save(fname, 'all_pops', 'all_bests', 'all_stats', 'params');

ge_plots(all_stats, varargin{:});