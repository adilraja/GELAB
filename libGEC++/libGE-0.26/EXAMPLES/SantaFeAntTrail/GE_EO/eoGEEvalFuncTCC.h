// eoGEEvalFuncTCC.h -*- C++ -*-
#ifndef _eoGEEvalFuncTCC_h
#define _eoGEEvalFuncTCC_h

// include the base definition of eoEvalFunc
#include "eoEvalFunc.h"

#include<GE/ge.h>

// Use TCC for evaluation
#include"libtcc.h"

template <class EOT>
class eoGEEvalFunc : public eoEvalFunc<EOT>{
	public:
		eoGEEvalFunc(GEGrammar &originalMapper, string grammarFile, unsigned int wrappingEvents){
			/* Save local mapper pointer */
			mapper=&originalMapper;
			/* Init GE mapper */
			// Set maximum number of wrapping events per mapping
			mapper->setMaxWraps(wrappingEvents);
			// Load grammar
			if (!mapper->readBNFFile(grammarFile)){
				cerr << "Could not read grammar file.\n";
				cerr << "Execution aborted.\n";
				exit(0);
			}
			/* Read buffer code files */
			char buffer[1000];
			FILE *c_code;
			SFstart="";
			if(!(c_code=fopen("santafestart.tcc","r"))){
				cerr << "Could not read santafestart.tcc\n";
				cerr << "Execution aborted.\n";
				exit(0);
			}
			while(fgets(buffer,1000,c_code))
				SFstart+=buffer;
			fclose(c_code);
			SFend="";
			if(!(c_code=fopen("santafeend.tcc","r"))){
				cerr << "Could not read santafeend.tcc\n";
				cerr << "Execution aborted.\n";
				exit(0);
			}
			while(fgets(buffer,1000,c_code))
				SFend+=buffer;
			fclose(c_code);
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
					//Create TCC state
					TCCState *s=tcc_new();
					//Set output type
					tcc_set_output_type(s,TCC_OUTPUT_MEMORY);
					//Add GEant and GETrail definitions
					tcc_add_file(s,"tcc_GEant.o");
					tcc_add_file(s,"tcc_GEtrail.o");
					//Create buffer
					buffer=SFstart+phenotype->getString()+SFend;
					//Compile buffer
					if(tcc_compile_string(s,buffer.c_str())!=0){
						fit=0;
					}
					else{//Load and interpret buffer
						fit=tcc_run(s,0,NULL);
					}
					//Delete TCC state
					tcc_delete(s);
				}
				_eo.fitness(fit);
			}
		}

	private:
		GEGrammar *mapper;
		string SFstart;
		string SFend;
		string buffer;
		int fit;
};

#endif

