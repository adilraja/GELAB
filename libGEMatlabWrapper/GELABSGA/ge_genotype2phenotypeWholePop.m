function pop=ge_genotype2phenotypeWholePop(pop, params)
popSize=length(pop);
for(i=1:popSize)
    if(params.genotypeCaching==1)
        if(~ge_isKeyofGenotypeCache(pop(i), params.genotypeCache))
            [phenotype_string grammar]=genotype2phenotype(pop(i).genome, params.grammar);
            pop(i).string=phenotype_string;
            pop(i).valid=grammar.isPhenotypeValid();%
            pop(i).treeDepth=grammar.getTreeDepth();
            %params = ge_addIndtoGenotypeCache(pop(i), params);Dont put
            %un-evaluated inds to the cache.
            %pop(i).grammar=grammar;
        else
            pop(i)=params.genotypeCache(sprintf('%d', pop(i).genome));
        end
    else%if no caching is used
        [phenotype_string grammar]=genotype2phenotype(pop(i).genome, params.grammar);
        pop(i).string=phenotype_string;
        pop(i).valid=grammar.isPhenotypeValid();%
        pop(i).treeDepth=grammar.getTreeDepth();
    end
end