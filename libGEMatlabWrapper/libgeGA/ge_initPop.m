function pop=ge_initPop(popsize, genome_length, grammar)

for(i=1:popsize)
    pop(i)=ge_createIndividual(genome_length, grammar);
end
end