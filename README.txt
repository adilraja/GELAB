
Initially a framework for Grammatical Evolution in Java. This is based on the original source code of GE in C++.
Now, GELAB: A Matlab Toolbox for Grammatical Evolution.
Installation: -
In order to install libGEjava on your system, simply clone this repository (or download it).

Once you have done that, you can simply run this software from the Matlab command line. Simply navigate to the libgeGA folder and run ge_main.m. The software should run.

If you make any changes to the java code, please copy the latest version of libGEjava.jar from the dist folder to libGEMatlabWrapper/libGEjar/ folder. Something like the following should work
mv dist/libGEjava.jar libGEMatlabWrapper/libGEjar/libGEjava.jar

You can tweak the java code using Netbeans IDE easily as the code has been built using that. 

For any additional queries please email adilraja@gmail.com


Please cite the following if you wish to use this software in your research.

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
