// CFGrammar.cpp -*- C++ -*-
#ifndef _CFGRAMMAR_CPP_
#define _CFGRAMMAR_CPP_

//#include<config.h>

#include<cstdio>
#include<iostream>
#include<sstream>
#include<cstring>
#include<vector>
#include<stack>
#include<fstream>

#include"CFGrammar.h"

///////////////////////////////////////////////////////////////////////////////
// Default constructor.
CFGrammar::CFGrammar():Grammar(){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'CFGrammar::CFGrammar()' called\n";
	#endif
}

///////////////////////////////////////////////////////////////////////////////
// Constructor setting the genotype structure of this mapper to newGenotype.
CFGrammar::CFGrammar(const Genotype &newGenotype):Grammar(newGenotype){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'CFGrammar::CFGrammar(const Genotype &)' called\n";
	#endif
}

///////////////////////////////////////////////////////////////////////////////
// Constructor setting the phenotype structure of this mapper to newPhenotype.
CFGrammar::CFGrammar(const Phenotype &newPhenotype):Grammar(newPhenotype){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'CFGrammar::CFGrammar(const Phenotype &)' called\n";
	#endif
}

///////////////////////////////////////////////////////////////////////////////
// Copy Constructor.
CFGrammar::CFGrammar(const CFGrammar& copy):Grammar(copy){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'CFGrammar::CFGrammar(const CFGrammar&)' called\n";
	#endif
	// Now must go through the copied grammar, and replace references to
	// the copy's lhs symbols with references to the new lhs symbols.
	iterator ruleIt=begin();
	Rule::iterator prodIt;
	Production::iterator symbIt;
	Rule *rulePtr;
	while(ruleIt!=end()){
		prodIt=ruleIt->begin();
		while(prodIt!=ruleIt->end()){
			symbIt=prodIt->begin();
			while(symbIt!=prodIt->end()){
				if((*symbIt)->getType()==NTSymbol){
					rulePtr=findRule(**symbIt);
					if(!rulePtr){
						/* Undefined NTSymbol - create new symbol */
						*symbIt=new Symbol(**symbIt);
					}
					else{
						/* Point to symbol's definition */
						*symbIt=rulePtr->lhs.back();
					}
				}
				symbIt++;
			}
			prodIt++;
		}
		ruleIt++;
	}
	// Invalidate phenotype - lower classes in hierarchy can always call
	// genotype2Phenotype() to regenerate it
	phenotype.clear();
	phenotype.setValid(false);
	// Don't copy derivation tree: procedure is too complex and expensive.
	// If tree is requested, it will be regenerated.
}

///////////////////////////////////////////////////////////////////////////////
// Destructor.
CFGrammar::~CFGrammar(){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'CFGrammar::~CFGrammar()' called\n";
	#endif
}

///////////////////////////////////////////////////////////////////////////////
// Opens the file whose name is passed as an argument, reads its contents onto
// a character string, and calls readBNFString.
bool CFGrammar::readBNFFile(const char *filename){
#if (DEBUG_LEVEL >= 2)
	cerr << "'CFGrammar::readBNFFile(const char *)' called\n";
#endif
	/*
	FILE *pFile;
	if(!(pFile=fopen(filename,"r"))){
		cerr << "Could not open grammar file " << filename << ".\nExecution aborted.\n";
		exit(1);
	}
	fseek(pFile,0,SEEK_END);
	int size = ftell(pFile);
	char program[size+1];
	strncpy(program,"",size);
	char line[1024];
	rewind(pFile);
	while(fgets(line,1024,pFile))
		strcat(program,line);
	fclose(pFile);
	strcat(program,"\n");
	return readBNFString(program);
	*/
	ifstream file(filename,ios::in|ios::binary);
	if(!file){
		cerr << "Could not open grammar file " << filename << ".\nExecution aborted.\n";
		exit(1);
	}
	char buffer[1024];
	string program;
	while(!file.eof()){
		file.read(buffer,1024);
		program.append(buffer,file.gcount());
	}
	file.close();
	program+="\n";
	return readBNFString(program.c_str());
}

///////////////////////////////////////////////////////////////////////////////
// Interface to the readBNFFile(const char *) method.
bool CFGrammar::readBNFFile(const string &filename){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'CFGrammar::readBNFFile(const string&)' called\n";
	#endif
	return readBNFFile(filename.c_str());
}

///////////////////////////////////////////////////////////////////////////////
// Reads in the BNF grammar specified by its argument text. Returns true if
// loading of grammar was successful, false otherwise.
bool CFGrammar::readBNFString(const char *stream){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'CFGrammar::readBNFString(const char *)' called\n";
	#endif
	// Delete the current grammar, if any
	clear();

	Rule newRule;				// Used to create new rules for grammar
	bool insertRule=false;			// If newRule is to be inserted onto grammar
	Rule *currentRule=NULL;			// Used in pass 2 to add productions to current rule
	Production newProduction;		// Used to create new productions for grammar
	Symbol newSymbol;			// Used to create new symbols for grammar
	Symbol newTokenSeparator;		// Used to create token separators for grammar
	unsigned int stream_size=strlen(stream);
	unsigned int ii,jj;			// Working variables
	char currentChar;			// Current char of input
	bool skip=false;			// SKip an iteration on parser (for escaped newlines)
	bool quoted=false;			// If current char is quoted
	bool non_terminal=false;		// If current text is a non-terminal symbol
	char separated=0;			// If there was a separator between previous token and current one
	vector<Symbol*> nonTerminals;		// Contains pointers to all defined non-terminals
	vector<Symbol*>::iterator nonTerminalsIt;
	string currentBuffer;			// Buffer used to add new symbols to grammar
	currentBuffer.reserve(stream_size);
	// States of parser
	#define START			0
	#define START_RULE		1
	#define LHS_READ		2
	#define PRODUCTION		3
	#define START_OF_LINE		4
	unsigned int state=START;// Current state of parser

	// ERROR FUNCTION
	#define ERROR_IN_GRAMMAR {cerr << "Grammar not loaded.\n"; clear(); setValidGrammar(false); phenotype.clear(); phenotype.setValid(false); return false;}

	//#define libGE_DEBUG_CFGRAMMAR_PARSER

	for(int pass=1;pass<=2;pass++){
		ii=jj=0;
		while(ii<=stream_size){
			if(ii<stream_size){
				currentChar=stream[ii];
			}
			else{
				// Simulate presence of endl at end of grammar
				currentChar='\n';
			}
			if(stream[ii]=='\\'){// Escape sequence
				ii++;
				if(ii>=stream_size){
					// Escape sequence as last char is invalid
					ERROR_IN_GRAMMAR;
				}
				else if((non_terminal)&&(stream[ii]!='\n')){
					// Only escaped newline allowed inside non-terminal
					cerr << "ERROR: Escape sequence detected inside non-terminal symbol.\n";
					ERROR_IN_GRAMMAR;
				}
				if(stream[ii]=='\''){// Single quote
					currentChar='\'';
				}
				else if(stream[ii]=='\"'){// Double quote
					currentChar='\"';
				}
				else if(stream[ii]=='\\'){// Backslash
					currentChar='\\';
				}
				else if(stream[ii]=='0'){// Null character
					currentChar='\0';
				}
				else if(stream[ii]=='a'){// Audible bell
					currentChar='\a';
				}
				else if(stream[ii]=='b'){// Backspace
					currentChar='\b';
				}
				else if(stream[ii]=='f'){// Formfeed
					currentChar='\f';
				}
				else if(stream[ii]=='n'){// Newline
					currentChar='\n';
				}
				else if(stream[ii]=='r'){// Carriage return
					currentChar='\r';
				}
				else if(stream[ii]=='t'){// Horizontal tab
					currentChar='\t';
				}
				else if(stream[ii]=='v'){// Vertical tab
					currentChar='\v';
				}
				else if(stream[ii]=='\n'){// Escaped newline
					// Ignore newline
					skip=true;
				}
				else if(stream[ii]=='\r'){// Escaped DOS return
					// Ignore newline
					skip=true;
					if(stream[++ii]!='\n'){
						cerr << "ERROR: \\r character not followed by \\n.\n";
						ERROR_IN_GRAMMAR;
					}
				}
				else{// Normal character
					currentChar=stream[ii];
				}
				if((!skip)&&(pass>1)){
					if(currentBuffer.empty()){
						newSymbol.setType(TSymbol);
					}
					currentBuffer+=currentChar;
				}
			}
			else{
				switch(state){
					case(START):
						if(currentChar=='\r'){
							break;// Ignore DOS newline first char
						}
						switch(currentChar){
							case ' ':// Ignore whitespaces
							case '\t':// Ignore tabs
							case '\n':// Ignore newlines
								break;
							case '<':// START OF RULE
								newSymbol.setType(NTSymbol);
								currentBuffer+=currentChar;
								state=START_RULE;
								break;
							default: // Illigal
								cerr << "ERROR: Character '" << currentChar << "' caused an error.\n";
								ERROR_IN_GRAMMAR;
						}
						break;
					case(START_RULE):// Read the lhs Non-terminal symbol
						if(currentChar=='\r'){
							break;// Ignore DOS newline first char
						}
						switch(currentChar){
							case '\n':// Newlines are illigal here
								cerr << "ERROR: Newline inside non-terminal.\n";
								ERROR_IN_GRAMMAR;
								break;
							case '>': // Possible end of non-terminal symbol
								currentBuffer+=currentChar;
								#ifdef libGE_DEBUG_CFGRAMMAR_PARSER
								cerr << "'" << currentBuffer << "'" << newSymbol.getType() << "\n";
								#endif
								newSymbol=currentBuffer.c_str();
								if(pass==1){
									// First pass
									// Check if new symbol definition
									insertRule=!(findRule(newSymbol));
									if(insertRule){
										// Create new rule for symbol
										newRule.clear();
										newRule.lhs.push_back(new Symbol(newSymbol));
										// Add to grammar
										nonTerminals.push_back(newRule.lhs.back());
									}
									else{// Existing symbol, do nothing
									}
								}
								else{
									// Second pass
									// Point currentRule to previously defined rule
									if(!(currentRule=findRule(newSymbol))){
										cerr << "ERROR: Grammar changed between parser passes.\n";
										ERROR_IN_GRAMMAR;
									}
								}
								// Reset the buffer
								currentBuffer.clear();
								// lhs for this rule has been read
								state=LHS_READ;
								break;
							default:// Check for non-escaped special characters
								if(((currentChar=='"')||(currentChar=='|')||(currentChar=='<'))){
									cerr << "ERROR: Invalid character '" << currentChar << "' inside non-terminal symbol.\n";
									ERROR_IN_GRAMMAR;
								}
								currentBuffer+=currentChar;
						}
						break;
					case(LHS_READ):// Must read ::= token
						if(currentChar=='\r'){
							break;// Ignore DOS newline first char
						}
						switch(currentChar){
							case ' ':// Ignore whitespaces
							case '\t':// Ignore tabs
							case '\n':// Ignore newlines
								break;
							case ':':// Part of ::= token
								currentBuffer+=currentChar;
								break;
							case '=':// Should be end of ::= token
								currentBuffer+=currentChar;
								if(currentBuffer!="::="){// Something other than ::= was read
									cerr << "ERROR: Token '" << currentBuffer << "' caused an error\n";
									ERROR_IN_GRAMMAR;
								}
								// Reset the buffer
								currentBuffer.clear();
								// START OF PRODUCTION
								newProduction.clear();
								state=PRODUCTION;
								break;
							default: // Illigal
								cerr << "ERROR: Character '" << currentChar << "' caused an error.\n";
								ERROR_IN_GRAMMAR;
						}
						break;
					case(PRODUCTION):// Read everything until | token or \n, or EOL
						if(currentChar=='\r'){
							break;// Ignore DOS newline first char
						}
						if(pass==1){
							if (currentChar=='\n')
								state=START_OF_LINE;
						}
						else switch(currentChar){
							case '|':// Possible end of production
								if(quoted){// Normal character
									currentBuffer+=currentChar;
									break;
								}
							case '\n':// End of production (and possibly rule)
								// Reset separator marker
								separated=0;
								if((currentBuffer.length())||(!newProduction.size())){// There is a symbol to add
									#ifdef libGE_DEBUG_CFGRAMMAR_PARSER
									cerr << "'" << currentBuffer << "'" << newSymbol.getType() << "\t";
									#endif
									if(!currentBuffer.length()){
										// No symbol exists; create terminal empty symbol
										newSymbol.setType(TSymbol);
									}
									if(non_terminal){// Current non-terminal symbol isn't finished
										cerr << "ERROR: Symbol '" << currentBuffer << "' caused an error.\n";
										ERROR_IN_GRAMMAR;
									}
									newSymbol=currentBuffer.c_str();
									if(newSymbol.getType()==NTSymbol){
										// Find rule that defines this symbol
										Rule *tempRule=findRule(newSymbol);
										if(tempRule){
											newProduction.push_back(tempRule->lhs.back());
										}
										else{
											// Undefined symbol, insert anyway
											newProduction.push_back(new Symbol(newSymbol));
										}
									}
									else{// Add terminal symbol
										newProduction.push_back(new Symbol(newSymbol));
									}
									// Reset the symbol
									newSymbol.clear();
								}
								else{// Empty token; ignored
									;
								}
								// END OF PRODUCTION
								#ifdef libGE_DEBUG_CFGRAMMAR_PARSER
								cerr << "\n";
								#endif
								// Add production to current rule
								currentRule->push_back(newProduction);

								// Reset the buffer
								currentBuffer.clear();
								if(currentChar=='\n')
									state=START_OF_LINE;
								else{
									// START OF PRODUCTION
									newProduction.clear();
								}
								break;
							case '<':// Possible start of non-terminal symbol
							case '>':// Possible end of non-terminal symbol
							case ' ':// Possible token separator
							case '\t':// Possible token separator
								if((quoted)// Normal character
								||(((currentChar==' ')||(currentChar=='\t'))&&(non_terminal))){// Spaces inside non-terminals are accepted
									currentBuffer+=currentChar;
									if(!non_terminal) newSymbol.setType(TSymbol);
									break;
								}
								if(currentChar=='>'){// This is also the end of a non-terminal symbol
									currentBuffer+=currentChar;
									non_terminal=false;
								}
								if(currentBuffer.length()){
									#ifdef libGE_DEBUG_CFGRAMMAR_PARSER
									cerr << "'" << currentBuffer << "'" << newSymbol.getType() << "\t";
									#endif
									if(non_terminal){// Current non-terminal symbol isn't finished
										cerr << "ERROR: Symbol " << currentBuffer << "' caused an error.\n";
										ERROR_IN_GRAMMAR;
									}
									if((currentChar==' ')||(currentChar=='\t')){// Token separator
										separated=1;
									}
									newSymbol=currentBuffer.c_str();

									if(newSymbol.getType()==NTSymbol){
										// Find rule that defines this symbol
										Rule *tempRule=findRule(newSymbol);
										if(tempRule){
											newProduction.push_back(tempRule->lhs.back());
										}
										else{
											// Undefined symbol, insert anyway
											newProduction.push_back(new Symbol(newSymbol));
										}
									}
									else{// Add terminal symbol
										newProduction.push_back(new Symbol(newSymbol));
									}
									// Reset the symbol
									newSymbol.clear();
								}
								else{// Empty buffer
									if(((currentChar==' ')||(currentChar=='\t'))// Token separator
											&&(!newProduction.empty())){
										// Probably a token separator after a non-terminal symbol
										separated=1;
									}
								}
								// Reset the buffer
								currentBuffer.clear();
								if(currentChar=='<'){// This is also the start of a non-terminal symbol
									// Special case; must create new Symbol here
									newSymbol.clear();
									newSymbol.setType(NTSymbol);
									currentBuffer+=currentChar;
									non_terminal=true;// Now reading a non-terminal symbol
									if(separated){// Insert a token separator
										separated=0;
										newTokenSeparator.clear();
										newTokenSeparator=" ";
										newTokenSeparator.setType(TSymbol);
										newProduction.push_back(new Symbol(newTokenSeparator));
										#ifdef libGE_DEBUG_CFGRAMMAR_PARSER
										cerr << "' '" << TSymbol << "\t";
										#endif
									}
								}
								break;
							default: // Add character to current buffer
								if(separated){// Insert a token separator
									separated=0;
									newTokenSeparator.clear();
									newTokenSeparator=" ";
									newTokenSeparator.setType(TSymbol);
									newProduction.push_back(new Symbol(newTokenSeparator));
									#ifdef libGE_DEBUG_CFGRAMMAR_PARSER
									cerr << "' '" << TSymbol << "\t";
									#endif
								}
								if(currentChar=='"'){// Start (or end) quoted section
									quoted=!quoted;
									newSymbol.setType(TSymbol);
									break;
								}
								if(!currentBuffer.length()){
									newSymbol.setType(TSymbol);
								}
								currentBuffer+=currentChar;
						}
						break;
					case(START_OF_LINE):
						if(currentChar=='\r'){
							break;// Ignore DOS newline first char
						}
						switch(currentChar){
							case ' ':// Ignore whitespaces
							case '\t':// Ignore tabs
							case '\n':// Ignore newlines
								break;
							case '|':// Start of new production
								state=PRODUCTION;
								if(pass==2){
									// START OF PRODUCTION
									newProduction.clear();
								}
								break;
							case '<':// Start of lhs non-terminal symbol
								#ifdef libGE_DEBUG_CFGRAMMAR_PARSER
								cerr << "\n";
								#endif
								// END OF RULE
								if(pass==1){
									// Add current rule
									if(insertRule){
										push_back(newRule);
									}
								}
								// START OF RULE
								newSymbol.setType(NTSymbol);
								currentBuffer+=currentChar;
								state=START_RULE;
								break;
							default: // Illigal
								cerr << "ERROR: Detected line starting with terminal symbol.\n";
								ERROR_IN_GRAMMAR;
						}
						break;
					default://Impossible error, quit the program now!
						cerr << "Internal error.\nPlease report error 'Impossible state in CFGrammar parser' to " << PACKAGE_BUGREPORT << "\n";
						exit(0);
				}
			}
				skip=false;
			ii++;
		}
		// END OF PASS
		if(state!=START_OF_LINE){// This must be the state of the parser
			cerr << "Parsing error reading grammar.\n";
			ERROR_IN_GRAMMAR;
		}
		if(pass==1){
			// Add current rule
			if(insertRule){
				push_back(newRule);
			}
		}
	}
	#ifdef libGE_DEBUG_CFGRAMMAR_PARSER
	cerr << "\n";
	#endif

	updateRuleFields();

	setValidGrammar(true);
	genotype2Phenotype();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Interface to the readBNFString(const char *) method.
bool CFGrammar::readBNFString(const string &stream){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'CFGrammar::readBNFString(const string&)' called\n";
	#endif
	return readBNFString(stream.c_str());
}

///////////////////////////////////////////////////////////////////////////////
// Reads in the BNF grammar-part specified by its argument text, and adds it to
// the current grammar. Returns true if loading of new grammar part was
// successful, false otherwise.
bool CFGrammar::addBNFString(const char *stream){
	// FIXME Slow implementation.
	#if (DEBUG_LEVEL >= 2)
	cerr << "'CFGrammar::addBNFString(const char *)' called\n";
	#endif
	// Copy current grammar
	vector<Rule> grammarCopy(*this);
	// Create appended grammar string
	ostringstream newGrammarStream;
	outputBNF(newGrammarStream);
	string newGrammar(newGrammarStream.str());
	newGrammar.append(stream);
	// Read new grammar
	if(!readBNFString(newGrammar.c_str())){
		// Restore previous state of Mapper
		readBNFString(newGrammarStream.str().c_str());
		return false;
	}
	return true;

}

///////////////////////////////////////////////////////////////////////////////
// Interface to the addBNFString(const char *) method.
bool CFGrammar::addBNFString(const string &stream){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'CFGrammar::addBNFString(const string&)' called\n";
	#endif
	return addBNFString(stream.c_str());
}

///////////////////////////////////////////////////////////////////////////////
// Pretty print the current BNF grammar.
void CFGrammar::outputBNF(ostream& stream){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'CFGrammar::outputBNF(ostream&)' called\n";
	#endif
	if(!getValidGrammar()){
		return;
	}
	iterator r_it=begin();
	while(r_it!=end()){
		stream << *(r_it->lhs.back()) << " ::=";
		// go through productions
		Rule::iterator p_it=r_it->begin();
		while(p_it!=r_it->end()){
			// go through symbols
			Production::iterator s_it=p_it->begin();
			while(s_it!=p_it->end()){
				stream << **s_it;
				// get next symbol
				s_it++;
			}
			// get next production
			p_it++;
			if(p_it!=r_it->end())
				stream << " | ";
		}
		stream << '\n';
		// get next rule
		r_it++;
	};
}

///////////////////////////////////////////////////////////////////////////////
// Returns the address of the rule defining the argument non-terminal symbol,
// if it exists; otherwise returns NULL.
Rule* CFGrammar::findRule(const Symbol &nonterminal){
	#if (DEBUG_LEVEL >= 2)
	cerr << "'Rule* CFGrammar::findRule(const Symbol &)' called\n";
	#endif
	iterator ruleIt=begin();
	while(ruleIt!=end()){
		if(*(ruleIt->lhs.back())==nonterminal)
			return &(*ruleIt);
		ruleIt++;
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Returns the calculated recursive nature of the Rule passed as argument,
// and updates its minimum mapping depth (minimumDepth)
bool CFGrammar::isRecursive(vector<Symbol*> &visitedRules, Rule *currentRule){
	Rule::iterator prodIt=currentRule->begin();
	Production::iterator symbIt;
	vector<Symbol*>::iterator visitedRulesIt=visitedRules.begin();
	Rule *rulePtr;
	bool result;

	// DON'T DO IT - otherwise minimumDepth is not updated properly
	// If this rule has already been labeled, exit
	//if(currentRule->getRecursive()!=SI_Undef){
	//	return currentRule->getRecursive();
	//}

	// Check if this is a recursive call to a previously visited rule
	while(visitedRulesIt!=visitedRules.end()){
		if(*visitedRulesIt==currentRule->lhs.back()){
			currentRule->setRecursive(true);
			return true;
		}
		visitedRulesIt++;
	}

	// Go through each production in the rule
	while(prodIt!=currentRule->end()){
		prodIt->setMinimumDepth(0);
		symbIt=prodIt->begin();
		// Go through each symbol in the production
		while(symbIt!=prodIt->end()){
			if((*symbIt)->getType()==NTSymbol){// Symbol is non-terminal, possible recursion
				rulePtr=findRule(**symbIt);// Find defining rule
				if(rulePtr){// Symbol is defined
					// Recursive call
					visitedRules.push_back(currentRule->lhs.back());
					result=isRecursive(visitedRules,rulePtr);
					visitedRules.pop_back();
					if(result){// Production is recursive
						// Mark production as recursive
						prodIt->setRecursive(true);
						// Mark current rule also as recursive
						currentRule->setRecursive(true);
					}
					if(prodIt->getMinimumDepth()<(rulePtr->getMinimumDepth()+1)){
						prodIt->setMinimumDepth(rulePtr->getMinimumDepth()+1);
					}
				}
				else{ // Non-defined non-terminal symbols are considered terminal symbols
					if(prodIt->getMinimumDepth()<1){
						prodIt->setMinimumDepth(1);
					}
				}
			}
			else{// Terminal symbol
				if(prodIt->getMinimumDepth()<1){
					prodIt->setMinimumDepth(1);
				}
			}
			symbIt++;
		}
		//if(prodIt->getRecursive()==SI_Undef){// Production is not recursive
		//	prodIt->setRecursive(SI_NonRec);
		//}
		if(currentRule->getMinimumDepth()>prodIt->getMinimumDepth()){// Update rule minimumDepth
			currentRule->setMinimumDepth(prodIt->getMinimumDepth());
		}
		prodIt++;
	}
	//if(currentRule->getRecursive()!=SI_Rec){// Rule is not recursive, as it contains no recursive productions
	//	currentRule->setRecursive(SI_NonRec);
	//	return SI_NonRec;
	//}
	//return SI_Rec;
	return currentRule->getRecursive();
}

///////////////////////////////////////////////////////////////////////////////
// Update recursive and minimumDepth fields for every Rule
// and Production in grammar.
void CFGrammar::updateRuleFields(){
	vector<Symbol*> visitedRules;
	iterator ruleIt=begin();

	clearRuleFields();

	// Go through each rule in the grammar
	while(ruleIt!=end()){
		visitedRules.clear();
		ruleIt->setRecursive(isRecursive(visitedRules,&(*ruleIt)));
		ruleIt++;
	}
	// Second pass, to correctly update all recursive rules
	ruleIt=begin();
	while(ruleIt!=end()){
		visitedRules.clear();
		ruleIt->setRecursive(isRecursive(visitedRules,&(*ruleIt)));
		ruleIt++;
	}
/*
ruleIt=begin();
Rule::iterator prodIt;
while(ruleIt!=end()){
 cerr << *(ruleIt->lhs.back()) << "(" << ruleIt->getMinimumDepth() << ")\n";
 prodIt=ruleIt->begin();
 while(prodIt!=ruleIt->end()){
   cerr << " (" << prodIt->getMinimumDepth() << ")";
   prodIt++;
 }
 cerr << "\n";
 ruleIt++;
}
*/
}

///////////////////////////////////////////////////////////////////////////////
// Update recursive and minimumDepth fields for every Rule
// and Production in grammar.
void CFGrammar::clearRuleFields(){
	iterator ruleIt=begin();
	// Reset minimum depths and recursion fields
	while(ruleIt!=end()){
		ruleIt->setMinimumDepth(INT_MAX>>1);
		ruleIt->setRecursive(false);
		ruleIt++;
	}
}

#endif

