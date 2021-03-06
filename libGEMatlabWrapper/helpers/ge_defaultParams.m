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
params.mutationProbability=1;
params.noxoverp=0.1;
params.spxoverp=0.1;
params.vpxoverp=0.2;
params.subtreexoverp=0.2;
params.weavep=0.2;
params.tweavep=0.2;
params.nomutationp=0.2;%
params.pmutationp=0.2;%Point mutation
params.fpmutationp=0.2;%Few points mutation
params.fbmutationp=0.2;%%fixed bounds mutation
params.stmutationp=0.2;
%params.vbmutationp=0.25;%variable bounds mutation
if(params.hybrid)
    params.hybridFraction=0.25;%Proportion of individuals to be treated with numerical optimization
    params.criticalAge1=1;
    params.criticalAge2=5;
end

params.selectionFunction='ge_lpptour';



params.genotypeCaching=input('Do you want to use genotype caching? (0 for no 1 for yes)?\n');
if(params.genotypeCaching==1)
    params.cacheSize=3000;
    params.genotypeCache=containers.Map;
    params.genotypeCacheCounter=containers.Map;
end