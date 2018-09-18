function params=ge_updateGenotypeCache(params, params2)
%function params=ge_updateGenotypeCache(). This function takes in two
%caches and combines them to return a single genotype cache. Written by
%Muhammad Adil Raja, 24th July, 2018.

cache_keys=keys(params2.genotypeCache);
numKeys=length(cache_keys);
for(i=1:numKeys)
        if(isKey(params2.genotypeCache, cache_keys{i}))
            individual=params2.genotypeCache(cache_keys{i});
            params = ge_addIndtoGenotypeCache(individual, params);
        else
end

end

