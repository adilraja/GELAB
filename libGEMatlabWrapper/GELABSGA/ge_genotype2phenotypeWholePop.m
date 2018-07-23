function [pop, grammar]=ge_genotype2phenotypeWholePop(pop, grammar)
popSize=length(pop);
for(i=1:popSize)
    [phenotype_string grammar]=genotype2phenotype(pop(i).genome, grammar);
    pop(i).string=phenotype_string;
    pop(i).valid=grammar.isPhenotypeValid();%
    pop(i).treeDepth=grammar.getTreeDepth();
    %pop(i).grammar=grammar;
end