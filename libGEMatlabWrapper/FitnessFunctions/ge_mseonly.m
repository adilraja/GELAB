function individual = ge_mseonly (individual, params, train_y)
if(individual.isEvaluated)
    return;%No need to re-evaluate this individual
end
individual.isEvaluated=1;%Mark this individual as evaluated, so that it does not get re-evaluated
    X=params.data.train_x;
    w=individual.constants;
   
    %in subsequent generations. This is supposed to save evaluation time.
    if(individual.valid==1 && individual.treeDepth<=params.maxDepth)%if this is a valid individual
        result=eval(individual.string);
        individual.result=result;
    else
        individual.fitness=params.maxBadFitness;
        if(params.data.test)
            individual.testFitness=params.maxBadFitness;
        end
        %disp('How often do I come here?');
        %individual.valid=0;Never do this here
        return;
     end
        if(length(result)~=length(train_y))
            individual.fitness=params.maxBadFitness;%really bad fitness
            individual.testFitness=params.maxBadFitness;%Really bad testFitness
            individual.result=ones(length(train_y), 1)*params.maxBadFitness;
            %individual.valid=0;
            return;
        end
        individual.fitness=ge_mse(result, train_y);
        % now limit fitness precision, to eliminate rounding error problem:
         individual.fitness=fixdec(individual.fitness, params.precision);
        if(isnan(individual.fitness)||isinf(individual.fitness))
            individual.fitness=params.maxBadFitness;%Give a very large value to fitness so that the individual is removed:Adil
            if(params.data.test)
                individual.testFitness=params.maxBadFitness;
            end
            return;
        end
%     else
%         individual.fitness=50000;
%         individual.testFitness=50000;
%         return;
%     end
    %You can plug in your own fitness function here.
    if(params.data.test==0)
        return;
    end
    %Compute testfitness
%     [x, y]=size(params.data.test_x);
%     for(i=1:y)
%        val=strcat('params.data.test_x(:,', num2str(i),')');
%        var2=strcat(var, num2str(i));
%        eval([var2 '=' val ';']); 
%     end
%     testResult=eval(individual.string);
%     individual.testResult=testResult;
%     individual.testFitness=ge_mse(testResult, params.data.test_y);
%     individual.testFitness=fixdec(individual.testFitness, params.precision);
%     if(isnan(individual.testFitness) || isinf(individual.testFitness))
%         individual.testFitness=params.maxBadFitness;
%     end
end