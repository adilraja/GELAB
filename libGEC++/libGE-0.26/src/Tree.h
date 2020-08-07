// Tree.h -*- C++ -*-
#ifndef _TREE_H_
#define _TREE_H_

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* This is a templated class that implements an n-ary tree.                  */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

//#include "libGEdefs.h"

#include<vector>

using namespace std;

template <class T>
class Tree;

template <class T>
class Tree: public vector<Tree<T> >{
	public:
		Tree(const unsigned int=1,const unsigned int=1);
		Tree(const T&,const unsigned int=1,const unsigned int=1);
		Tree(const Tree<T>&);
		~Tree();
		unsigned int getDepth() const;
		void setDepth(const unsigned int);
		unsigned int getCurrentLevel() const;
		void setCurrentLevel(const unsigned int);
		const T getData() const;
		void setData(const T&);
		bool getValid() const;
		void setValid(const bool);
	private:
		T data;
		unsigned int depth;
		unsigned int currentLevel;
		bool valid;
};

///////////////////////////////////////////////////////////////////////////////
// Constructor; initialises depth and current level.
template<class T>
Tree<T>::Tree(const unsigned int newDepth,const unsigned int newCurrentLevel):
	depth(newDepth),currentLevel(newCurrentLevel){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Tree<T>::Tree(const unsigned int, const unsigned int)' called\n";
#endif
	setValid(false);
}

///////////////////////////////////////////////////////////////////////////////
// Constructor; initialises data to match arguments.
template<class T>
Tree<T>::Tree(const T &newData,const unsigned int newCurrentLevel,
		const unsigned int newDepth):data(newData),depth(newDepth),
		currentLevel(newCurrentLevel){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Tree<T>::Tree(const T&, const unsigned int, const unsigned int)' called\n";
#endif
	setValid(true);
}

///////////////////////////////////////////////////////////////////////////////
// Copy constructor.
template<class T>
Tree<T>::Tree(const Tree<T> &copy):vector<Tree<T> >(copy){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Tree<T>::Tree(const Tree<T>&)' called\n";
#endif
	setData(copy.getData());
	setDepth(copy.getDepth());
	setCurrentLevel(copy.getCurrentLevel());
	setValid(copy.getValid());
}

///////////////////////////////////////////////////////////////////////////////
// Destructor.
template<class T>
Tree<T>::~Tree(){
#if (DEBUG_LEVEL >= 2)
	cerr << "'Tree<T>::~Tree()' called\n";
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Return depth from this node until the deepest leaf.
template<class T>
unsigned int Tree<T>::getDepth() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'unsigned int Tree<T>::getDepth() const' called\n";
#endif
	return depth;
}

///////////////////////////////////////////////////////////////////////////////
// Set new depth of this node.
template<class T>
void Tree<T>::setDepth(const unsigned int newDepth){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Tree<T>::setDepth(const unsigned int)' called\n";
#endif
	depth=newDepth;
}

///////////////////////////////////////////////////////////////////////////////
// Return level of this node.
template<class T>
unsigned int Tree<T>::getCurrentLevel() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'unsigned int Tree<T>::getCurrentLevel() const' called\n";
#endif
	return currentLevel;
}

///////////////////////////////////////////////////////////////////////////////
// Set new current level of this node.
template<class T>
void Tree<T>::setCurrentLevel(const unsigned int newCurrentLevel){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Tree<T>::setCurrentLevel(const unsigned int)' called\n";
#endif
	currentLevel=newCurrentLevel;
}

///////////////////////////////////////////////////////////////////////////////
// Return data stored in this node.
template<class T>
const T Tree<T>::getData() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'const T Tree<T>::getData() const' called\n";
#endif
	if(getValid()){
		return data;
	}
	else{
		return 0;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Set data to store in this node.
template<class T>
void Tree<T>::setData(const T &newData){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Tree<T>::setData(const T&)' called\n";
#endif
	data=newData;
	setValid(true);
}

///////////////////////////////////////////////////////////////////////////////
// Return validity of this node.
template<class T>
bool Tree<T>::getValid() const{
#if (DEBUG_LEVEL >= 2)
	cerr << "'bool Tree<T>::getValid() const' called\n";
#endif
	return valid;
}

///////////////////////////////////////////////////////////////////////////////
// Set validity of this node.
template<class T>
void Tree<T>::setValid(const bool newValid){
#if (DEBUG_LEVEL >= 2)
	cerr << "'void Tree<T>::setValid(const bool)' called\n";
#endif
	valid=newValid;
}

#endif

