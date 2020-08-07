// cartcenter-lua.cpp -*- C++ -*-
#ifndef _CARTCENTER_LUA_CPP_
#define _CARTCENTER_LUA_CPP_

#include<cstdio>
#include<cstdlib>
#include<cstring>

#include<ga/ga.h>
#include<GE/ge.h>
#include"GEListGenome.h"

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

using namespace std;

typedef double Real;

// GE mapper, declared in main.cpp
extern GEGrammarSI mapper;

// Numer of Objective function calls, declared in main.cpp
extern int obj_calls;

char buffer[7000];

// Lua state.
lua_State *L;

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

	/* Set up lua and load required libraries. */
	L = lua_open();
	luaL_openlibs(L);
	
	/* Load the GECart.lua functions file. */
	if (luaL_dofile(L, "GEcart.lua") != 0)
	{
	  cerr << "Could not load GEcart.lua into lua state.\n";
	  cerr << lua_tostring(L, 0) << "\n";
	  cerr << "Execution aborted.\n";
	  exit(0);
	}
}

//Attributes a fitness score to a genome
float objfunc(GAGenome &g){
	obj_calls++;
	GEListGenome &genome = static_cast<GEListGenome&>(g);
	//Assign genotype to mapper
	mapper.setGenotype(genome);
	//Grab phenotype
        Phenotype const *phenotype=mapper.getPhenotype();
	if(phenotype->getValid()){

	  Real fitness = 0.0;

	  //Write start code to buffer
	  strcpy(buffer, "initCart(); resetCart(); while currFitCase < numFitCase do if ");
	  //Write phenotype code to buffer
	  strcat(buffer, phenotype->getString().c_str());
	  //Write end code to buffer
	  strcat(buffer, " > 0.0 then velocityChange = posForceVelChange; else velocityChange = negForceVelChange; end stepSim(); end");

	  /* load the phenotype into lua environment */
	  if (luaL_dostring(L, buffer) != 0)
	  {
	    cerr << "Could not execute phenotype code in lua state,\n";
	    cerr << lua_tostring(L, -1) << "\n";
	    cerr << "Execution aborted.\n";
	    return (0);
	  }

	  /* Get the fitness value. */
	  lua_getglobal(L, "sumFitCaseTimes");
	  if (lua_isnumber(L, -1) == 1)
	  {
	    fitness = lua_tonumber(L, -1);
	  }
	  else
	  {
	    cerr << "Could not read value of sumFitCaseTimes in Lua state.\n" ;
	    cerr << "Execution aborted.\n";
	    exit(0);
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


	  

	  
