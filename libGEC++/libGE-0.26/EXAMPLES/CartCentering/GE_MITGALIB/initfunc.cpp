// initfunc.cpp -*- C++ -*-
#ifndef _INITFUNC_CPP_
#define _INITFUNC_CPP_

#include<ga/ga.h>
#include<GE/ge.h>

using namespace std;

// GE mapper, declared in main.cpp
extern GEGrammarSI mapper;
// Min and maximum size for random initialisation defined in main.cpp.
extern int minSize;
extern int maxSize;

//Randomly initialise genome with minSize<=length<=maxSize, of 0<=value<=255
void initFuncRandom(GAGenome &g){
	GAListGenome<unsigned char> &genome=
		static_cast<GAListGenome<unsigned char> &>(g);

	//Destroy any pre-existing list
	while(genome.head()) genome.destroy();

	// Create all individuals with a length between minSize and maxSize.
	int n=GARandomInt(minSize, maxSize);
	//Each gene is a number between 0 and 255
	//Insert the first gene
	genome.insert(GARandomInt(0,static_cast<unsigned char>(-1)),
				  GAListBASE::HEAD);
	//Create rest of list
	for(int ii=0; ii<n-1; ii++)
		genome.insert(GARandomInt(0,static_cast<unsigned char>(-1)));
}

void initFuncSI(GAGenome &g){
	GAListGenome<unsigned char> &genome=
		static_cast<GAListGenome<unsigned char> &>(g);

	//Destroy any pre-existing list
	while(genome.head()) genome.destroy();

	// Apply sensible initialisation to genotype
	if(!mapper.init()){
		cerr << "Error using sensible initialisation.\n";
		cerr << "Execution aborted.\n";
		exit(0);
	}
	// Now copy genotype onto genome
	Genotype::const_iterator genIt=(mapper.getGenotype())->begin();
	// Insert the first gene
	genome.insert(*(genIt++),GAListBASE::HEAD);
	//Create rest of list
	while(genIt!=(mapper.getGenotype())->end()){
		genome.insert(*genIt);
		genIt++;
	}
}

#endif
