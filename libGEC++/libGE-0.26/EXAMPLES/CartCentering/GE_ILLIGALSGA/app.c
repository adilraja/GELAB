// app.c -*- C -*-
#ifndef _APP_C_
#define _APP_C_

#include <stdlib.h>
#include <string.h>
#include "external.h"
#include <GE/ge.h>

typedef float Real;

//Buffers for start and end code of the individual.c file
char CCstart[3000];
char CCend[3000];

application()
{
}


app_data()
{
}


app_free()
{
}


app_init()
{
	/* Init GE mapper */
	/*Set maximum number of wrapping events per mapping*/
	GE_ILLIGALSGA_setMaxWraps(10);
	/*Load grammar*/
	if (!GE_ILLIGALSGA_readBNFFile("grammar.bnf")){
		fprintf(stderr,"Call to GE_ILLIGALSGA_readBNF failed.\n");
		fprintf(stderr,"Execution aborted.\n");
		exit(0);
	}
	/*Print grammar onto screen*/
	GE_ILLIGALSGA_outputBNF();

	char buffer[1000];
	FILE *c_code;

	/* Read code start and end files */
	strcpy(CCstart,"");
	if(!(c_code=fopen("cartcenterstart.c","r"))){
	        fprintf(stderr, "Could not read cartcenterstart.c\n");
		fprintf(stderr, "Execution aborted.\n");
		exit(0);
	}
	while(fgets(buffer,1000,c_code))
		strcat(CCstart,buffer);
	fclose(c_code);
	strcpy(CCend,"");

	if(!(c_code=fopen("cartcenterend.c","r"))){
	        fprintf(stderr, "Could not read cartcenterend.c\n");
		fprintf(stderr, "Execution aborted.\n");
		exit(0);
	}
	while(fgets(buffer,1000,c_code))
		strcat(CCend,buffer);
	fclose(c_code);
}


app_initreport()
{
}


app_malloc()
{
}


app_report()
{
}


app_stats(pop)
struct individual *pop;
{
}


objfunc(critter)
struct individual *critter;
{
	/*Assign critter to mapper, using lchrom and 8 bits per gene*/
	GE_ILLIGALSGA_Mapper(critter,lchrom,8);
	if(GE_ILLIGALSGA_validPhenotype()){
		char *characters;
		int size,i;
		FILE *file;
		Real fitness = 0.0;
		/*Create output file*/
		if(!(file=fopen("individual.c","w"))){
			fprintf(stderr,"Could not open individual.c.\n");
			fprintf(stderr,"Execution aborted.\n");
			exit(0);
		}

		//Write start buffer to file
		fprintf(file,"%s",CCstart);
		//Write phenotype code to file
		size=GE_ILLIGALSGA_getPhenotype(&characters);
		for(i=0;i<size;i++){
			fprintf(file,"%c",characters[i]);
		}
		fprintf(file,"\n");
		//Write end buffer to file
		fprintf(file,"%s",CCend);
		fclose(file);

#if defined GECART_USE_TCC_COMP
		//Compile and execute file with TCC
		if(system("tcc -pipe individual.c GEcart-tcc.o -lm &&\
                                ./a.out > result")==-1){
		        fprintf(stderr, "Compilation or execution failed.\n");
			fprintf(stderr, "Execution aborted.\n");
			exit(0);
		}
#else
		//Compile and execute file with GCC
		if(system("gcc -pipe individual.c GEcart.o -lm &&\
                                ./a.out > result")==-1){
        		fprintf(stderr, "Compilation or execution failed.\n");
			fprintf(stderr, "Execution aborted.\n");
			exit(0);
		}
#endif

		/*Open result file, containing fitness score*/
		if(!(file=fopen("result","r"))){
			fprintf(stderr,"Could not open result file.\n");
			fprintf(stderr,"Execution aborted.\n");
			exit(0);
		}
		fscanf(file,"%f",&fitness);
		fclose(file);

		// Invert fitness because GA's maximise fitness.
		if (fitness > 0.0)
		{
		  fitness = 1.0 / fitness;
		}

		critter->fitness = fitness;
	}
	else
		critter->fitness=0;
}

#endif

