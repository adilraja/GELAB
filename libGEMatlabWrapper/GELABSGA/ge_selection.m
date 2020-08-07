function [individual1, individual2] = ge_selection(population, params)
%[individual1, individual2] = ge_selection(population, params). This
%version of the tournament selection algorithm was written on 22nd July,
%2018. Muhammad Adil Raja. It chooses two (fitness-wise) dissimilar
%individuals. 

% if(contains(ctfroot, 'MATLAB'))
%   % MATLAB is running.
%   rng('shuffle', 'twister');
% end

popSize=length(population);

j=2;
restart_tournament=1;

while(j<=params.tournament_size)
    
    if(restart_tournament)
        tour_ind=randperm(popSize, params.tournament_size);
        cand_ind1=tour_ind(1);%First candidate
        individual1=population(cand_ind1);%This chooses the first individual
        restart_tournament=0;
    end
    
    %Now choose the second individual
    cand_ind2=tour_ind(j);
    individual2=population(cand_ind2);
    if(individual2.fitness~=individual1.fitness && abs(individual1.age-individual2.age)<=2)%The desired individual has been found
            break;
    elseif(j>=params.tournament_size)%else restart the loop
        restart_tournament=1;
        j=1;
    end
    j=j+1;
end
end