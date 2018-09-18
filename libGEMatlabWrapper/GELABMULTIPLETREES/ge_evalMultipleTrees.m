%Written by Muhammad Adil Raja. 6th September, 2018
%function [multiTree, params]=ge_evalMultipleTrees(multiTree, params)
%     numInds=length(multiTree.ind);
%     for(i=1:numInds)
%         [inds, params]=ge_evalPop(multiTree.ind(i), params);
%         multiTree.ind(i)=inds;
%     end
%     
% end
    

function [multiTree, params]=ge_evalMultipleTrees(multiTree, params)
    numInds=length(multiTree.ind);
%     for(i=1:numInds)
        [inds, params]=ge_evalPopMT(multiTree.ind, params, params.data.train_y);
        multiTree.ind=inds;
%     end
    
end
    