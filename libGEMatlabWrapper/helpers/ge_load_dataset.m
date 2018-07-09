function data=ge_load_dataset(trainx_filename, trainy_filename, testx_filename, testy_filename)
tempData=load(trainx_filename);
data.test=0;
data.train_x=tempData;
tempData=load(trainy_filename);
data.train_y=tempData;
[trxr trxc]=size(data.train_x);
[tryr tryc]=size(data.train_y);

if(trxr~=tryr)
   disp('The number of input/output instances in training data is not equal:');
   return;
end


if(exist('testx_filename', 'var')~=0)
    tempData=load(testx_filename);
    data.test_x=tempData;
    tempData=load(testy_filename);
    data.test_y=tempData;
    [texr texc]=size(data.test_x);
    [teyr teyc]=size(data.test_y);
    if(texr~=teyr)
        disp('The number of input/output instances in test data is not equal:');
        return;
    end
    if(trxc~=texc)
        disp('The number of features in training and testing data is not equal:'); 
        return;
    end
    data.test=1;
end

