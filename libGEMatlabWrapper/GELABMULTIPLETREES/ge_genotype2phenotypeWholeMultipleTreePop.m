%function pop=ge_genotype2phenotypeWholeEnsemblePop(pop, params). Muhammad
%Adil Raja 18th August, 2018.
function pop=ge_genotype2phenotypeWholeMultipleTreePop(pop, params)
    popSize=length(pop);
    for(i=1:popSize)
        pop(i).ind=ge_genotype2phenotypeWholePop(pop(i).ind, params);
    end
end