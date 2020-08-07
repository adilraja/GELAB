#ifndef _eoGEEvalFunc_h
#define _eoGEEvalFunc_h

// include the base definition of eoEvalFunc
#include <eoEvalFunc.h>

#include<GE/ge.h>

// Use lua for evaluation
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

typedef double Real;

template <class EOT>
class eoGEEvalFunc : public eoEvalFunc<EOT>{
	public:
		eoGEEvalFunc(GEGrammar &originalMapper, string grammarFile, unsigned int wrappingEvents)
{
			/* Save local mapper pointer */
			mapper=&originalMapper;
			/* Init GE mapper */
			//Set maximum number of wrapping events per mapping
			mapper->setMaxWraps(wrappingEvents);
			//Load grammar
			if (!mapper->readBNFFile(grammarFile)){
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

		void operator()(EOT & _eo){
			// test for invalid to avoid recomputing fitness
			// of unmodified individuals
			if (_eo.invalid()){
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

				Real fitness = 0.0;
				if(phenotype->getValid()){
				        string buffer;
				        //Write start code to buffer
				        buffer =  "initCart(); resetCart(); while currFitCase < numFitCase do if ";
					//Write phenotype code to buffer
					buffer += phenotype->getString();
					//Write end code to buffer
					buffer += " > 0.0 then velocityChange = posForceVelChange; else velocityChange = negForceVelChange; end stepSim(); end";

					/* load the phenotype into lua environment */
					if (luaL_dostring(L, buffer.c_str()) != 0)
					{
					  cerr << "Could not execute phenotype code in lua state,\n";
					  cerr << lua_tostring(L, -1) << "\n";
					  cerr << "Execution aborted.\n";
					  exit (0);
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
				}
				_eo.fitness(fitness);
			}
		}

	private:
		GEGrammar *mapper;
		lua_State *L;
};

#endif

