function individual=ge_msetargetweighted(individual, params, train_y)
%function mean_squared_error=ge_mse(evolved_data, target_data)
%This function computes mean squared error of the data. Written by Muhammad
%Adil Raja, 20th June, 2018. Input: - evolved_data, target_data, Output: -
%mse.
%Apart from simple mse, this fitness function weighs the error in every
%instance of data proportional to the difference of the traget value with
%the mean of the target data. This fitness function tries to vercome the
%problem where the evolved data tilts more towards the mean of the target.
%In other words, this fitness function tries to tilt the predictions more
%towards the extreme values in the target data.

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
        mean_target_data=mean(train_y);

        difference_from_the_mean_target_data=power(train_y-mean_target_data,2);
        data_difference=result-train_y;
        squared_error=power(data_difference, 2);
        mean_squared_error_weighted=mean(squared_error.*difference_from_the_mean_target_data);
        individual.fitness=mean_squared_error_weighted;
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
 
end





% evolved_data=evolved_data(:);
% target_data=target_data(:);





