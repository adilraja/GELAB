function mean_squared_error=ge_mse(evolved_data, target_data)
%This function computes mean squared error of the data. Written by Muhammad
%Adil Raja, 20th June, 2018. Input: - evolved_data, target_data, Output: -
%mse

data_difference=evolved_data-target_data;
squared_error=power(data_difference, 2);
mean_squared_error=mean(squared_error);