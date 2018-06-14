#ifndef _eoGEEvalFunc_h
#define _eoGEEvalFunc_h

// include the base definition of eoEvalFunc
#include <eoEvalFunc.h>

#include<GE/ge.h>

// Use Slang for evaluation
#include<slang/slang.h>

typedef double Real;

template <class EOT>
class eoGEEvalFunc : public eoEvalFunc<EOT>{
	public:
		eoGEEvalFunc(GEGrammar &originalMapper, string grammarFile, unsigned int wrappingEvents)
		  : fitness(0.0)
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
			// Init S-lang interface
			if((-1==SLang_init_slang())//basic interpreter functions
			   || (-1 == SLang_init_slmath())) {
				exit (EXIT_FAILURE);
			}
			if(-1==SLang_load_file("GEcart.sl")){
				SLang_restart(1);
				SLang_set_error(0);
			}

			//Create interface between fit and Fitness_Variable
			if (-1==SLadd_intrinsic_variable("Total_Time",
				       &(fitness),SLANG_DOUBLE_TYPE, 0)){
			  exit(EXIT_FAILURE);
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

				fitness = 0.0;
				if(phenotype->getValid()){
				        string buffer;
					//Write start code to buffer
					buffer="initCart(); resetCart(); while(currFitCase < numFitCase) { if (";
					//Write phenotype code to buffer
					buffer+=phenotype->getString();
					//Write end code to buffer
					buffer+=" > 0.0) { velocityChange = posForceVelChange; } else { velocityChange = negForceVelChange; } stepSim(); } Total_Time=sumFitCaseTimes;";

					//Load and interpret buffer
					if (-1==SLang_load_string(const_cast<char*>(buffer.c_str()))){
						SLang_restart(1);
						SLang_set_error(0);
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
		// (NOTE: the type of Real must match the type
		// specified in the call to SLadd_intrinsic_variable above.
		Real fitness;
};

#endif

