function pop=ge_initValidPopUsingSensibleInit(params, popSize)
%function pop=ge_initValidPop(params, runSensibleInitialization).
%Creates a valid population using sensible initialization.
%Written by Muhammad Adil Raja. 21st July, 2018

popSize=params.popSize;
j=0;
while(j<popSize)
    temp_ind=ge_createIndividual(params.genome_length, params.grammar, 1);
    if(temp_ind.valid==1)
        j=j+1;
        pop(j)=temp_ind;
    end
end
disp('Returning from initValidPop');
end