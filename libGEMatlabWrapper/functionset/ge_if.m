function result=ge_if(condition,actiontrue,actionfalse)
%MYIF    Calculates the result of an IF-THEN-ELSE statement.
%   MYIF(CONDITION,ACTIONTRUE,ACTIONFALSE) evaluates the CONDITION
%   and returns the result of evaluating ACTIONTRUE if CONDITION is
%   true, or the result of evaluating ACTIONFALSE if CONDITION is
%   false. If condition evaluates to any number different from 0,
%   CONDITION is true.
%
%   Input arguments:
%      CONDITION - the expression to evaluate (expression)
%      ACTIONTRUE - the action if CONDITION is true (expression)
%      ACTIONFALSE - the action if CONDITION is false (expression)
%   Output arguments:
%      RESULT - the result of evaluating ACTIONTRUE or ACTIONFALSE (double)
%
%   Copyright (C) 2003-2004 Sara Silva (sara@dei.uc.pt)
%   This file is part of the GPLAB Toolbox

% first make sure all matrices are the same size:
m=max([length(condition) length(actiontrue) length(actionfalse)]);
if length(condition)<m
   condition=repmat(condition,m,1);
end
if length(actiontrue)<m
   actiontrue=repmat(actiontrue,m,1);
end
if length(actionfalse)<m
   actionfalse=repmat(actionfalse,m,1);
end

result=zeros(size(condition));

b=condition;

% for those who evaluate true, do action true:
i=find(b~=0);
result(i)=actiontrue(i);


% for those who evaluate false, do action false:
i=find(b==0);
result(i)=actionfalse(i);