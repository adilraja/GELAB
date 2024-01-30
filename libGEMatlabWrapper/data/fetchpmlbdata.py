#from sklearn.linear_model import LogisticRegression
#from sklearn.naive_bayes import GaussianNB
from sklearn.model_selection import train_test_split
import csv
import matlab.engine


#import matplotlib.pyplot as plt
#import seaborn as sb

from pmlb import fetch_data, regression_dataset_names

logit_test_scores = []
gnb_test_scores = []
eng = matlab.engine.start_matlab()


for regression_dataset in regression_dataset_names:
	print(regression_dataset)
	X, y = fetch_data(regression_dataset, return_X_y=True)
	train_X, test_X, train_y, test_y = train_test_split(X, y)
	with open(regression_dataset + '_train_x.csv' , 'w') as trainxFile:
    		writer = csv.writer(trainxFile, delimiter=',')
    		writer.writerows(train_X)

		print("writing completed")

		trainxFile.close()
	list_data = train_y.tolist() 
	matlab_data = matlab.double(list_data) 

	str=eng.strcat(regression_dataset, '_train_y.csv')
	eng.dlmwrite(str, matlab_data, nargout=0)
	with open(regression_dataset + '_test_x.csv' , 'w') as testxFile:
    		writer = csv.writer(testxFile, delimiter=',')
    		writer.writerows(test_X)

		print("writing completed")

		testxFile.close()
	list_data = test_y.tolist() 
	matlab_data = matlab.double(list_data) 

	str=eng.strcat(regression_dataset, '_test_y.csv')
	eng.dlmwrite(str, matlab_data, nargout=0)
