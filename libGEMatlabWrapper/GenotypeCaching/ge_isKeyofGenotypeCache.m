function keyFound = ge_isKeyofGenotypeCache(ind, genotypeCache)
%function [ind keyfound]= ge_readFromGenotypeCache(ind, genotypeCache)
%This read from the genotype cache if a key/value pair is present in the
%cache. If found, it returns the value. genotypeCache is of type
%containers.Map and ind is a struct. Keyfound is boolean flag suggesting is
%a key was found in the cache. Written by Muhammad Adil Raja, 24th July,
%2018.

key1=sprintf('%d', ind.genome);
keyFound=isKey(genotypeCache, key1);