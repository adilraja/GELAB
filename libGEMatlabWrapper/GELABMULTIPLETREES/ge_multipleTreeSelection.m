function [ensemble1, ensemble2] = ge_multipleTreeSelection(population, params)
%[individual1, individual2] = ge_ensembleSelection(population, params). This
%version of the tournament selection algorithm was written on 18th August,
%2018. Muhammad Adil Raja. It chooses two (fitness-wise) dissimilar
%individuals. 
% popSize=length(population);
% 
% 
% tour_ind=randperm(popSize, params.tournament_size);
% ensemble1=tour_ind(1);%First candidate
% ensemble2=tour_ind(2);

[ensemble1, ensemble2] = ge_selection(population, params);

end