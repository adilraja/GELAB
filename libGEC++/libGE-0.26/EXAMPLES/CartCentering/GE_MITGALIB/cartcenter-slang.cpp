// cartcenter-slang.cpp -*- C++ -*-
#ifndef _CARTCENTER_SLANG_CPP_
#define _CARTCENTER_SLANG_CPP_

#include<cstdio>
#include<cstdlib>
#include<cstring>

#include<ga/ga.h>
#include<GE/ge.h>
#include"GEListGenome.h"
#include<slang/slang.h>

using namespace std;

typedef double Real;

// GE mapper, declared in main.cpp
extern GEGrammarSI mapper;

// Numer of Objective function calls, declared in main.cpp
extern int obj_calls;

// Fitness value (NOTE: the type of Real must match the type
// specified in the call to SLadd_intrinsic_variable below.
Real fitness;

//Initialises the mapper, and the s-lang interpreter
void app_init(unsigned int wrappingEvents,string grammarFile){
	/* Init GE mapper */
	//Set maximum number of wrapping events per mapping
	mapper.setMaxWraps(wrappingEvents);
	//Load grammar
	if (!mapper.readBNFFile(grammarFile)){
		cerr << "Could not read grammar.bnf\n";
		cerr << "Execution aborted.\n";
		exit(0);
	}
	/* Init S-lang interface */
	if ((-1 == SLang_init_slang ()) /* basic interpreter functions */
	    || (-1 == SLang_init_stdio ()) /* stdio file I/O */
	    || (-1 == SLang_init_slmath())) { /* math functions */
	        exit(EXIT_FAILURE);
	}

	if (-1 == SLang_load_file ("GEcart.sl")){
		SLang_restart(1);
		SLang_set_error(0);
	}

	// Create interface between fitness and Fitness_Variable.
	if (-1==SLadd_intrinsic_variable("Total_Time",
				   &(fitness),SLANG_DOUBLE_TYPE, 0)){
	  exit(EXIT_FAILURE);
	}
}

//Attributes a fitness score to a genome
float objfunc(GAGenome &g){
	obj_calls++;
	string buffer;
	GEListGenome &genome = static_cast<GEListGenome&>(g);
	//Assign genotype to mapper
	mapper.setGenotype(genome);
	//Grab phenotype
        Phenotype const *phenotype=mapper.getPhenotype();

	fitness = 0.0;
	if(phenotype->getValid()){

		//Write start code to buffer
		buffer="initCart(); resetCart(); while(currFitCase < numFitCase) { if (";
		//Write phenotype code to buffer
		buffer+=phenotype->getString();
		//Write end code to buffer
		buffer+=" > 0.0) { velocityChange = posForceVelChange; } else { velocityChange = negForceVelChange; } stepSim(); } Total_Time=sumFitCaseTimes;";

		//Load and interpret buffer
		if (-1==SLang_load_string(const_cast<char*>(buffer.c_str()))){
			SLang_restart(1);
			SLang_set_error(0);
			}

		// Invert fitness because GA's maximise fitness.
		if (fitness != 0.0)
		{
		  fitness = 1.0 / fitness;
		}

		// Set effective size of genome
		genome.setEffectiveSize(mapper.getGenotype()->getEffectiveSize());

		return fitness;
	}
	return 0;
}

//Print an individual to stdout
void print_individual(const GAGenome &g){
	GAListGenome<unsigned char> &genome =
		(GAListGenome<unsigned char> &) g;
	//Assign genotype to mapper
	mapper.setGenotype(genome);
	//Print phenotype
	cout << *(mapper.getPhenotype());
	cout << endl;
	cout << "Genotype = " << *mapper.getGenotype() << "\n";
	cout << "Total length     = "
		<< mapper.getGenotype()->size() << "\n";
	cout << "Effective length = "
		<< mapper.getGenotype()->getEffectiveSize() << "\n";
	cout << "Wrapping events = "
		<< mapper.getGenotype()->getWraps() << "\n";
}

#endif
