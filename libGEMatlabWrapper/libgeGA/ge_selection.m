function [individual1, individual2] = ge_selection(population, tournament_size)
    for(i=1:length(population))
      fitness(i)=population(i).fitness;
    end
    x=length(fitness);
    for(i=1:tournament_size)
      candidate(i)=floor(rand(1)*(x-1))+1;
      if i > 1
            % Make sure that same candidate is not choosen.
            while ~isempty(find(candidate(1 : i - 1) == candidate(i)))
                candidate(i) = round((x-1)*rand(1))+1;
                if (candidate(i) > length(fitness))
                    candidate(i) = length(fitness);
                end
            end
        end
    end
    [ind1, index1]=min(fitness(candidate));
    fitness(candidate(index1))=500000;
    [ind2, index2]=min(fitness(candidate));
    fitness(candidate(index2))=500000;
%    candidate(index1);
%    candidate(index2);
    
    individual1=population(candidate(index1));
    individual2=population(candidate(index2));

end