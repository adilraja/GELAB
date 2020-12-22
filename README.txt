
Initially a framework for Grammatical Evolution in Java. This is based on the original source code of GE in C++.
Now, GELAB: A Matlab Toolbox for Grammatical Evolution.
Installation: -
In order to install libGEjava on your system, simply clone this repository (or download it).

Running This Software: -

Add the folder "GELAB/libGEMatlabWrapper", and all of its sub-folders, to your Matlab path.

Once you have done that, you can simply run this software from the Matlab command line. Simply (navigate to the libgeGA folder and) run ge_main.m. The software should run.

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


@InProceedings{gelab,
author="Raja, Muhammad Adil
and Ryan, Conor",
editor="Yin, Hujun
and Camacho, David
and Novais, Paulo
and Tall{\'o}n-Ballesteros, Antonio J.",
title="GELAB - A Matlab Toolbox for Grammatical Evolution",
booktitle="Intelligent Data Engineering and Automated Learning -- IDEAL 2018",
year="2018",
publisher="Springer International Publishing",
address="Cham",
pages="191--200",
abstract="In this paper, we present a Matlab version of libGE. libGE is a famous library for Grammatical Evolution (GE). GE was proposed initially in [1] as a tool for automatic programming. Ever since then, GE has been widely successful in innovation and producing human-competitive results for various types of problems. However, its implementation in C++ (libGE) was somewhat prohibitive for a wider range of scientists and engineers. libGE requires several tweaks and integrations before it can be used by anyone. For anybody who does not have a background in computer science, its usage could be a bottleneck. This prompted us to find a way to bring it to Matlab. Matlab, as it is widely known, is a fourth generation programming language used for numerical computing. Details aside, but it is well known for its user-friendliness in the wider research community. By bringing GE to Matlab, we hope that many researchers across the world shall be able to use it, despite their academic background. We call our implementation of GE as GELAB. GELAB is currently present online as an open-source software (https://github.com/adilraja/GELAB). It can be readily used in research and development.",
isbn="978-3-030-03496-2"
}

If you have used GELAB with hybrid optimization turned on, please cite the following paper:

@inproceedings{raja2020gelab,
  title={GELAB and Hybrid Optimization Using Grammatical Evolution},
  author={Raja, Muhammad Adil and Murphy, Aidan and Ryan, Conor},
  booktitle={International Conference on Intelligent Data Engineering and Automated Learning},
  pages={292--303},
  year={2020},
  organization={Springer}
}

