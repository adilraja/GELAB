// eoGEEvalFuncGCC.h -*- C++ -*-
#ifndef _eoGEEvalFuncGCC_h
#define _eoGEEvalFuncGCC_h

// include the base definition of eoEvalFunc
#include "eoEvalFunc.h"

#include<GE/ge.h>

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
			/* Read buffer code files */
			char buffer[1000];
			FILE *c_code;
			SFstart="";
			if(!(c_code=fopen("santafestart.c","r"))){
				cerr << "Could not read santafestart.c\n";
				cerr << "Execution aborted.\n";
				exit(0);
			}
			while(fgets(buffer,1000,c_code))
				SFstart+=buffer;
			fclose(c_code);
			SFend="";
			if(!(c_code=fopen("santafeend.c","r"))){
				cerr << "Could not read santafeend.c\n";
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
					FILE *file;
					//Create output file
					if(!(file=fopen("individual.c","w"))){
						cerr << "Could not open individual.c.\n";
						cerr << "Execution aborted.\n";
						exit(0);
					}
					//Write start buffer to file
					fprintf(file,"%s",SFstart.c_str());
					//Write phenotype code to file
					fprintf(file,"%s",phenotype->getString().c_str());
					//Write end buffer to file
					fprintf(file,"%s",SFend.c_str());
					fclose(file);

#if defined GECART_USE_TCC_COMP
					//Compile and execute file with TCC
					if(system("tcc individual.c tcc_GEant.o\
                                                 tcc_GEtrail.o && ./a.out > result")==-1){
					  cerr << "Compilation or execution failed.\n";
					  cerr << "Execution aborted.\n";
					  exit(0);
					}
#else
					//Compile and execute file with GCC
					if(system("gcc -pipe individual.c gcc_GEant.o\
						 gcc_GEtrail.o && ./a.out > result")==-1){
					  cerr << "Compilation or execution failed.\n";
					  cerr << "Execution aborted.\n";
					  exit(0);
					}
#endif

					//Open result file, containing fitness score
					if(!(file=fopen("result","r"))){
						cerr << "Could not open result file.\n";
						cerr << "Execution aborted.\n";
						exit(0);
					}
					fscanf(file,"%d",&fit);
					fclose(file);
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

