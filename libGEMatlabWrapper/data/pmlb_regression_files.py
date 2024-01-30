from pmlb import fetch_data, regression_dataset_names


f=open("pmlb_regression_files.txt", "w")

for regression_dataset in regression_dataset_names:
    f.write(regression_dataset + "\n")
f.close()
