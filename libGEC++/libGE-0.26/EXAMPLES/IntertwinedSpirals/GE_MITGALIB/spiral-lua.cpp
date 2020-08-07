#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

#include<ga/ga.h>
#include<GE/ge.h>
#include "GEListGenome.h"

// Use lua for evaluation
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}


using namespace std;


// GE mapper, declared in main.cpp
extern GEGrammarSI mapper;

// Lua state.
lua_State *L;


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

  /* Set up lua and load required libraries. */
  L = lua_open();
  luaL_openlibs(L);
  
  /* Load the GECart.lua functions file. */
  if (luaL_dofile(L, "GEspiral.lua") != 0)
    {
      cerr << "Could not load GEspiral.lua into lua state.\n";
      cerr << lua_tostring(L, 0) << "\n";
      cerr << "Execution aborted.\n";
      exit(0);
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
    int fitness;

    //Write start code to buffer
    buffer="initVals(); temp = 0.0; fit = 0.0; ";
    buffer+="for i=0,193,1 do ";
    buffer+="x=xvals[i]; y=yvals[i]; temp=";
    buffer+=phenotype->getString();
    //Write end code to buffer
    buffer+="; if temp < 0 then Evolved[i]=0; else Evolved[i]=1; end end ";
    buffer+="Fitness_Variable = AssignFitness();";
    
    /* load the phenotype into lua environment */
    if (luaL_dostring(L, buffer.c_str()) != 0)
      {
	cerr << "Could not execute phenotype code in lua state,\n";
	cerr << lua_tostring(L, -1) << "\n";
	cerr << "Execution aborted.\n";
	exit (0);
      }
	    
    /* Get the fitness value. */
    lua_getglobal(L, "Fitness_Variable");
    if (lua_isnumber(L, -1) == 1)
      {
	fitness = static_cast<int>(lua_tonumber(L, -1));
      }
    else
      {
	cerr << "Could not read value of 'Fitness_Variable' in Lua state.\n" ;
	cerr << "Execution aborted.\n";
	exit(0);
      }
	    
    if(isinf(fitness) || isnan(fitness) || !isfinite(fitness))
      fitness = 0;

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


