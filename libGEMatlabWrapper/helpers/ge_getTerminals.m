function terminals=ge_getTerminals(params);
%Returns the active terminals. Written by Muhammad Adil Raja. 17th
%December, 2019.

grammar=params.grammar;
terminals=grammar.getTerminals();
terminals=string(char(terminals));
terminals = strrep(terminals,' ','');%Remove spaces from strings of terminals

terminals2=[];
for(i=1:length(terminals))
    terminals2=strcat(terminals2, {', '}, terminals(i));
end

terminals=terminals2;