function [individual1, individual2] = ge_lpptour(population, params)
%[individual1, individual2] = ge_selection(population, params). This
%version of the tournament selection algorithm was written on 31st October,
%2018. Muhammad Adil Raja. It chooses two (fitness-wise) dissimilar
%individuals. Moreover, it implements lexicographic parsimony pressure.
val_ind=[];

popSize=length(population);

%Only use valid individuals in selection!
for(i=1:popSize)
    val_ind(i)=population(i).valid;
end

val_indices=find(val_ind==1);

population2=population(val_indices);

population=population2;
popSize=length(population);


j=2;
restart_tournament=1;
max_tournaments=20;
tournaments=0;
while(j<=params.tournament_size)
    
    if(restart_tournament)
        tour_ind=randperm(popSize, params.tournament_size);
        tournament=population(tour_ind);
        individual1=tournament(1);%This chooses the first individual
        restart_tournament=0;
        tournaments=tournaments+1;
        %Extract the fitness and sizes of the remaining individuals in the
        %tournament
        fitvec=zeros(params.tournament_size-1,1);
        sizvec=zeros(params.tournament_size-1,1);
        for(i=2:params.tournament_size)
            fitvec(i-1,1)=population(tour_ind(i)).fitness;
            sizvec(i-1,1)=population(tour_ind(i)).treeDepth;
        end
    end  
    
    %Now choose the second individual
    cand_ind2=tour_ind(j);
    temp_ind=population(cand_ind2);
    if(temp_ind.fitness~=individual1.fitness && abs(individual1.age-temp_ind.age)<2)%
        if(j>=params.tournament_size)
            individual2=temp_ind;%We have no option and the second individual has been found.
            break;
        end
        fit_ind=find(fitvec(j+1:length(fitvec),1)==temp_ind.fitness);
        fit_ind=fit_ind+j;%Compensate for the offsets
        if(isempty(fit_ind))%Everything is fitness wise dissimilar to the first ind
            individual2=temp_ind;
            break;%The desired individual has been found
        else
            [tmp sz_ind]=min(sizvec(fit_ind,1));
            cand_ind2=tour_ind(sz_ind+1);%Because sizvec is one element shorter
            individual2=population(cand_ind2);%The desired individual has been found
            break;
        end
    elseif(j>=params.tournament_size)%else restart the loop
        restart_tournament=1;
        j=1;
    end
    if(tournaments>max_tournaments)%If nothing is being found after repeated trials (perhaps the diversity is really low)
        [individual1, individual2] = ge_tournamentSelection(population, params);%Perform a simple tournament selection
        break;
    end
    j=j+1;
end
end