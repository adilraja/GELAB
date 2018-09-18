function params = ge_addIndtoGenotypeCache(ind, params)
%function map = ge_addIndtoGenotypeCache(ind, map). genotypeCache is of type
% containers.Map and ind is a struct
%This function has been
%written by Muhammad Adil Raja. 24th July 2018.


%genotypeCache, genotypeCacheCounter
%Remove extra entries
if(params.genotypeCacheCounter.length>=params.cacheSize)
    counts=values(params.genotypeCacheCounter);
    keySet=keys(params.genotypeCacheCounter);
    count_array=cell2mat(counts);
    [count_ind, I]=min(count_array);
    remove(params.genotypeCacheCounter, keySet{I(1)});
    remove(params.genotypeCache, keySet{I(1)});
end

key1=sprintf('%d', ind.genome);

%Now try to add the new individual to the caches.
if(ge_isKeyofGenotypeCache(ind, params.genotypeCacheCounter))%Entry already exists
    value=params.genotypeCacheCounter(key1);
    params.genotypeCacheCounter(key1)=value+1;%just increment the count
else
    params.genotypeCache(key1)=ind;
    params.genotypeCacheCounter(key1)=1;
end

