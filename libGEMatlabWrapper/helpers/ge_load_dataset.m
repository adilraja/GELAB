function data=ge_load_dataset(trainx_filename, trainy_filename, testx_filename, testy_filename)
tempData=load(trainx_filename);
data.train_x=tempData;
tempData=load(trainy_filename);
data.train_y=tempData;


if(exist('testx_filename', 'var')~=0)
    tempData=load(testx_filename);
    data.test_x=tempData;
    tempData=load(testy_filename);
    data.test_y=tempData;
end

