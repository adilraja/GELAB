// Inilialiser.h -*- C++ -*-
#ifndef _INITIALIZER_H_
#define _INITIALIZER_H_

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* This is an abstract class that cannot be instantiated; it defines the     */
/* most basic characteristics and functionality of an initialiser. An        */
/* initialiser contains a population size and a population index. It defines */
/* the virtual method init(), which applies the initialisation process.      */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "libGEdefs.h"

using namespace std;

class Initialiser{
	public:
		Initialiser(const unsigned int=1);
		Initialiser(const Initialiser&);
		virtual ~Initialiser();
		unsigned int getPopSize() const;
		void setPopSize(const unsigned int);
		unsigned int getIndex() const;
		void setIndex(const unsigned int);
		virtual bool init(const unsigned int) = 0;
	private:
		unsigned int popSize;
		unsigned int popIndex;
};

#endif

