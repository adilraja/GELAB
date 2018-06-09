function data=ge_load_dataset(train_filename, test_filename)
tempData=load(train_filename);
[x, y]=size(tempData);
data.train_x=tempData(:,1:y-1);
data.train_y=tempData(:,y);


if(exist('test_filename', 'var')~=0)
    tempData=load(test_filename);
    [x, y]=size(tempData);
    data.test_x=tempData(:, 1:y-1);
    data.test_y=tempData(:, y);
end

