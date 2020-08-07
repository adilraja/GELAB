// Phenotype.cpp -*- C++ -*-
#ifndef _PHENOTYPE_CPP_
#define _PHENOTYPE_CPP_

//#include <config.h>

#include<iostream>
#include<string>

#include"Phenotype.h"

///////////////////////////////////////////////////////////////////////////////
// Default constructor. Creates a phenotype structure, and sets its valid
// field to newValid and its fitness to newFitness. Non-specified arguments are
// given default values, as specified in the function prototype.
Phenotype::Phenotype(const bool newValid,const FitnessType newFitness):vector<const Symbol*>(),_libGE_Phenotype_valid(newValid),_libGE_Phenotype_fitness(newFitness){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Phenotype::Phenotype(const bool, const FitnessType)' called\n";
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Copy constructor.
Phenotype::Phenotype(const Phenotype &copy):vector<const Symbol*>(copy){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Phenotype::Phenotype(const Phenotype&)' called\n";
#endif
	setValid(copy.getValid());
	setFitness(copy.getFitness());
}

///////////////////////////////////////////////////////////////////////////////
// Destructor.
Phenotype::~Phenotype(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Phenotype::~Phenotype()' called\n";
#endif
// do nothing!
}

///////////////////////////////////////////////////////////////////////////////
// Returns the current _libGE_Phenotype_valid field.
bool Phenotype::getValid() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'bool Phenotype::getValid()' called\n";
#endif
	return _libGE_Phenotype_valid;
}

///////////////////////////////////////////////////////////////////////////////
// Sets a new value for the _libGE_Phenotype_valid field.
void Phenotype::setValid(const bool newValid){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Phenotype::setValid(const bool)' called\n";
#endif
	_libGE_Phenotype_valid=newValid;
}

///////////////////////////////////////////////////////////////////////////////
// Returns the current fitness score.
FitnessType Phenotype::getFitness() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'FitnessType Phenotype::getFitness()' called\n";
#endif
	return _libGE_Phenotype_fitness;
}

///////////////////////////////////////////////////////////////////////////////
// Sets a new fitness score.
void Phenotype::setFitness(const FitnessType newFitness){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Phenotype::setFitness(const FitnessType)' called\n";
#endif
	_libGE_Phenotype_fitness=newFitness;
}

///////////////////////////////////////////////////////////////////////////////
// Returns string containing phenotype symbols.
string Phenotype::getString() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'string Phenotype::getString()' called\n";
#endif
	string s;
	Phenotype::const_iterator it = begin();

	while(it!=end()){
		s+=**it;
		it++;
	}
	return s;
}

/*
///////////////////////////////////////////////////////////////////////////////
// Returns char* containing phenotype symbols.
const char* Phenotype::c_str() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'char* Phenotype::c_str()' called\n";
#endif
	return getString().c_str();
}
*/

///////////////////////////////////////////////////////////////////////////////
// Print the contents of the phenotype.
ostream &operator<<(ostream &stream, const Phenotype &ph){
#if (DEBUG_LEVEL >= 2)
	cerr << "'ostream &operator<<(ostream &, const Phenotype &)' called\n";
#endif
	string s;
	Phenotype::const_iterator it = ph.begin();

	while(it!=ph.end()){
		s+=**it;
		it++;
	}
	return stream << s;
}

#endif

