function [pop, params]=ge_evalPop(pop, params)
%Given a pop and params, evaluate the whole pop.
%function [pop, params]=ge_evalPop(pop, params)
%Muhammad Adil Raja. July, 2018.
    popsize=length(pop);
    j=0;
    for(i=1:popsize)
        if(params.genotypeCaching==1)%if the individual is already evaluated, try to use its evaluation from the cache
            if(~ge_isKeyofGenotypeCache(pop(i), params.genotypeCache))
                %Do nothing if the individual is not in the cache, you have
                %to evaluate it any way!
                if(pop(i).isEvaluated)%If the individual is already evaluated
                    if(params.hybrid)%However, if hybrid optimization is used, perform the following checks
                         if(pop(i).age>=params.criticalAge1 || pop(i).age<=params.criticalAge2)
                            pop(i).isEvaluated=0;
                            if(pop(i).valid==1)
                                pop(i)=feval(params.fitnessFunction, pop(i), params, params.data.train_y);
                            elseif(pop(i).valid==0)
                                pop(i).fitness=params.maxBadFitness*2;
                                if(params.data.test)
                                    pop(i).testFitness=params.maxBadFitness;
                                end
                            end  
                         end
                    end
%                     disp('Where am I getting stuck? 1');
                else%If the individual is not already evaluated
                    if(pop(i).valid==1)
                        pop(i)=feval(params.fitnessFunction, pop(i), params, params.data.train_y);
                    elseif(pop(i).valid==0)
                        pop(i).fitness=params.maxBadFitness*2;
                        if(params.data.test)
                            pop(i).testFitness=params.maxBadFitness*2;
                        end
                    end
                end
                pop(i).age=pop(i).age+1;
                params=ge_addIndtoGenotypeCache(pop(i), params);
%                 disp('Where am I getting stuck? 2');
            else%if the individual is present in the cache
                 if(pop(i).isEvaluated)%If it is already evaluated (no need to re-evaluate it).
                     if(params.hybrid)%However, if hybrid optimization is used, perform the following checks
                         if(pop(i).age>=params.criticalAge1 || pop(i).age<=params.criticalAge2)
                            pop(i).isEvaluated=0;
                            if(pop(i).valid==1)
                                pop(i)=feval(params.fitnessFunction, pop(i), params, params.data.train_y);
                            elseif(pop(i).valid==0)
                                pop(i).fitness=params.maxBadFitness*2;
                                if(params.data.test)
                                    pop(i).testFitness=params.maxBadFitness*2;
                                end
                            end  
                         end
                     end
                     pop(i).age=pop(i).age+1;
%                      disp('Where am I getting stuck? 3');
                else%If it is not evaluated, see if the corresponding entry in the cache is evaluated!
                    if(params.hybrid)%However, if hybrid optimization is used, perform the following checks
                         if(pop(i).age>=params.criticalAge1 || pop(i).age<=params.criticalAge2)
                            pop(i).isEvaluated=0;
                            if(pop(i).valid==1)
                                pop(i)=feval(params.fitnessFunction, pop(i), params, params.data.train_y);
                            elseif(pop(i).valid==0)
                                pop(i).fitness=params.maxBadFitness*2;
                                if(params.data.test)
                                    pop(i).testFitness=params.maxBadFitness*2;
                                end
                            end  
                         end
                    else%if hybrid optimization is not used
                        temp_key=sprintf('%d', pop(i).genome);
                        temp_ind=params.genotypeCache(temp_key);
                        if(temp_ind.isEvaluated)%If the corresponding entry in the cache is evaluated.
                            pop(i)=temp_ind;
%                             pop(i).fitness=temp_ind.fitness;
%                             pop(i).testFitness=temp_ind.testFitness;
%                             pop(i).valid=temp_ind.valid;
%                             pop(i).constants=temp_ind.constants;
%                             pop(i).slope=temp_ind.slope;
%                             pop(i).intercept=temp_ind.intercept;
%                             pop(i).result=temp_ind.result;
                        else%If the corresponding entry in the cache is not evaluated
                            if(pop(i).valid==1)
                                pop(i)=feval(params.fitnessFunction, pop(i), params, params.data.train_y);
                            elseif(pop(i).valid==0)
                                pop(i).fitness=params.maxBadFitness*2;
                                if(params.data.test)
                                    pop(i).testFitness=params.maxBadFitness*2;
                                end
                            end       
                        end
                    end
                    
                    
                    pop(i).age=pop(i).age+1;
%                     disp('Where am I getting stuck? 4');
                 end
                 params=ge_addIndtoGenotypeCache(pop(i), params);     
            end
            
        else%if caching is not used
            if(pop(i).valid==1)
                    pop(i)=feval(params.fitnessFunction, pop(i), params, params.data.train_y);
            elseif(pop(i).valid==0)
                pop(i).fitness=params.maxBadFitness*2;
                if(params.data.test)
                    pop(i).testFitness=params.maxBadFitness*2;
                end
            end
            pop(i).age=pop(i).age+1;
        end
        
        if(pop(i).valid==1)
            j=j+1;
        end
    end
    numValid=j;
%     disp('Returning from evalPop');
end