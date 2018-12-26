function individual = ge_hybrid(individual, params, train_y)
%function individual = ge_hybrid(individual, params, train_y). This
%function performs hybrid optimization. To this end, it tunes values of
%coefficients of the models produced by GE. Written by Muhammad Adil Raja.
%9th October, 2018

X=params.data.train_x;
T=train_y;
% w=rand(1,params.numCoefs);
str1=char(individual.string);
if(contains(str1, 'w')==0)
    return;%Do nothing as there are no constants in the string (Model).
end
% disp(str1);
fitfunc=['@(w,X,T)mean(power(T-(' str1 '),2))'];
parameterized_objective=str2func(fitfunc);
ObjectiveFunction=@(w)parameterized_objective(w, X, T);
LB=params.LB;
UB=params.UB;
W0=2*UB*rand(1,params.numCoefs)-UB;
switch params.hybridAlgorithm
   case 'sa'
        options = optimoptions('simulannealbnd','Display','off');
        [coefs,cost] = simulannealbnd(ObjectiveFunction,W0, LB, UB, options);
    case 'ga'
        options = optimoptions('ga','Display','off');
        [coefs,cost] = ga(ObjectiveFunction, params.numCoefs, [], [], [], [], LB, UB, options);
    case 'pso'
        options = optimoptions('particleswarm','SwarmSize',100, 'Display', 'off');
        [coefs,cost,exitflag] = particleswarm(ObjectiveFunction,nvars,LB,UB,options);
    case 'lsq'
        options=  optimset('display','off');
        [coefs, cost] = lsqnonlin(ObjectiveFunction,W0,LB,UB, options);
    case 'fminuncqs'
        [x,fval] = fminunc(ObjectiveFunction,W0);
    otherwise
        [coefs,cost] = simulannealbnd(ObjectiveFunction,W0);
end
if(~individual.isEvaluated || cost<individual.fitness)
    individual.constants=coefs;
    individual.fitness=cost;
    w=coefs;
    individual.result=eval(str1);
end

if(length(individual.result)~=length(train_y))
    individual.fitness=params.maxBadFitness;%really bad fitness
    individual.testFitness=params.maxBadFitness;%Really bad testFitness
    individual.result=ones(length(train_y), 1)*params.maxBadFitness;
    %individual.valid=0;
    return;
end


