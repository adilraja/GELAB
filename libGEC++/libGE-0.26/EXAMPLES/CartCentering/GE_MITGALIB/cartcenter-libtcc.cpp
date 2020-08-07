#ifndef _CARTCENTER_GCC_CPP_
#define _CARTCENTER_GCC_CPP_

#include<cstdio>
#include<cstdlib>
#include<cstring>

#include<ga/ga.h>
#include<GE/ge.h>
#include "GEListGenome.h"

// Use libTCC for evaluation.
#include <libtcc.h>

using namespace std;

typedef double Real;

// GE mapper, declared in main.cpp
extern GEGrammarSI mapper;

// Numer of Objective function calls, declared in main.cpp
extern int obj_calls;

//Buffers for start and end code of the phenotype
static char CCstart[1000];
static char CCend[500];
static char GEfunc[3000];
static char buffer[7000];


//Loads the start and end code required to compile phenotypes,
//and initialises the mapper
void app_init(unsigned int wrappingEvents,string grammarFile){
	FILE *c_code;

	/* Init GE mapper */
	//Set maximum number of wrapping events per mapping
	mapper.setMaxWraps(wrappingEvents);
	//Load grammar
	if (!mapper.readBNFFile(grammarFile)){
		cerr << "Could not read grammar.bnf\n";
		cerr << "Execution aborted.\n";
		exit(0);
	}

	/* Read buffer code files */
	strcpy(CCstart,"");
	if(!(c_code=fopen("cartcenterstart.c","r"))){
		cerr << "Could not read cartcenterstart.c\n";
		cerr << "Execution aborted.\n";
		exit(0);
	}
	while(fgets(buffer,1000,c_code))
		strcat(CCstart,buffer);
	fclose(c_code);

	strcpy(CCend,"");
	if(!(c_code=fopen("cartcenterend.c","r"))){
		cerr << "Could not read cartcenterend.c\n";
		cerr << "Execution aborted.\n";
		exit(0);
	}
	while(fgets(buffer,1000,c_code))
		strcat(CCend,buffer);
	fclose(c_code);

	/* Load the GECart.c functions file. */
	if(!(c_code=fopen("GEcart.c","r"))){
		cerr << "Could not read GEcart.c\n";
		cerr << "Execution aborted.\n";
		exit(0);
	}
	while(fgets(buffer,1000,c_code))
	  strcat(GEfunc,buffer);
	fclose(c_code);
}

//Attributes a fitness score to a genome
float objfunc(GAGenome &g){
	obj_calls++;
	
	// string buffer;
	GEListGenome &genome = static_cast<GEListGenome&>(g);
	//Assign genotype to mapper
	mapper.setGenotype(genome);
	//Grab phenotype
        Phenotype const *phenotype=mapper.getPhenotype();
	if(phenotype->getValid()){
	  Real fitness = 0.0;

	  /* create tcc state */
	  TCCState *tcc_state = tcc_new();
	  if (!tcc_state) {
	    fprintf(stderr, "Could not create tcc state\n");
	    exit(1);
	  }
	  tcc_set_output_type(tcc_state, TCC_OUTPUT_MEMORY);

	  /* add the math library */
	  tcc_add_library(tcc_state, "m");

	  /* Compile the GE functions in the tcc state */
	  if (tcc_compile_string(tcc_state, GEfunc) != 0) {
	    fprintf(stderr, 
		    "Error in GEcart.c TCC string compilation!, Exiting!\n");
	    exit(-1);
	  }

	  //Write start code to buffer
	  strcpy(buffer, CCstart);
	  //Write phenotype code to buffer
	  strcat(buffer, phenotype->getString().c_str());
	  //Write end code to buffer
	  strcat(buffer, CCend);

	  // Compile the buffer.
	  if (tcc_compile_string(tcc_state, buffer) != 0) {
	    fprintf(stderr, "Error in phenotype TCC compilation!, Exiting!\n");
	    exit(-1);
	  }

	  if (tcc_relocate(tcc_state) != 0) {
	    fprintf(stderr, "Error tcc_relocate failed, Exiting!\n");
	    exit(-1);
	  }

	  // Get the main() function symbol.
	  unsigned long val;
	  if (tcc_get_symbol(tcc_state, &val, "main") == -1) {
	    fprintf(stderr, "Error: could not tcc_get_symbol main, Exiting");
	    exit(-1);
	  }

	  // Execute the main function.
	  int (*p_tccMainFunc)();
	  p_tccMainFunc = (int (*)())val;
	  p_tccMainFunc();

	  // Get the sumFitCaseTimes variable symbol.
	  if (tcc_get_symbol(tcc_state, &val, "sumFitCaseTimes") == -1) {
	    fprintf(stderr, "Error: could not tcc_get_symbol sumFitCaseTimes, Exiting");
	    exit(-1);
	  }
	  Real* p_tccFitness = (Real*)val;
	  fitness = *p_tccFitness;

	  // Delete the tcc state.
	  tcc_delete(tcc_state);
	  tcc_state = 0;

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
