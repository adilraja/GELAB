% ## Copyright (C) 2017 FGFS
% ## 
% ## This program is free software; you can redistribute it and/or modify it
% ## under the terms of the GNU General Public License as published by
% ## the Free Software Foundation; either version 3 of the License, or
% ## (at your option) any later version.
% ## 
% ## This program is distributed in the hope that it will be useful,
% ## but WITHOUT ANY WARRANTY; without even the implied warranty of
% ## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% ## GNU General Public License for more details.
% ## 
% ## You should have received a copy of the GNU General Public License
% ## along with this program.  If not, see <http://www.gnu.org/licenses/>.
% 
% ## -*- texinfo -*- 
% ## @deftypefn {Function File} {@var{retval} =} Evaluate (@var{input1}, @var{input2})
% ##
% ## @seealso{}
% ## @end deftypefn
% 
% ## Author: FGFS <fgfs@fgfs-Precision-WorkStation-T3500>
% ## Created: 2017-03-16

function individual = ge_evaluate (individual, params)
    individual.isEvaluated=1;%Mark this individual as evaluated, so that it does not get re-evaluated
    if(params.evalinws==0)
        var='X';
        [x, y]=size(params.data.train_x);
        for(i=1:y)
            val=strcat('params.data.train_x(:,', num2str(i),')');
            var2=strcat(var, num2str(i));
            eval([var2 '=' val ';']);
        end
    end
   
    %in subsequent generations. This is supposed to save evaluation time.
    if(individual.valid==1 && individual.treeDepth<=params.maxDepth)%if this is a valid individual
        if(params.evalinws)
            str=strcat(char(individual.string), ';');
            %str2=char(str);
            result=evalin('base', str);
        else
            result=eval(individual.string);
        end
            individual.result=result;
    else
            individual.fitness=params.maxBadFitness;
            if(data.test)
                individual.testFitness=params.maxBadFitness;
            end
            %disp('How often do I come here?');
            %individual.valid=0;Never do this here
            return;
     end
        if(length(result)~=length(params.data.train_y))
            individual.fitness=params.maxBadFitness;%really bad fitness
            individual.testFitness=params.maxBadFitness;%Really bad testFitness
            %individual.valid=0;
            return;
        end
         [individual.intercept, individual.slope]=ge_linearScaling(result, params.data.train_y);
        individual.fitness=ge_mse(individual.slope*result+individual.intercept, params.data.train_y);
        % now limit fitness precision, to eliminate rounding error problem:
         individual.fitness=fixdec(individual.fitness, params.precision);
        if(isnan(individual.fitness)||isinf(individual.fitness))
            individual.fitness=params.maxBadFitness;%Give a very large value to fitness so that the individual is removed:Adil
            if(params.data.test)
                individual.testFitness=params.maxBadFitness;
            end
            return;
        end
    %You can plug in your own fitness function here.
    if(params.data.test==0)
        return;
    end
    %Compute testfitness
    individual=ge_computeTestFitness(individual, params);
end
