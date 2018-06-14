// app.c -*- C -*-
#ifndef _APP_C_
#define _APP_C_

#include "external.h"
#include <GE/ge.h>

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
		int fitness;
		/*Create output file*/
		if(!(file=fopen("individual.c","w"))){
			fprintf(stderr,"Could not open individual.c.\n");
			fprintf(stderr,"Execution aborted.\n");
			exit(0);
		}
		/*Write start code to file*/
		fprintf(file,"int _energy;\nint  _picked_up;\n");
		fprintf(file,"int main(){\ninitGEant();\ninitGEtrail();\n");
		fprintf(file,"ReadTrailGEtrail(\"santafe.trl\");\n");
		fprintf(file,"while(_energy>0){");
		/*Write phenotype code to file*/
		size=GE_ILLIGALSGA_getPhenotype(&characters);
		for(i=0;i<size;i++){
			fprintf(file,"%c",characters[i]);
		}
		fprintf(file,"\n");
		/*Write end code to file*/
		fprintf(file,"}\nprintf(\"%%d\\n\",_picked_up);\n}\n");
		fclose(file);
		/*Compile and execute file with GCC*/
		if(system("gcc -pipe individual.c GEant.o\
				GEtrail.o && ./a.out > result")==-1){
			fprintf(stderr,"Compilation or execution failed.\n");
			fprintf(stderr,"Execution aborted.\n");
			exit(0);
		}
		/*Open result file, containing fitness score*/
		if(!(file=fopen("result","r"))){
			fprintf(stderr,"Could not open result file.\n");
			fprintf(stderr,"Execution aborted.\n");
			exit(0);
		}
		fscanf(file,"%d",&fitness);
		fclose(file);
		critter->fitness=fitness;
	}
	else
		critter->fitness=0;
}

#endif

