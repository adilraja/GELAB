#ifndef _eoGEEvalFunc_h
#define _eoGEEvalFunc_h

// include the base definition of eoEvalFunc
#include "eoEvalFunc.h"

#include <cmath>

#include<GE/ge.h>

// Use lua for evaluation
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}


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
	    buffer="initVals(); temp = 0.0; fit = 0.0; ";
	    buffer+="for i=0,193,1 do ";
	    // buffer+="io.write(\"i is \", i, \" x is \", x, \" y is \", y, \"\\n\"); temp=";
	    buffer+="x=xvals[i]; y=yvals[i]; temp=";
	    buffer+=phenotype->getString();
	    //Write end code to buffer
	    buffer+="; if temp < 0 then Evolved[i]=0; else Evolved[i]=1; end end ";
	    buffer+="Fitness_Variable = AssignFitness();";
	    // std::cerr << buffer << std::endl;

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
	  }
	_eo.fitness(fitness);
      }
  }
 private:
  string buffer;
  lua_State *L;
};

#endif

