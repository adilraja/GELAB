#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

#include<ga/ga.h>
#include<GE/ge.h>
#include "GEListGenome.h"

// Use libTCC for evaluation.
#include <libtcc.h>

using namespace std;


// GE mapper, declared in main.cpp
extern GEGrammarSI mapper;


//Buffers for start and end code of the phenotype
static char ISstart[1000];
static char ISend[500];
static char GEfunc[3000];

//Initialises the mapper, and the s-lang interpreter
void app_init(unsigned int wrappingEvents, string grammarFile){

  /* Init GE mapper */
  //Set maximum number of wrapping events per mapping
  mapper.setMaxWraps(wrappingEvents);
  //Load grammar
  if (!mapper.readBNFFile(grammarFile)){
    cerr << "Could not read "<< grammarFile << "\n";
    cerr << "Execution aborted.\n";
    exit(0);
  }

  //Set maximum number of wrapping events per mapping
  mapper.setMaxWraps(wrappingEvents);
  //Load grammar
  if (!mapper.readBNFFile(grammarFile)){
    cerr << "Could not read grammar.bnf\n";
    cerr << "Execution aborted.\n";
    exit(0);
  }

  /* Read code start and end files */
  char buffer[1000];
  FILE *c_code;

  strcpy(ISstart,"");
  if(!(c_code=fopen("spiralstart.c","r"))){
    cerr << "Could not read cartcenterstart.c\n";
    cerr << "Execution aborted.\n";
    exit(0);
  }
  while(fgets(buffer,1000,c_code))
    strcat(ISstart,buffer);
  fclose(c_code);

  strcpy(ISend,"");
  if(!(c_code=fopen("spiralend.c","r"))){
    cerr << "Could not read cartcenterend.c\n";
    cerr << "Execution aborted.\n";
    exit(0);
  }
  while(fgets(buffer,1000,c_code))
    strcat(ISend,buffer);
  fclose(c_code);    

  /* Load the GECart.c functions file. */
  if(!(c_code=fopen("GEspiral.c","r"))){
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
  GEListGenome &genome = static_cast<GEListGenome&>(g);
  //Assign genotype to mapper
  mapper.setGenotype(genome);
  //Grab phenotype
  Phenotype const *phenotype=mapper.getPhenotype();
  if(phenotype->getValid()){
    int fitness;

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
	      "Error in GEspiral.c TCC string compilation!, Exiting!\n");
      exit(-1);
    }

    string buffer;
    //Write start code to buffer
    buffer = ISstart;
    //Write phenotype code to buffer
    buffer += phenotype->getString();
    //Write end code to buffer
    buffer += ISend;

    // Compile the buffer.
    if (tcc_compile_string(tcc_state, buffer.c_str()) != 0) {
      fprintf(stderr, "Error in phenotype TCC compilation!, Exiting!\n");
      exit(-1);
    }
					
    if (tcc_relocate(tcc_state) != 0) {
      fprintf(stderr, "Error tcc_relocate failed, Exiting!\n");
      exit(-1);
    }
					
    // Get pointer to the main function symbol.
    unsigned long val;
    int (*p_tccMainFunc)();
    if (tcc_get_symbol(tcc_state, &val, "main") == -1) {
      fprintf(stderr, "Error: could not tcc_get_symbol main, Exiting");
      exit(-1);
    }
				
    // Execute the main function.
    p_tccMainFunc = (int (*)())val;
    p_tccMainFunc();
					
    // Get the fitness function symbol.
    int (*p_tccFitnessFunc)();
    if (tcc_get_symbol(tcc_state, &val, "AssignFitness") == -1) {
      fprintf(stderr, "Error: could not tcc_get_symbol AssignFitness, Exiting");
      exit(-1);
    }
    // Execute the AssignFitness function.
    p_tccFitnessFunc = (int (*)())val;
    fitness = p_tccFitnessFunc();

    // Delete the tcc state.
    tcc_delete(tcc_state);

    if(isinf(fitness) || isnan(fitness) || !isfinite(fitness))
      fitness = 0;

    // cout << *phenotype << " (" << fitness << ")\n"; 

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
  cout << "Best individual:\n";
  //Print phenotype
  cout << *(mapper.getPhenotype());
  cout << endl;
  cout << "Genotype = " << *mapper.getGenotype() << "\n";
  cout << "Total length     = " << mapper.getGenotype()->size() << "\n";
  cout << "Effective length = " << mapper.getGenotype()->getEffectiveSize() << "\n";
  cout << "Wrapping events = " << mapper.getGenotype()->getWraps() << "\n";
}


