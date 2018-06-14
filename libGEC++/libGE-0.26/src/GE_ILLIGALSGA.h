/*
Allocates memory for an integer array, stores the current genotype in that
array, and returns the address of the allocated memory in the argument pointer,
as well as its size as the return value. The user is responsible for freeing
the allocated memory.
*/
extern int GE_ILLIGALSGA_getGenotype(int **);

/*
Allocates memory for a NULL-terminated character array, stores the current
phenotype in that array, and returns the address of the allocated memory in the
argument pointer, as well as its size as the return value. The user is
responsible for freeing the allocated memory.
*/
extern int GE_ILLIGALSGA_getPhenotype(char **);

/*
Returns the validity of the phenotype contained in the static mapper.
*/
extern int GE_ILLIGALSGA_validPhenotype();

/*
Sets the number of allowed wrapping events for the static mapper.
*/
extern void GE_ILLIGALSGA_setMaxWraps(int);

/*
Interface to the readBNFFile(char *) method in CFGrammar, for the static
mapper.
*/
extern int GE_ILLIGALSGA_readBNFFile(char *);

/*
Interface to the readBNFString(char *) method in CFGrammar, for the static
mapper.
*/
extern int GE_ILLIGALSGA_readBNFString(char *);

/*
Interface to the outputBNF(ostream&) method in CFGrammar, for the static
mapper.
*/
extern void GE_ILLIGALSGA_outputBNF();

/*
Accepts an sga-c chromosome, transforms it into a libGE Genotype structure, and
assigns it to the static mapper.
*/
extern void GE_ILLIGALSGA_Mapper(struct individual *critter, int lchrom, int bpg);

