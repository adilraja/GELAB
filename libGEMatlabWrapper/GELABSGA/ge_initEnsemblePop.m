function pop=ge_initEnsemblePop(params, runSensibleInitialization)

for(i=1:params.popSize)
    pop(i)=ge_createEnsemble(params.genome_length, params.grammar, runSensibleInitialization);
    %disp(i);
end
end