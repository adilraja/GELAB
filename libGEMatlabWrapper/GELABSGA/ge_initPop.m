function pop=ge_initPop(params, runSensibleInitialization)

for(i=1:params.popSize)
    pop(i)=ge_createIndividual(params, runSensibleInitialization);
    %disp(i);
end
end