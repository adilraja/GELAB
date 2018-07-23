function pop=ge_initUniqueValidPopUsingSensibleInit(params)
%function pop=ge_initValidPop(params, runSensibleInitialization).
%Creates a valid population using sensible initialization.
%Written by Muhammad Adil Raja. 21st July, 2018

j=1;
fit_vec=[];%This is a fitness cache

while(j<params.popSize)
    temp_ind=ge_createIndividual(params.genome_length, params.grammar, 1);
    
    %fit_vec=[fit_vec temp_ind.fitness];
    if(temp_ind.valid==1)
        temp_ind=feval(params.fitnessFunction, temp_ind, params);
        if(j==1)
            fit_vec=[fit_vec; temp_ind.fitness];
            pop(j)=temp_ind;
            j=j+1;
        else
            I=find(fit_vec==temp_ind.fitness);
            if(isempty(I))
                pop(j)=temp_ind;
                fit_vec=[fit_vec; temp_ind.fitness];
                fprintf('Creating unique and valid individual: %d\n', j);
                j=j+1;
            end
        end
    end
end
disp('Returning from initValidPop');
end