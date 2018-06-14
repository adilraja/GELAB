#ifndef _CARTCENTER_GCC_CPP_
#define _CARTCENTER_GCC_CPP_
#include<cstdio>
#include<cstdlib>
#include<cstring>

#include<ga/ga.h>
#include<GE/ge.h>
#include"GEListGenome.h"

using namespace std;

typedef float Real;

// GE mapper, declared in main.cpp
extern GEGrammarSI mapper;

// Numer of Objective function calls, declared in main.cpp
extern int obj_calls;

//Buffers for start and end code of the individual.c file
static char CCstart[3000];
static char CCend[3000];

//Loads the start and end code required to compile phenotypes,
//and initialises the mapper
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

	char buffer[7000];
	FILE *c_code;

	/* Read code start and end files */
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

//Attributes a fitness score to a genome
float objfunc(GAGenome &g){
	obj_calls++;
	GEListGenome &genome = static_cast<GEListGenome&>(g);
	//Assign genotype to mapper
	mapper.setGenotype(genome);
	//Grab phenotype
        Phenotype const *phenotype=mapper.getPhenotype();
	if(phenotype->getValid()){
		FILE *file;
		Real fitness = 0.0;

		//Create output file
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
		if(system("tcc individual.c tcc_GEcart.o -lm &&\
                                ./a.out > result")==-1){
			cerr << "Compilation or execution failed.\n";
			cerr << "Execution aborted.\n";
			exit(0);
		}
#else
		//Compile and execute file with GCC
		if(system("gcc -pipe individual.c gcc_GEcart.o -lm &&\
                                ./a.out > result")==-1){
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

		// Set effective size of genome
		genome.setEffectiveSize(mapper.getGenotype()->getEffectiveSize());

		return fitness;
	}
	else
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
