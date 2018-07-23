function res=ge_expandVarsinWorkSpace(params)
%This function expands the data variables in the base workspace. Written by
%Muhammad Adil Raja, 22 July, 2018.
var='X';
    [x, y]=size(params.data.train_x);
    for(i=1:y)
%        val=strcat('params.data.train_x(:,', num2str(i),')');
        var2=strcat(var, num2str(i));
%        evalin('base', [var2 '=' val ';']); 
         assignin('base', var2, params.data.train_x(:, i)); 
    end