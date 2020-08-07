#include <stdio.h>
#include <math.h>
#include "GEspiral.h"

extern double xvals[194];
extern double yvals[194];
extern int Evolved[194];
int main()
{
 initVals();
 int i;
 double temp,x,y;
 for(i=0;i<194;i++)
   {
     x=xvals[i];
     y=yvals[i];
     temp=
