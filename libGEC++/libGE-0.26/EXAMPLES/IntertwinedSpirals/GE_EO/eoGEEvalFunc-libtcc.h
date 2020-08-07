#ifndef _eoGEEvalFunc_h
#define _eoGEEvalFunc_h

// include the base definition of eoEvalFunc
#include "eoEvalFunc.h"

#include <cmath>

#include<GE/ge.h>

// Use libTCC for evaluation
#include<libtcc.h>


// GE mapper.
extern GEGrammarSI mapper;

template <class EOT>
class eoGEEvalFunc : public eoEvalFunc<EOT>{
 public:
  eoGEEvalFunc(GEGrammar &mapper, string grammarFile, unsigned int wrappingEvents)
    {
      //Set maximum number of wrapping events per mapping
      mapper.setMaxWraps(wrappingEvents);
      if (!mapper.readBNFFile(grammarFile))
	{
	  cerr << "Could not read " << grammarFile << "\n";
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
  void operator()(EOT & _eo)
  {
    //	  FILE *file;
    // test for invalid to avoid recomputing fitness
    // of unmodified individuals
    if (_eo.invalid())
      {
	int fitness=0;
	//Create new (valid) genotype
	int genome[_eo.size()];
	for(unsigned int ii=0;ii<_eo.size();ii++)
	  {
	    genome[ii]=_eo[ii];
	  }
	Genotype genotype(genome,_eo.size());
	//Assign genotype to mapper
	mapper.setGenotype(genotype);
	//Grab phenotype
	Phenotype const *phenotype=mapper.getPhenotype();
	_eo.setEffectiveSize(mapper.getGenotype()->getEffectiveSize());
	if(phenotype->getValid())
	  {
	    /* create tcc state */
	    TCCState *tcc_state = tcc_new();
	    if (!tcc_state) {
	      cerr << "Could not create tcc state\n";
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
	  }
	_eo.fitness(fitness);
      }
  }
 private:
  string buffer;
  char ISstart[3000];
  char ISend[3000];
  char GEfunc[3000];
};

#endif

