function [pop, params]=ge_initUniqueValidMultipleTreePopUsingSensibleInit(params)
%function pop=ge_initValidPop(params, runSensibleInitialization).
%Creates a valid population using sensible initialization.
%Written by Muhammad Adil Raja. 18 August, 2018

precision=params.precision;
params.precision=25;

j=1;
fit_vec=[];%This is a fitness cache
tot=0;

    while(j<=params.popSize)
        ensemble=ge_createEnsemble(params);
        tot=tot+1;
        [ensemble, params]=ge_evalEnsemble(ensemble, params);
        pop(i)=ensemble;
        j=j+1;
    end
end





