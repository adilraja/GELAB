%function ensemble = ge_ensembleMutation(ensemble, params). Written by
%Muhammad Adil Raja, 18th August, 2018.
function multiTree = ge_multipleTreeMutation(multiTree, params)
    for(i=1:params.numMultipleTrees)
        multiTree.ind(i) = ge_mutation(multiTree.ind(i), params);
    end   
end