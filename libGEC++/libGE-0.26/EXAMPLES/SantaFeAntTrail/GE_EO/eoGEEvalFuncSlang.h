// eoGEEvalFuncSlang.h -*- C++ -*-
#ifndef _eoGEEvalFuncSlang_h
#define _eoGEEvalFuncSlang_h

// include the base definition of eoEvalFunc
#include "eoEvalFunc.h"

#include<GE/ge.h>

// Use Slang for evaluation
#include<slang/slang.h>

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
			// Init S-lang interface
			if((-1==SLang_init_slang())//basic interpreter functions
				||(-1==SLang_init_stdio())){// stdio file I/O
				cerr << "Could not init S-Lang interface.\n";
				cerr << "Execution aborted.\n";
				exit(0);
			}
			if(-1==SLang_load_file("GEant.sl")){
				cerr << "Could not read GEant.sl\n";
				cerr << "Execution aborted.\n";
				exit(0);
			}
			if (-1==SLang_load_file ("GEtrail.sl")){
				cerr << "Could not read GEtrail.sl\n";
				cerr << "Execution aborted.\n";
				exit(0);
			}
			if (-1==SLang_load_string("ReadTrailGEtrail(\"santafe.trl\");")){
				cerr << "Could not execute code within the S-Lang interpreter.\n";
				cerr << "Execution aborted.\n";
				exit(0);
			}
			//Create interface between fit and Fitness_Variable
			if (-1==SLadd_intrinsic_variable("Fitness_Variable",
					&(fit),SLANG_INT_TYPE,0)){
				cerr << "Could not interface variable with S-Lang interpreter.\n";
				cerr << "Execution aborted.\n";
				exit(0);
			}
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
					buffer="initGEtrail(); resetGEtrail(615);while(_energy > 0){";
					//Write phenotype code to buffer
					buffer+=phenotype->getString();
					//Write end code to buffer
					buffer+="}\nFitness_Variable=_picked_up;";
					//Load and interpret buffer
					if (-1==SLang_load_string(const_cast<char*>(buffer.c_str()))){
						SLang_restart(1);
						SLang_set_error(0);
					}
				}
				_eo.fitness(fit);
			}
		}

	private:
		GEGrammar *mapper;
		string buffer;
		int fit;
};

#endif

