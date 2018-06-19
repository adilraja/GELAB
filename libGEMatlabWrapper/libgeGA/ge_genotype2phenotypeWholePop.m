function pop=ge_genotype2phenotypeWholePop(pop)
popSize=length(pop);
for(i=1:popSize)
    pop(i).grammar.setGenotype(pop(i).genome, length(pop(i).genome));
    [phenotype_string grammar]=genotype2phenotype(pop(i).genome, pop(i).grammar);
    pop(i).string=phenotype_string;
    pop(i).valid=grammar.isPhenotypeValid();%
    pop(i).grammar=grammar;
end