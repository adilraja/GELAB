function params=ge_updateGrammarVars(params)

[x,y]=size(params.data.train_x);

for(i=1:y)
    str=strcat('X(:,', num2str(i), ')');
    params.grammar.setVars(str);
end
% disp('Updating Vars in Grammar');
% params.grammar.getVars()
% disp(i);
