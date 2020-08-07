// santafe-slang.cpp -*- C++ -*-
#ifndef _SANTAFE_SLANG_CPP_
#define _SANTAFE_SLANG_CPP_

#include<cstdio>
#include<cstdlib>
#include<cstring>

#include<ga/ga.h>
#include<GE/ge.h>
#include<slang/slang.h>
#include"GEListGenome.h"

using namespace std;

// GE mapper, declared in main.cpp
extern GEGrammarSI mapper;

// Numer of Objective function calls, declared in main.cpp
extern int obj_calls;

// Fitness value;
int fitness;

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
		|| (-1 == SLang_init_stdio ())){ /* stdio file I/O */
		cerr << "Could not init S-Lang interface.\n";
		cerr << "Execution aborted.\n";
		exit(0);
	}

	if (-1 == SLang_load_file ("GEant.sl")){
		cerr << "Could not read GEant.sl\n";
		cerr << "Execution aborted.\n";
		exit(0);
	}
	if (-1 == SLang_load_file ("GEtrail.sl")){
		cerr << "Could not read GEtrail.sl\n";
		cerr << "Execution aborted.\n";
		exit(0);
	}
	if (-1 == SLang_load_string ("ReadTrailGEtrail(\"santafe.trl\");")){
		cerr << "Could not execute code within the S-Lang interpreter.\n";
		cerr << "Execution aborted.\n";
		exit(0);
	}
	//Create interface between fitness and Fitness_Variable
	if (-1==SLadd_intrinsic_variable("Fitness_Variable",
			&(fitness),SLANG_INT_TYPE, 0)){
		cerr << "Could not interface variable with S-Lang interpreter.\n";
		cerr << "Execution aborted.\n";
		exit(0);
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
	if(phenotype->getValid()){
		// Write start code to buffer.
		buffer="initGEtrail();resetGEtrail(615);while(_energy > 0){";
		// Write phenotype code to buffer.
		buffer+=phenotype->getString();
		// Write end code to buffer.
		buffer+="}\nFitness_Variable=_picked_up;";
		// Load and interpret buffer.
		if (-1==SLang_load_string(const_cast<char*>(buffer.c_str()))){
			SLang_restart(1);
			SLang_set_error(0);
			fitness=0;
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

