#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

#include<ga/ga.h>
#include<GE/ge.h>
#include "GEListGenome.h"

#include<slang/slang.h>

using namespace std;


// GE mapper, declared in main.cpp
extern GEGrammarSI mapper;

// Fitness variable.
int fitness;


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

  /* Init S-lang interface */
  if (-1 == SLang_init_all ())
    exit (EXIT_FAILURE);

  if (-1 == SLang_load_file ("GEspiral.sl")){
    SLang_restart (1);
    SLang_set_error(0);
  } 
}


//Attributes a fitness score to a genome
float objfunc(GAGenome &g){
  string buffer;
  GEListGenome &genome = static_cast<GEListGenome&>(g);

  //Assign genotype to mapper
  mapper.setGenotype(genome);
  //Grab phenotype
  Phenotype const *phenotype=mapper.getPhenotype();
  if(phenotype->getValid()){
    

    //Write start code to buffer
    buffer="initVals();\nvariable i;\nvariable temp = Double_Type;\n";
    buffer+="variable fit = Double_Type;\nfit=0;\nfor(i=0;i<194;i++)\n";
    buffer+="{\nvariable x = Double_Type;\nvariable y= Double_Type;\n";
    buffer+="y=yvals[i];\nx=xvals[i];\nEvolved[i]=";
    buffer+=phenotype->getString();
    //Write end code to buffer
    buffer+=";\n}\nFitness_Variable=AssignFitness();";
    
    //Create interface with variable Fitness_Variable
    if (-1 == SLadd_intrinsic_variable("Fitness_Variable",
				     &(fitness), SLANG_INT_TYPE, 0))
    {
      exit(EXIT_FAILURE);
    }

    //Load and interpret buffer
    if (-1 == SLang_load_string(const_cast<char*>(buffer.c_str()))){
      SLang_restart(1);
      SLang_set_error(0);
    }
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


