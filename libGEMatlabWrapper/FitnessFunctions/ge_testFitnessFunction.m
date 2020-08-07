function [fitness1, fitness2, individual]=ge_testFitnessFunction(individual, params, train_y)
%This function is written to test basically whether linear scaling is any
%better than MSE
individual.isEvaluated=0;
individual=ge_mseonly(individual, params, params.data.train_y);
fitness1=individual.fitness;
individual.isEvaluated=0;
individual=ge_evaluate(individual, params, params.data.train_y);
fitness2=individual.fitness;
