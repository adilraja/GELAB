#ifndef _eoGEEvalFunc_h
#define _eoGEEvalFunc_h

#include<GE/ge.h>

// include the base definition of eoEvalFunc
#include <eoEvalFunc.h>

typedef float Real;

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

			/* Read code start and end files */
			char buffer[1000];
			FILE *c_code;
			strcpy(CCstart,"");
			if(!(c_code=fopen("cartcenterstart.c","r"))){
			  cerr << "Could not read cartcenterstart.c\n";
			  cerr << "Execution aborted.\n";
			  exit(0);
			}
			while(fgets(buffer,1000,c_code))
			  strcat(CCstart,buffer);
			fclose(c_code);
			strcpy(CCend,"");

			if(!(c_code=fopen("cartcenterend.c","r"))){
			  cerr << "Could not read cartcenterend.c\n";
			  cerr << "Execution aborted.\n";
			  exit(0);
			}
			while(fgets(buffer,1000,c_code))
			  strcat(CCend,buffer);
			fclose(c_code);
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

				  //Create output file
				  FILE *file;
				  if(!(file=fopen("individual.c","w"))){
				    cerr << "Could not open individual.c.\n";
				    cerr << "Execution aborted.\n";
				    exit(0);
				  }
				  //Write start buffer to file
				  fprintf(file,"%s",CCstart);
				  //Write phenotype code to file
				  fprintf(file, 
					  "%s",
					  phenotype->getString().c_str());
				  
				  //Write end buffer to file
				  fprintf(file,"%s",CCend);
				  fclose(file);

#if defined GECART_USE_TCC_COMP
				  //Compile and execute file with TCC
				  if(system("tcc individual.c tcc_GEcart.o -lm && ./a.out > result")==-1){
				    cerr << "Compilation or execution failed.\n";
				    cerr << "Execution aborted.\n";
				    exit(0);
				  }
#else
				  //Compile and execute file with GCC
				  if(system("gcc -pipe individual.c gcc_GEcart.o -lm && ./a.out > result")==-1){
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
				  fscanf(file,"%f", &fitness);
				  fclose(file);

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
		char CCstart[3000];
		char CCend[3000];
};

#endif

