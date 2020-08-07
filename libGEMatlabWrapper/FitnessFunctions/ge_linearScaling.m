function [intercept, slope]=ge_linearScaling(evolved,target)
%This is the version of linear scaling as proposed by Maarten Keijzer for
%symbolic regression.
i=0;
% if length(evolved) ~= length(target)
%      disp('No of Target Values is not the same as Evolved Values');
%      [x, y]=size(target);
%      evolved=zeros(x, y)*evolved(1);%perhaps evolved was just a constant returned by a program having no variables.
%    %  disp('Exiting .... ');
%     % exit(0);
%  end
 
 meanTarget = mean(target);
 meanEvolved = mean(evolved);
 
 b = 1; a=0; numerator=0;denominator=0;
 
      factor1 = evolved-meanEvolved;
      factor2=target-meanTarget;
     numerator= sum(factor2.*factor1);
     denominator =sum(power(factor1,2));
     slope=1;
if(denominator~=0)     
     slope=numerator/denominator;
%  elseif (denominator==0) 
%      slope=0;%i.e. when the variance in evolved y is zero
elseif(meanEvolved == 0)  
     slope = 1;
else
    slope = meanTarget ./ meanEvolved;
%  else slope=1;
end
 intercept=meanTarget - slope*meanEvolved; 