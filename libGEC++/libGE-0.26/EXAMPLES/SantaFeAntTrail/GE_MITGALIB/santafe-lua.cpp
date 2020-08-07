// santafe-lua.cpp -*- C++ -*-
#ifndef _SANTAFE_LUA_CPP_
#define _SANTAFE_LUA_CPP_

#include<cstdio>
#include<cstdlib>
#include<cstring>

#include<ga/ga.h>
#include<GE/ge.h>
#include"GEListGenome.h"

extern "C"{
#include"lua.h"
#include"lualib.h"
#include"lauxlib.h"
}

using namespace std;

// GE mapper, declared in main.cpp
extern GEGrammarSI mapper;

// Numer of Objective function calls, declared in main.cpp
extern int obj_calls;

// Fitness value;
int fitness;

// Lua state
lua_State *lua_state;

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
	/* Init lua interface */
	//Open lua state
	lua_state=lua_open();
	luaL_openlibs(lua_state);

	//Load GEant and GETrail code
	if((luaL_loadfile(lua_state,"GEant.lua"))||lua_pcall(lua_state,0,0,0)){
		cerr << lua_tostring(lua_state,-1) << "\n";
		cerr << "Could not read GEant.lua\n";
		cerr << "Execution aborted.\n";
		exit(0);
	}
	if((luaL_loadfile(lua_state,"GEtrail.lua"))||lua_pcall(lua_state,0,0,0)){
		cerr << lua_tostring(lua_state,-1) << "\n";
		cerr << "Could not read GEtrail.lua\n";
		cerr << "Execution aborted.\n";
		exit(0);
	}
	char *initcode="ReadTrailGEtrail(\"santafe.trl\")";
	if(luaL_loadbuffer(lua_state,initcode,strlen(initcode),"line")||
		lua_pcall(lua_state,0,0,0)){
		cerr << lua_tostring(lua_state,-1);
		cerr << "Could not execute initial trail code.\n";
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
		//Write start code to buffer
		buffer="initGEtrail()\nresetGEtrail(615)\nwhile _energy>0 do\n";
		//Write phenotype code to buffer
		buffer+=phenotype->getString();
		//Write end code to buffer
		buffer+="\nend\n";
		//Load and interpret buffer
		if(luaL_loadbuffer(lua_state,buffer.c_str(),buffer.size(),"line")||
			lua_pcall(lua_state,0,0,0)){
			// Lua error compiling buffer
			cout << lua_tostring(lua_state,-1);
			fitness=0;
		}
		else{
			lua_getglobal(lua_state,"_picked_up");
			fitness=static_cast<int>(lua_tonumber(lua_state,-1));
		}
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

