variable xvals = Double_Type [194];
variable yvals = Double_Type [194];
variable Class = Integer_Type [194];
variable Evolved = Double_Type [194];
variable FitnessCases=194;

define initVals()
{
  variable i,j;
  variable angle = Double_Type;
  variable radius = Double_Type;
  variable varx = Double_Type;
  variable vary = Double_Type;

  for (i=0,j=0; i<FitnessCases/2; i++,j++) 
    {
      angle = i * PI  / 16.0;
      radius = 6.5 * (104 - i) / 104.0;
      varx = radius * sin(angle);
      vary = radius * cos(angle);
      xvals[j] = varx;
      yvals[j] = vary;
      Class[j]=1;
      j++;

      xvals[j] = -varx;
      yvals[j] = -vary;
      Class[j]= 0;

    }
}

define AssignFitness()
{
  variable i,hits = Integer_Type;
  hits=0;
  for(i=0;i<FitnessCases;i++)
  {
     if(((Evolved[i] > 0) and (Class[i] == 1)) or ((Evolved[i] <= 0) and (Class[i] == 0)))
     {
      hits++;
     }
  }
  return hits;
}


define if_cond(ex1,ex2,ex3,ex4)
{
    if(ex1<=ex2)
     return ex3;
    else
     return ex4;
}


define pdiv(a1,a2)
{
  if(a2 == 0)
    return 0;
  else
    return  a1/a2;
}

define myadd(a1,a2)
{
  return a1+a2;
}

define mysub(a1,a2)
{
   return  a1-a2;
}

define mymul(a1,a2)
{
  return  a1*a2;
}

