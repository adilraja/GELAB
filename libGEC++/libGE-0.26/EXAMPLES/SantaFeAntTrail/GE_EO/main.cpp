// main.cpp -*- C++ -*-
#ifndef _MAIN_CPP_
#define _MAIN_CPP_
#include <iostream>

using namespace std;

// eo general include
#include "eo"
#include "eoReduceMergeReduce.h" // Not included on main eo include file

/** definition of representation **/
#include "eoGE.h"

/** definition of initilisation **/
#include "eoGEInit.h"
/** definition of evaluation **/
//#include "eoGEEvalFunc.h"
/** definition of operators **/
#include "eoGEQuadCrossover.h"
#include "eoGEMutation.h"

// Fitness Type (eoMinimizingFitness if you are minimizing)
typedef eoMaximizingFitness MyFitT;

// EO Objects
typedef eoGE<MyFitT> Indi;

/** libGE **/
#include<GE/ge.h>
GEGrammarSI mapper;

void main_function(int argc, char **argv){
	// PARSER (for command-line arguments)
	eoParser parser(argc, argv);

	// -- Random Seed --
	long int seed = parser.createParam(time(0),"seed","Random number seed",'R',"Random Number Generation").value();
	// - Grammar File --
	string grammarFile = parser.createParam(static_cast<string>("grammar.bnf"),"grammarFile","Grammar file",'g',"Mapping Process").value();
	// --- Wrapping ----
	unsigned int wrappingEvents = parser.createParam(static_cast<unsigned int>(0),"wrappingEvents","Number of wrapping events",'w',"Mapping Process").value();
	// --- Pop Size ----
	unsigned int popSize = parser.createParam(static_cast<unsigned int>(100),"popSize","Population size",'P',"Search Engine").value();
	// -- Generations --
	unsigned int maxGen = parser.createParam(static_cast<unsigned int>(10),"maxGen","Maximum number of generations",'G',"Stopping Criterion").value();
	// -- Crossover % --
	float pCross = parser.createParam(static_cast<float>(0.9),"pCross","Probability of Crossover",'C',"Genetic Operators").value();
	// - Eff Crossover -
	bool effCross = parser.createParam(static_cast<bool>(false),"effCross","Use Effective Crossover",'E',"Genetic Operators").value();
	// -- Mutation % ---
	float pMut = parser.createParam(static_cast<float>(1.0),"pMut","Probability of Mutation",'M',"Genetic Operators").value();
	float pMutPerBit = parser.createParam(static_cast<float>(0.01),"pMutPerBit","Probability of bit-flip Mutation",'b',"Genetic Operators").value();
	// --- SI or rnd ---
	bool sensibleInit = parser.createParam(static_cast<bool>(false),"sensibleInit","Use Sensible Initialisation",'s',"Initialisation").value();
	// - rnd::minSize --
	unsigned int minSize = parser.createParam(static_cast<unsigned int>(15),"minSize","Minimum size for random initialisation",'x',"Initialisation").value();
	// - rnd::maxSize --
	unsigned int maxSize = parser.createParam(static_cast<unsigned int>(25),"maxSize","Maximum size for random initialisation",'X',"Initialisation").value();
	// --- SI::grow ----
	float grow = parser.createParam(static_cast<float>(0.5),"grow","Grow ratio for SI",'r',"Initialisation").value();
	// --- SI::depth ---
	unsigned int maxDepth = parser.createParam(static_cast<unsigned int>(10),"maxDepth","Maximum depth for SI",'d',"Initialisation").value();
	// - SI::tailSize --
	unsigned int tailSize = parser.createParam(static_cast<unsigned int>(0),"tailSize","Tail size for SI",'T',"Initialisation").value();
	// - SI::tailRatio -
	float tailRatio = parser.createParam(static_cast<float>(0.0),"tailRatio","Tail ratio for SI",'t',"Initialisation").value();
	// --- Save File ---
	string loadName = parser.createParam(static_cast<string>(""),"Load","Save file to restart run",'L',"Persistence").value();
	// -- Params File --
	string strStatus = parser.createParam(static_cast<string>(parser.ProgramName()+".status"),"Status","Status file",'S',"Persistence").value();
	// Parser related code
	if(parser.userNeedsHelp()){// Print help and quit
		parser.printHelp(cout);
		exit(1);
	}
	if(strStatus!=""){// Print params into params file
		ofstream os(strStatus.c_str());
		os << parser;
	}

	// Mapper setting
	mapper.setGenotypeMaxCodonValue(UCHAR_MAX);

	// FITNESS function
	eoGEEvalFunc<Indi> objfunc(mapper,grammarFile,wrappingEvents);
	eoEvalFuncCounter<Indi> eval(objfunc);

	// POPULATION
	eoPop<Indi> pop;

	// STATE
	// Create state for reading
	eoState inState;
	// Register rng (global variable) and pop in state, so they can be
	// loaded from save file if required
	inState.registerObject(rng);
	inState.registerObject(pop);
	// Check if run is a continuation of previous run
	if(loadName!=""){// Yes
		inState.load(loadName); // load rng and pop
	}
	else{// No
		// Initialiser
		rng.reseed(seed);
		eoGEInit<Indi> init(mapper,seed,minSize,maxSize,sensibleInit,popSize,grow,maxDepth,tailSize,tailRatio);

		// Fill population
		for(unsigned int igeno=0;igeno<popSize;igeno++){
			Indi v;// void individual, to be filled
			init(v);// Call initialiser
			pop.push_back(v);//put it in the population
		}
		// Evaluate population in one go
		apply<Indi>(eval, pop);
	}
	// SELECTION AND REPLACEMENT
	// Use Roulette-wheel selection
	eoProportionalSelect<Indi> selectRoulette;
	eoSelectPerc<Indi> select(selectRoulette);
	// Steady-state
	eoSSGAWorseReplacement<Indi> replace;
	//eoTruncate<Indi> reduce;
	//eoPlus<Indi> merge;
	//eoReduceMerge<Indi> reduce;
	eoPlusReplacement<Indi> plusReplacement;
	//eoTruncate<Indi> reduce;
	//eoReduceMergeReduce<Indi> reduceMergeReduce(eoHowMany(0),false,eoHowMany(popSize),reduce,eoHowMany(popSize),reduce,reduce);

	// OPERATORS
	// 1-point crossover
	eoGEQuadCrossover<Indi> xover(effCross);
	// bit-flip mutation
	eoGEMutation<Indi>  mutation(pMutPerBit);
	// Encapsulate operators into eoTransform object
	eoSGATransform<Indi> transform(xover, pCross, mutation, pMut);

	// CONTINUATOR - called after each generation
	// Stop when maxGen generations are reached
	eoGenContinue<Indi> genCont(maxGen);
	eoCombinedContinue<Indi> continuator(genCont);
	// Wrap continuator with checkpoint
	//eoCheckPoint<Indi> checkpoint(continuator);
	eoCheckPoint<Indi> checkpoint(genCont);
	// -- Generation counter and Incrementor --
	eoValueParam<unsigned int> generationCounter(0,"Gen.");
	eoIncrementor<unsigned int> increment(generationCounter.value());
	checkpoint.add(increment);
	// -- Statistics --
	eoBestFitnessStat<Indi> bestStat;
	eoSecondMomentStats<Indi> secondStat; // mean and stddev
	eoAverageStat<Indi> meanStat; // mean and stddev
	eoNthElementFitnessStat<Indi> worstStat(popSize-1); // mean and stddev
	checkpoint.add(bestStat);
	checkpoint.add(secondStat);
	checkpoint.add(meanStat);
	checkpoint.add(worstStat);
	// -- STDOUT monitor --
	eoStdoutMonitor monitor(false);
	monitor.add(generationCounter);
	monitor.add(eval);// Counter of objfunc calls
	monitor.add(bestStat);
	monitor.add(secondStat);
	checkpoint.add(monitor);
	// -- File monitor --
	eoFileMonitor fileMonitor("stats.xg","\t");
	fileMonitor.add(generationCounter);
	fileMonitor.add(eval);// Counter of objfunc calls
	fileMonitor.add(bestStat);
	fileMonitor.add(meanStat);
	fileMonitor.add(worstStat);
	checkpoint.add(fileMonitor);
	// -- State saver --
	eoState outState;
	outState.registerObject(parser);
	outState.registerObject(pop);
	outState.registerObject(rng);
	// Save every 10 generations
	eoCountedStateSaver stateSaver(10,outState,"generation");
	checkpoint.add(stateSaver);
  
	// ALGORITHM
	eoEasyEA<Indi> gga(checkpoint, eval, select, transform, plusReplacement);
	// Apply it to population
	gga(pop);
	// Print out best individual
	pop.sort();
	pop[0].invalidate();
	eval(pop[0]);
	cout << "Best individual\n";
	cout << *(mapper.getPhenotype()) << endl;// Print phenotype
	
}

int main(int argc, char* argv[]){
	try{
		main_function(argc,argv);
	}
	catch(exception& e){
        	cout << "Exception: " << e.what() << '\n';
	}
	return 0;
}

#endif

