
function individual = ge_hybrid(individual, params, train_y, hybridAlgorithm)
%function individual = ge_hybrid(individual, params, train_y). This
%function performs hybrid optimization. To this end, it tunes values of
%coefficients of the models produced by GE. Written by Muhammad Adil Raja.
%9th October, 2018

if(~individual.improvable)
    return;% The individual is not improvable, so lets go back.
end

X=params.data.train_x;
T=train_y;
% w=rand(1,params.numCoefs);
str1=char(individual.string);
if(contains(str1, 'w')==0)
    return;%Do nothing as there are no constants in the string (Model).
end

slope=num2str(individual.slope);
intercept=num2str(individual.intercept);

str2=strcat(slope, '.*(', str1, ')+', intercept);
% disp(str1);
fitfunc=['@(w,X,T, mT2)mean(power(T-(' str2 '),2))'];
parameterized_objective=str2func(fitfunc);
ObjectiveFunction=@(w)parameterized_objective(w, X, T);
LB=params.LB;
UB=params.UB;
W0=2*UB*rand(1,params.numCoefs)-UB;
cost=params.maxBadFitness;

if(nargin<4)
    hybridAlgorithm=params.hybridAlgorithm;
    W0=individual.constants;
end

switch hybridAlgorithm
    case 'sa'
        options = optimoptions('simulannealbnd','Display','off', 'MaxTime', 60);
        LB=ones(1, params.numCoefs).*params.LB;
        UB=ones(1, params.numCoefs).*params.UB;
        [coefs,cost, exitflag] = simulannealbnd(ObjectiveFunction,W0, LB, UB, options);
        if(exitflag==-5)%Computation time infeasible
%             individual.isEvaluated=1;
            individual.improvable=0;%The individual is either not improvable, or it is difficult to improve it. So it will not be optimized again.
        end
    case 'ga'
        options = optimoptions('ga','Display','off', 'MaxTime', 60);
        LB=ones(1, params.numCoefs).*params.LB;
        UB=ones(1, params.numCoefs).*params.UB;
        [coefs,cost, exitflag] = ga(ObjectiveFunction, params.numCoefs, [], [], [], [], LB, UB, [], options);
        if(exitflag==-4 || exitflag==5)%Computation time infeasible
%             individual.isEvaluated=1;
            individual.improvable=0;%The individual is either not improvable, or it is difficult to improve it. So it will not be optimized again.
        end
    case 'pso'
        options = optimoptions('particleswarm','SwarmSize',100, 'Display', 'off', 'MaxTime', 60);
        [coefs,cost,exitflag] = particleswarm(ObjectiveFunction, params.numCoefs,LB,UB,options);
        if(exitflag==-5)%Computation time infeasible
%             individual.isEvaluated=1;
            individual.improvable=0;%The individual is either not improvable, or it is difficult to improve it. So it will not be optimized again.
        end
    case 'lsq'
        options=  optimset('Display','off');
        LB=ones(1, params.numCoefs).*params.LB;
        UB=ones(1, params.numCoefs).*params.UB;
        
        [coefs, cost] = lsqnonlin(ObjectiveFunction,W0,LB,UB, options);
    case 'fminuncqs'
        [x,fval] = fminunc(ObjectiveFunction,W0);
    otherwise
        [coefs,cost] = simulannealbnd(ObjectiveFunction,W0);
end
if(cost<individual.fitness)
    individual.constants=coefs;
    individual.fitness=cost;
    w=coefs;
    individual.result=eval(str1);
    individual.isEvaluated=0;
    individual.improvable=1;%The individual is improvable so it can be re-evaluated again (in a subsequent generation)
else
%     individual.isEvaluated=1;
    individual.improvable=0;%The individual is either not improvable, or it is difficult to improve it. So it will not be optimized again.
end


if(length(individual.result)~=length(train_y))
    individual.fitness=params.maxBadFitness;%really bad fitness
    individual.testFitness=params.maxBadFitness;%Really bad testFitness
    individual.result=ones(length(train_y), 1)*params.maxBadFitness;
    %individual.valid=0;
    return;
end


