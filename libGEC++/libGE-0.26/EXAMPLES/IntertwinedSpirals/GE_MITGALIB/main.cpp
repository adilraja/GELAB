// main.cpp -*- C++ -*-
#ifndef _MAIN_CPP_
#define _MAIN_CPP_

#include <iostream>
#include <string>
#include<ga/ga.h>
#include<GE/ge.h>
// Genome definition
#include"GEListGenome.h"

using namespace std;

// Function prototypes
float app_init(unsigned int wrappingEvents,string grammarFile);
float objfunc(GAGenome&);
void initFuncRandom(GAGenome&);
void initFuncSI(GAGenome&);
void print_individual(const GAGenome &g);
int PointMutator(GAGenome&, float);

// Static mapper for initialisation and evaluation of individuals
GEGrammarSI mapper;
// Parameters for Random Initialisation function.
unsigned int minSize=15; // Minimum size for Random Initialisation.
unsigned int maxSize=25; // Minimum size for Random Initialisation.

// Number of Objective function calls
int obj_calls = 0;


int main(int argc, char **argv){
    // Print version of libGE used
    cout << "Using libGE version " << libGEVersion << endl;
    // Parse command-line for options not taken care by GAParameterList
    unsigned int seed=0; // Random seed.
    string grammarFile("grammar.bnf"); // Grammar file.
    unsigned int wrappingEvents=0; // Wrapping events.
    bool sensibleInit=false; // Use Sensible Initialisation.
    float grow=0.5; // Grow rate for Sensible Initialisation.
    unsigned int maxDepth=10; // Maximum tree depth for Sensible Initialisation.
    unsigned int tailSize=0; // Tail size for Sensible Initialisation.
    float tailRatio = 0.0; // Tail ratio for Sensible Initialisation.
    bool effectiveXO=false; // Use Effective Crossover.
    std::string settingsFile; // The GALib settings file.
    for(int ii=1; ii<argc; ii++){
      if(strcmp(argv[ii],"seed")==0){
	seed=atoi(argv[++ii]);
      }
      else if(strcmp(argv[ii],"grammar")==0){
	grammarFile=argv[++ii];
      }
      else if(strcmp(argv[ii],"wrap")==0){
	wrappingEvents=atoi(argv[++ii]);
      }
      else if(strcmp(argv[ii],"sensible")==0){
	sensibleInit=atoi(argv[++ii]);
      }
      else if(strcmp(argv[ii],"min")==0){
	minSize=atoi(argv[++ii]);
      }
      else if(strcmp(argv[ii],"max")==0){
	maxSize=atoi(argv[++ii]);
      }
      else if(strcmp(argv[ii],"grow")==0){
			grow=atof(argv[++ii]);
      }
      else if(strcmp(argv[ii],"maxDepth")==0){
	maxDepth=atoi(argv[++ii]);
      }
      else if(strcmp(argv[ii],"tailSize")==0){
	tailSize=atoi(argv[++ii]);
      }
      else if(strcmp(argv[ii],"tailRatio")==0){
	tailRatio=atof(argv[++ii]);
      }
      else if(strcmp(argv[ii],"effective")==0){
	effectiveXO=atoi(argv[++ii]);
      }
      else if(strcmp(argv[ii],"settings_file")==0){
	settingsFile=(argv[++ii]);
      }
    }

    // Register default values of parameters.
    GAParameterList params;
    GASteadyStateGA::registerDefaultParameters(params);
    params.set(gaNpopulationSize,100); // Population size.
    params.set(gaNnGenerations,10); // Number of generations.
    params.set(gaNpCrossover,0.9); // Probability of crossover.
    params.set(gaNpMutation,0.01); // Probability of mutation.
    params.set(gaNpReplacement,1.0); // Replacement strategy for steady-state GA
    params.set(gaNscoreFrequency,1); // How often to record scores.
    params.set(gaNflushFrequency,1); // How often to dump scores to file.
    params.set(gaNscoreFilename,"is-output.dat"); // Output data file.
    // Grab values from file first.
    if (settingsFile.size() > 0)
    {
      std::cout << "Loading settings file '" << settingsFile 
		<< "'." << std::endl;
      params.read(settingsFile.c_str());
    }
    params.parse(argc,argv,gaFalse); // Parse command line for GAlib args.
    
    // Create genome, and associate the CartCentering objective function.
    //GAListGenome<unsigned char> genome(objfunc);
    GEListGenome genome;
    genome.evaluator(objfunc);
    // Use our initialisation function (initFuncRandom or initFuncSI).
    if(!sensibleInit){
      std::cout << "Using random initialisation." << std::endl;
      genome.initializer(::initFuncRandom);
    }
    else{
      std::cout << "Using sensible initialisation." << std::endl;
      genome.initializer(::initFuncSI);
    }
    // Use the one-point xo from GALib, or our effective version.
    if(!effectiveXO){
      std::cout << "Using one point crossover." << std::endl;
      genome.crossover(GEListGenome::OnePointCrossover);
    }
    else{
      std::cout << "Using effective crossover." << std::endl;
      genome.crossover(GEListGenome::effCrossover);
    }
    //Use our point-mutation.
    genome.mutator(GEListGenome::pointMutator);
    
    //Initialise libGE mapper.
    app_init(wrappingEvents,grammarFile);
    
    // Create GA with a steady-state approach.
    GASteadyStateGA ga(genome);
    // Associate parameters.
    ga.parameters(params);

    // Mapper settings.
    mapper.setGenotypeMaxCodonValue(UCHAR_MAX);
    mapper.setPopSize(ga.populationSize());
    mapper.setGrow(grow);
    mapper.setMaxDepth(maxDepth);
    if(tailSize){
      mapper.setTailSize(tailSize);
    }
    else{
      mapper.setTailRatio(tailRatio);
    }
    
    // Stats settings.
    // Which scores should we track?
    ga.set(gaNselectScores,
	   GAStatistics::AllScores);
    // Stats file.
    ofstream stats("stats");
    
    // Apply all settings to ga, including random seed
    ga.initialize(seed);
    
    //Evolutionary cycle
    while(!ga.done()){
      ga.step();
      cout << ".";
      cout.flush();
      stats << ga.statistics().generation() << "\t"
	    << obj_calls << "\t"
	    << ga.statistics().current(GAStatistics::Maximum) << "\t"
	    << ga.statistics().current(GAStatistics::Mean) << "\t"
	    << ga.statistics().current(GAStatistics::Minimum) << "\n";
    }
    cout << endl;
    //Output statistics
    cout << ga.statistics() << endl;
    //Print best individual
    cout << "Best individual:\n";
    print_individual(ga.statistics().bestIndividual());
    
    return 0;
}

#endif
