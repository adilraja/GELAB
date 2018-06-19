function pop=ge_initPop(popsize, genome_length, grammar, rungeno2pheno)

for(i=1:popsize)
    pop(i)=ge_createIndividual(genome_length, grammar, rungeno2pheno);
end
end