// Initialiser.cpp -*- C++ -*-
#ifndef _INITIALIZER_CPP_
#define _INITIALIZER_CPP_

//#include <config.h>

#include<iostream>

#include "Initialiser.h"

///////////////////////////////////////////////////////////////////////////////
// Default constructor. Create vector of random seeds.
Initialiser::Initialiser(const unsigned int newPopSize):popSize(newPopSize){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'Initialiser::Initialiser(const unsigned int)' called\n";
	#endif
	popIndex=0;
}

///////////////////////////////////////////////////////////////////////////////
// Copy Constructor.
Initialiser::Initialiser(const Initialiser& copy){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'Initialiser::Initialiser(const Initialiser&)' called\n";
	#endif
	setPopSize(copy.getPopSize());
	setIndex(copy.getIndex());
}

///////////////////////////////////////////////////////////////////////////////
// Destructor.
Initialiser::~Initialiser(){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'Initialiser::~Initialiser()' called\n";
	#endif
}

///////////////////////////////////////////////////////////////////////////////
// Returns current population size of initialiser.
unsigned int Initialiser::getPopSize() const{
	#if (DEBUG_LEVEL >= 2)
	cerr << "'Initialiser::getPopSize() const' called\n";
	#endif
	return popSize;
}

///////////////////////////////////////////////////////////////////////////////
// Sets population size of initialiser.
void Initialiser::setPopSize(const unsigned int newPopSize){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'Initialiser::setPopSize(unsigned int)' called\n";
	#endif
	popSize=newPopSize;
}

///////////////////////////////////////////////////////////////////////////////
// Returns current index of initialiser.
unsigned int Initialiser::getIndex() const{
	#if (DEBUG_LEVEL >= 2)
	cerr << "'Initialiser::getIndex() const' called\n";
	#endif
	return popIndex;
}

///////////////////////////////////////////////////////////////////////////////
// Sets population index of initialiser.
void Initialiser::setIndex(const unsigned int newPopIndex){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'Initialiser::setIndex(unsigned int)' called\n";
	#endif
	if(newPopIndex<0){
		popIndex=getPopSize()-((-newPopIndex)%getPopSize());
	}
	else if(newPopIndex>=getPopSize()){
		popIndex=newPopIndex%getPopSize();
	}
	else{
		popIndex=newPopIndex;
	}
}

#endif

