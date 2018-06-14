// GE_ILLIGALSGA.cpp -*- C++ -*-
#ifndef _GE_ILLIGALSGA_CPP_
#define _GE_ILLIGALSGA_CPP_

//#include <config.h>

#include<iostream>
#include<fstream>

#include "GEGrammar.h"

extern "C"{

// sga definitions
#ifndef BITS_PER_BYTE
#define BITS_PER_BYTE 8               // number of bits per byte on this machine
#endif
#ifndef UINTSIZE
#define UINTSIZE (BITS_PER_BYTE*sizeof(unsigned))       // # of bits in unsigned
#endif

struct individual 
{
    unsigned *chrom;                  /* chromosome string for the individual */
    double fitness;                              /* fitness of the individual */
    int      xsite;                               /* crossover site at mating */
    int      parent[2];                  /* who the parents of offspring were */
    int      *utility;           /* utility field can be used as pointer to a */
                /* dynamically allocated, application-specific data structure */
};

static GEGrammar mapper;

/*
Allocates memory for an integer array, stores the current genotype in that
array, and returns the address of the allocated memory in the argument pointer,
as well as its size as the return value. The user is responsible for freeing
the allocated memory.
*/
int GE_ILLIGALSGA_getGenotype(int **c_genotype){
	Genotype const *genotype=mapper.getGenotype();
	Genotype::const_iterator g_it=genotype->begin();
	*c_genotype=(int*)malloc(genotype->size()*sizeof(int));
	int i=0;
	while(g_it!=genotype->end()){
		(*c_genotype)[i]=*g_it;
		g_it++;
		i++;
	}
	return genotype->size();
}

/*
Allocates memory for a NULL-terminated character array, stores the current
phenotype in that array, and returns the address of the allocated memory in the
argument pointer, as well as its size as the return value. The user is
responsible for freeing the allocated memory.
*/
int GE_ILLIGALSGA_getPhenotype(char **c_phenotype){
	Phenotype const *phenotype=mapper.getPhenotype();
	Phenotype::const_iterator p_it=phenotype->begin();
	string ph="";

	// Add all symbols of phenotype
	while(p_it!=phenotype->end()){
		ph+=(*p_it++)->c_str();
	}

	// Allocate string size for phenotype 'string'
	if(!(*c_phenotype=(char*)malloc(ph.size()*sizeof(char)))){
		cerr << "Error allocating memory for phenotype string.\n";
		cerr << "Function 'int GE_ILLIGALSGA_getPhenotype(char **c_phenotype)'.\n";
		cerr << "Execution aborted.\n";
	}
	strncpy(*c_phenotype,ph.c_str(),ph.size());

	return ph.size()+1;
}

/*
Returns the validity of the phenotype contained in the static mapper.
*/
int GE_ILLIGALSGA_validPhenotype(){
	Phenotype const *phenotype=mapper.getPhenotype();
	return(phenotype->getValid());
}

/*
Sets the number of allowed wrapping events for the static mapper.
*/
void GE_ILLIGALSGA_setMaxWraps(int wraps){
	mapper.setMaxWraps(wraps);
}

/*
Interface to the readBNFFile(char *) method in CFGrammar, for the static
mapper.
*/
int GE_ILLIGALSGA_readBNFFile(char *filename){
	if (mapper.readBNFFile(filename))
		return 1;
	return 0;
}

/*
Interface to the readBNFString(char *) method in CFGrammar, for the static
mapper.
*/
int GE_ILLIGALSGA_readBNFString(char *str){
	if (mapper.readBNFString(str))
		return 1;
	return 0;
}

/*
Interface to the outputBNF(ostream&) method in CFGrammar, for the static
mapper.
*/
void GE_ILLIGALSGA_outputBNF(){
	mapper.outputBNF(cout);
}

/*
Accepts an array of unsigned, representing an sga-c chromosome, and translates
it to an array of integers, using the specified number of bits per gene, and
limiting the integer values to the range specified.
*/
int GE_ILLIGALSGA_translate(unsigned *chrom, int lchrom, int *string, int widthpos, int widthval, int range){
	char using_pos=1;//Start by using widthpos as value for bits_per_gene if using GAuGE
	register int length, i, value;
	int j, index_chrom;
	unsigned mask, tmp;
	
	if(widthpos)/* Using GAuGE */
		length=widthpos;
	else/* No position field */
		length=widthval;
	tmp = chrom[index_chrom=0];
	for(i=0,j=0,value=0,mask=1;i<lchrom;i++){
		length--;/* length of the current gene */
		if(tmp&mask)
			value++;
		tmp=tmp>>1;
		if(!length){/* completed a gene */
			if(range)
				value%=range;
			string[j++]=value;
			value=0;
			if(widthpos){/* Using GAuGE */
				if(using_pos)/* time to use widthval */
					length=widthval;
				else/* time to use widthpos */
					length=widthpos;
				using_pos=!using_pos;
				}
			else/* No position field */
				length=widthval;
			}
		/* left shift only if this isn't the last bit to be shifted in */
		if(i<lchrom-1)
			value=value<<1;
		/* if we reached the end of an unsigned int */
		if(!((i+1)%UINTSIZE))
			tmp=chrom[++index_chrom];
	}
	return j;
}

/*
Accepts an sga-c chromosome, transforms it into a libGE Genotype structure, and
assigns it to the static mapper.
*/
void GE_ILLIGALSGA_Mapper(struct individual *critter, int lchrom, int bpg){
	static Genotype genotype;
	/* int integers[lchrom/bpg]; */
	int *integers=new int [lchrom/bpg];
	if(!integers){
		cerr << "Memory allocation error in GE_ILLIGALSGA_Mapper().\n";
		cerr << "Execution terminated.\n";
		exit(0);
	}
	// Transform individual into Genotype
	unsigned newsize=GE_ILLIGALSGA_translate(critter->chrom,lchrom,integers,0,bpg,0);
	if(genotype.size()!=newsize)
		genotype.resize(newsize);
	Genotype::iterator g_it=genotype.begin();
	unsigned i=0;
	while(i<newsize){
		*g_it=integers[i];
		i++;
		g_it++;
	}
	genotype.setValid(true);

	// Give it to mapper
	mapper.setGenotype(genotype);

	delete [] integers;
}

}
#endif

