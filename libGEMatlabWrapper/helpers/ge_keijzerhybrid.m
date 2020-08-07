function [all_pops, all_bests, all_stats, params]=ge_keijzerhybrid(numRuns)
if(contains(ctfroot, 'MATLAB'))
  % MATLAB is running.
  rng('shuffle', 'twister');
end
p=load('keijzerparams.mat');
params=p.params;
all_pops=[];
all_bests=[];
all_stats=[];

if(exist('numRuns', 'var')==1)
    params.numRuns=numRuns;
    params.numcores=numRuns;
end
params.numCoefs=5;
params.UB=100;
%params.selectionFunction='ge_selection';
%  params.popSize=1000;

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


for(i=1:4)
    if(i==1)
        params.hybridAlgorithm='sa';
    elseif(i==2)
        params.hybridAlgorithm='ga';
    elseif(i==3)
        params.hybridAlgorithm='pso';
    else
        params.hybrid=0;
        params.fitnessFunction='ge_mseonly';
    end
    [size_mat, pops, bests, stats]=ge_keijzer('temp.mat', 1, params);
    all_pops=[all_pops; pops];
    all_bests=[all_bests; bests];
    all_stats=[all_stats; stats];
end


if(params.parallel)
    delete(pool);
    pause(5);
end
save('keijzersim.mat', '-v7.3', 'all_bests', 'all_stats', 'params');