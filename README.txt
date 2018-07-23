
Initially a framework for Grammatical Evolution in Java. This is based on the original source code of GE in C++.
Now, GELAB: A Matlab Toolbox for Grammatical Evolution.
Installation: -
In order to install libGEjava on your system, simply clone this repository (or download it).

Running This Software: -

Once you have done that, you can simply run this software from the Matlab command line. Simply navigate to the libgeGA folder and run ge_main.m. The software should run.

In order to run a full-fledged experiment, simply run: 

>>load('srparallelparams.mat', 'params');
>> [all_pops, all_bests, all_stats, params]=ge_inaloop(params);

Or simply:

>> [all_pops, all_bests, all_stats, params]=ge_inaloop;


If you are a lazy guy just like myself, you can copy your training and test data to the following files and run the whole thing for your own problem. trainingDataX.txt, trainingDataY.txt, testDataX.txt, testDataX.txt.

The software has been tested thorougly for symbolic regression. However, you can modify it to work for your own version of the problem. A few tweaks here and there would do. The only prerequisite is a bit of know how about how EAs (evolutionary algorithms) work.

If you make any changes to the java code, please copy the latest version of libGEjava.jar from the dist folder to libGEMatlabWrapper/libGEjar/ folder. Something like the following should work
mv dist/libGEjava.jar libGEMatlabWrapper/libGEjar/libGEjava.jar

You can tweak the java code using Netbeans IDE easily as the code has been built using that. 

For any additional queries please email adilraja@gmail.com | conor.ryan@ul.ie


Please feel free to use this software in your research. Once you get your work published using this, please let us know. We shall cite your work. We are working on a mega article about this software and we would love to cite you.

In the meanwhile, please cite the following if you wish to use this software in your research.

O'Neill, Michael, and Conor Ryan. "Grammatical evolution." IEEE Transactions on Evolutionary Computation 5, no. 4 (2001): 349-358.

@article{o2001grammatical,
  title={Grammatical evolution},
  author={O'Neill, Michael and Ryan, Conor},
  journal={IEEE Transactions on Evolutionary Computation},
  volume={5},
  number={4},
  pages={349--358},
  year={2001},
  publisher={IEEE}
}
