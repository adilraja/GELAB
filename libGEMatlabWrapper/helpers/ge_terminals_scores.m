function params=ge_terminals_scores(pop, params)
%This function computes overall scores for each the terminals (functions
%and variables) in a GE sense. The scores are used to remove productions
%from the grammar that are least being used. Written by Muhammad Adil Raja.
%16th December, 2019.

popSize=length(pop);

terminals_scores=params.terminals_scores;

num_terminals=height(terminals_scores);

for(i=1:num_terminals)%For each terminals
    for(j=1:popSize)%Scan each individual
        if(params.lowerisbetter)
            weight=1/pop(j).fitness;%Just invert the fitness to get a higher score.
        else
            weight=pop(j).fitness;
        end
        found1=strcmp(terminals_scores.terminals(i), pop(j).terminals_scores.terminals);%Find the index which matches the terminal
        I=find(found1==1);
%         disp(pop(j).terminals_scores.terminals(I));
        if(~isempty(I))
            terminals_scores.scores(i)=terminals_scores.scores(i)+(pop(j).terminals_scores.scores(I)*weight);%Update the scores in params.terminals_scores
            
        end
    end
end

terminals_scores.scores=terminals_scores.scores/popSize;%Normalize the scores somehow.

params.terminals_scores=terminals_scores;

