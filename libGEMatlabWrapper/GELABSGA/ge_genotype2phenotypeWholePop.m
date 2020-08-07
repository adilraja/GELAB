function pop=ge_genotype2phenotypeWholePop(pop, params)
%Given a population and params, perform genotype to phenotype mapping for
%the whole population.
% function pop=ge_genotype2phenotypeWholePop(pop, params)
% Input: pop, params. Output: pop.
% Written by Muhammad Adil Raja, September 2018.
popSize=length(pop);
for(i=1:popSize)
    if(params.genotypeCaching==1)
        if(~ge_isKeyofGenotypeCache(pop(i), params.genotypeCache))%if the individual is not in the cache, do the mapping and add it to the cache.
            [phenotype_string, grammar, lhs_rep_array, lhs_rep_inds_array, numWraps]=genotype2phenotype(pop(i).genome, params.grammar);
            pop(i).string=phenotype_string;
            pop(i).numWraps;
            pop(i).lhs_rep_array=lhs_rep_array;
            pop(i).lhs_rep_inds_array=lhs_rep_inds_array;
            pop(i).lhs_rep_type_array=grammar.getLHSRepTypeIntArray();
            pop(i).valid=grammar.isPhenotypeValid();%
            pop(i).treeDepth=grammar.getTreeDepth();
            %params = ge_addIndtoGenotypeCache(pop(i), params);Dont put
            %un-evaluated inds to the cache.
            %pop(i).grammar=grammar;
        else%if the individual is already in the cache, use its evaluation.
            pop(i)=params.genotypeCache(sprintf('%d', pop(i).genome));
        end
    else%if no caching is used
        [phenotype_string grammar lhs_rep_array lhs_rep_inds_array]=genotype2phenotype(pop(i).genome, params.grammar);
        pop(i).string=phenotype_string;
        pop(i).valid=grammar.isPhenotypeValid();%
        pop(i).numWraps=grammar.getNumWraps();
        pop(i).treeDepth=grammar.getTreeDepth();
        pop(i).lhs_rep_array=lhs_rep_array;
        pop(i).lhs_rep_inds_array=lhs_rep_inds_array;
        pop(i).lhs_rep_type_array=grammar.getLHSRepTypeIntArray();
    end
end