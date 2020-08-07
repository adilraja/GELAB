function params=ge_removeProduction(params)
%This function removes a production from the grammar that has the lowest
%score. Written by Muhammad Adil Raja. 16th December, 2019

terminals_scores=params.terminals_scores;

[x, I]=min(terminals_scores.scores);

production=terminals_scores.terminals(I(1));

if(params.grammar.removeProduction(java.lang.String(production))==1)%Remove the production
    params.terminals_scores.scores(I(1))=500000;%Give it a high score as it cannot be removed.
else
    params.terminals_scores(I(1),:)=[];%Remove the entry from the terminals_scores table as well.
end

