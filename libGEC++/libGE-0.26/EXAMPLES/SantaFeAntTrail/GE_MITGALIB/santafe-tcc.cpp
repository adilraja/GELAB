// santafe-tcc.cpp -*- C++ -*-
#ifndef _SANTAFE_TCC_CPP_
#define _SANTAFE_TCC_CPP_

#include<cstdio>
#include<cstdlib>
#include<cstring>

#include<ga/ga.h>
#include<GE/ge.h>
#include"libtcc.h"
#include"GEListGenome.h"

using namespace std;

// GE mapper, declared in main.cpp
extern GEGrammarSI mapper;

// Numer of Objective function calls, declared in main.cpp
extern int obj_calls;

//Buffers for start and end code of phenotype string
string SFstart;
string SFend;

//Initialises the mapper, and the s-lang interpreter
void app_init(unsigned int wrappingEvents,string grammarFile){
	char buffer[1000];
	FILE *c_code;

	/* Read buffer code files */
	SFstart="";
	if(!(c_code=fopen("santafestart.tcc","r"))){
		cerr << "Could not read santafestart.tcc\n";
		cerr << "Execution aborted.\n";
		exit(0);
	}
	while(fgets(buffer,1000,c_code)){
		SFstart+=buffer;
	}
	fclose(c_code);
	SFend="";
	if(!(c_code=fopen("santafeend.tcc","r"))){
		cerr << "Could not read santafeend.tcc\n";
		cerr << "Execution aborted.\n";
		exit(0);
	}
	while(fgets(buffer,1000,c_code)){
		SFend+=buffer;
	}
	fclose(c_code);

	/* Init GE mapper */
	//Set maximum number of wrapping events per mapping
	mapper.setMaxWraps(wrappingEvents);
	//Load grammar
	if (!mapper.readBNFFile(grammarFile)){
		cerr << "Could not read grammar.bnf\n";
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
		int fitness;
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
			fitness=0;
		}
		else{//Load and interpret buffer
			fitness=tcc_run(s,0,NULL);
		}
		//Delete TCC state
		tcc_delete(s);
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

