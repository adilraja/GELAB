function pop=ge_initMultipleTreePop(params, runSensibleInit)

for(i=1:params.popSize)
    pop(i)=ge_createMultipleTreeIndividual(params, runSensibleInit);
    %disp(i);
end
end