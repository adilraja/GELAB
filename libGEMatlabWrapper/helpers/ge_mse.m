function mse=ge_mse(d1, d2)
%This function computes mean squared error of the data.

diff_vec=d1-d2;
sq_vec=diff_vec.^2;
mse=sum(sq_vec);