#ifndef _eoGEEvalFunc_h
#define _eoGEEvalFunc_h

// include the base definition of eoEvalFunc
#include "eoEvalFunc.h"

#include <cmath>

#include<GE/ge.h>

// Use Slang for evaluation
#include<slang/slang.h>

// GE mapper.
extern GEGrammarSI mapper;

template <class EOT>
class eoGEEvalFunc : public eoEvalFunc<EOT>{
 public:
  eoGEEvalFunc(GEGrammar &mapper, string grammarFile, unsigned int wrappingEvents)
    {

      //Set maximum number of wrapping events per mapping
      mapper.setMaxWraps(3);
      if (!mapper.readBNFFile("grammar.bnf"))
	{
	  cerr << "Could not read grammar.bnf\n";
	  cerr << "Execution aborted.\n";
	  exit(0);
	}

      /* Init S-lang interface */
      if (-1 == SLang_init_all ()) /* basic interpreter functions */
	exit (EXIT_FAILURE);
      
      if (-1 == SLang_load_file ("GEspiral.sl"))
	{
	  SLang_restart (1);
	  SLang_set_error(0);
	  cout << "An error has occured while loading eval\n";
	  exit(0);
	}
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
	    //Write start code to buffer
	    buffer="initVals();\nvariable i;\nvariable temp = Double_Type;\n";
	    buffer+="variable fit = Double_Type;\nfit=0;\nfor(i=0;i<194;i++)\n";
	    buffer+="{\nvariable x=xvals[i];variable y=yvals[i];\ntemp=";
	    buffer+=phenotype->getString();
	    //Write end code to buffer
	    buffer+=";\nif(temp < 0)\nEvolved[i]=0;\nelse\nEvolved[i]=1;\n}\nFitness_Variable=AssignFitness();";
	    //Create interface with variable Fitness_Variable
	    if (-1 == SLadd_intrinsic_variable("Fitness_Variable",
					       &(fitness),SLANG_INT_TYPE, 0))
	      {
		exit(EXIT_FAILURE);
	      }
	    //Load and interpret buffer
	    if (-1 == SLang_load_string(const_cast<char*>(buffer.c_str())))
	      {
		cout << "an eoor has occured, exiting  \n" << buffer << endl;
		SLang_restart(1);
		SLang_set_error(0);
	      }
	    if(isinf(fitness) || isnan(fitness) || !isfinite(fitness))
	      fitness = 0;
	  }
	_eo.fitness(fitness);
      }
  }
 private:
  string buffer;
};

#endif

