function params=ge_updateParamsTerminalsScores(params)
%This function sets the terminals_scores table in params. Written by
%Muhammad Adil Raja. 16th December, 2019

% params.grammar=loadGrammar(params);%Load the grammar again, just in case
grammar=params.grammar;
terminals=grammar.getTerminals();
terminals=string(char(terminals));
terminals = strrep(terminals,' ','');%Remove spaces from strings of terminals

scores=zeros(length(terminals), 1);

terminals_scores=table(terminals, scores);

params.terminals_scores=terminals_scores;

disp('Terminals updated!');