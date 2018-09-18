function [pop, params]=ge_initUniqueValidPopUsingSensibleInit(params)
%function pop=ge_initValidPop(params, runSensibleInitialization).
%Creates a valid population using sensible initialization.
%Written by Muhammad Adil Raja. 21st July, 2018

precision=params.precision;
params.precision=25;

j=1;
fit_vec=[];%This is a fitness cache
tot=0;

while(j<=params.popSize)
    temp_ind=ge_createIndividual(params.genome_length, params.grammar, 1);
    tot=tot+1;
    %fit_vec=[fit_vec temp_ind.fitness];
    if(temp_ind.valid==1)
        temp_ind=feval(params.fitnessFunction, temp_ind, params, params.data.train_y);
        temp_ind.isEvaluated=1;
        params = ge_addIndtoGenotypeCache(temp_ind, params);
        if(j>1)
            I=find(fit_vec==temp_ind.fitness);
            if(isempty(I))
                pop(j)=temp_ind;
                fit_vec=[fit_vec; temp_ind.fitness];
                fprintf('Creating unique and valid individual: %d/%d\n', j, tot);
                j=j+1;
            end
        elseif(j==1)
            fit_vec=[fit_vec; temp_ind.fitness];
            pop(j)=temp_ind;
            j=j+1;
        end
    end
end
end





% while(j<=popSize)
%     temp_ind=ge_createIndividual(params.genome_length, params.grammar, 1);
%     tot=tot+1;
%     if(~ge_isKeyofGenotypeCache(temp_ind, params.genotypeCache))
%         %do nothing if the genotype exist
%         if(temp_ind.valid==1)
%             temp_ind=feval(params.fitnessFunction, temp_ind, params);
%             temp_ind.isEvaluated=1;
%             params=ge_addIndtoGenotypeCache(temp_ind, params);
%             pop(j)=temp_ind;
%             fprintf('Creating unique and valid individual: %d/%d\n', j, tot);
%             j=j+1;
%         end
%     end
% end
% disp('Returning from initUniqueValidPop');
% params.precision=precision;
% end



% fit_vec=[];%This is a fitness cache

