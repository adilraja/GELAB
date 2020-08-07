#ifndef _eoGEEvalFunc_h
#define _eoGEEvalFunc_h

// include the base definition of eoEvalFunc
#include "eoEvalFunc.h"

#include <cmath>

#include<GE/ge.h>

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

	    //Create output file
	    FILE *file;
	    if(!(file=fopen("individual.c","w"))){
	      cerr << "Could not open individual.c.\n";
	      cerr << "Execution aborted.\n";
	      exit(0);
	    }
	    //Write start buffer to file
	    fprintf(file,"%s",ISstart);
	    //Write phenotype code to file
	    fprintf(file, 
		    "%s",
		    phenotype->getString().c_str());
	    
	    //Write end buffer to file
	    fprintf(file,"%s",ISend);
	    fclose(file);

#if defined GESPIRAL_USE_TCC_COMP
	    //Compile and execute file with TCC
	    if(system("tcc individual.c tcc_GEspiral.o -lm && ./a.out > result")==-1){
	      cerr << "Compilation or execution failed.\n";
	      cerr << "Execution aborted.\n";
	      exit(0);
	    }
#else
	    //Compile and execute file with GCC
	    if(system("gcc -pipe individual.c gcc_GEspiral.o -lm && ./a.out > result")==-1){
	      cerr << "Compilation or execution failed.\n";
	      cerr << "Execution aborted.\n";
	      exit(0);
	    }
#endif
	    //Open result file, containing fitness score
	    if(!(file=fopen("result","r")))
	      {
		cerr << "Could not open result file.\n";
		cerr << "Execution aborted.\n";
		exit(0);
	      }
	    fscanf(file,"%d",&fitness);
	    fclose(file);
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
};

#endif

