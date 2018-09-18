function params=ge_defaultParams(params)
%This function simply sets the default params. Written by Muhammad Adil
%Raja, 24th July, 2018

params.maxDepth=17;
params.initMaxDepth=7;
params.maxWraps=9;
params.precision=4;
params.tournament_size=6;
params.evalinws=0;%Whether you want to eval in base workspace?
params.maxBadFitness=500000;
params.mutationProbability=0.25;

params.genotypeCaching=1;
if(params.genotypeCaching)
    params.cacheSize=3000;
    params.genotypeCache=containers.Map;
    params.genotypeCacheCounter=containers.Map;
end