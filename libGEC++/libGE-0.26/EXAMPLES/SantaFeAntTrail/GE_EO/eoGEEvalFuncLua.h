// eoGEEvalFuncLua.h -*- C++ -*-
#ifndef _eoGEEvalFuncLua_h
#define _eoGEEvalFuncLua_h

// include the base definition of eoEvalFunc
#include "eoEvalFunc.h"

#include<GE/ge.h>

// Use Lua for evaluation
extern "C"{
#include"lua.h"
#include"lualib.h"
#include"lauxlib.h"
}

template <class EOT>
class eoGEEvalFunc : public eoEvalFunc<EOT>{
	public:
		eoGEEvalFunc(GEGrammar &originalMapper, string grammarFile, unsigned int wrappingEvents){

			/* Save local mapper pointer */
			mapper=&originalMapper;
			/* Init GE mapper */
			//Set maximum number of wrapping events per mapping
			mapper->setMaxWraps(wrappingEvents);
			//Load grammar
			if (!mapper->readBNFFile(grammarFile)){
				cerr << "Could not read grammar file.\n";
				cerr << "Execution aborted.\n";
				exit(0);
			}


			/* Init lua interface */
			// Open lua state
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

		~eoGEEvalFunc(){
			lua_close(lua_state);
		}

		void operator()(EOT & _eo){
			// test for invalid to avoid recomputing fitness
			// of unmodified individuals
			if (_eo.invalid()){
				//Reset fitness
				fit=0;
				//Create new (valid) genotype
				int genome[_eo.size()];
				for(unsigned int ii=0;ii<_eo.size();ii++){
					genome[ii]=_eo[ii];
				}
				Genotype genotype(genome,_eo.size());
				//Assign genotype to mapper
				mapper->setGenotype(genotype);
				//Grab phenotype
				Phenotype const *phenotype=mapper->getPhenotype();
				_eo.setEffectiveSize(mapper->getGenotype()->getEffectiveSize());
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
					        std::cout << buffer << std::endl;
						cout << lua_tostring(lua_state,-1);
						exit(0);
						fit=0;
					}
					else{
						lua_getglobal(lua_state,"_picked_up");
						fit=static_cast<int>(lua_tonumber(lua_state,-1));
					}
				}
				_eo.fitness(fit);
			}
		}

	private:
		GEGrammar *mapper;
		string buffer;
		int fit;
		// Lua state
		lua_State *lua_state;
};

#endif

