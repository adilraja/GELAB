function [individual1, individual2] = ge_tournamentSelection(population, params)
%[individual1, individual2] = ge_selection(population, params). This
%version of the tournament selection algorithm was written on 22nd July,
%2018. Muhammad Adil Raja. It chooses two (fitness-wise) dissimilar
%individuals. 
popSize=length(population);

tournament=randperm(popSize, params.tournament_size);
individual1=population(tournament(1));
individual2=population(tournament(2));

end