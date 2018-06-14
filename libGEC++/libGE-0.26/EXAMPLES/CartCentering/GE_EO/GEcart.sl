

variable X = 0.0;
variable V = 0.0;
variable currTime = 0.0;

variable numFitCase = 20;
variable startValuesArray =
[0.50, 0.67,
-0.65, 0.40,
-0.16, -0.57,
0.10, 0.50,
-0.71,  0.66,
0.43, 0.01,
-0.28, -0.71,
0.27, -0.73,
-0.50, 0.34,
-0.57, 0.32,
0.43, -0.69,
-0.52, -0.16,
-0.33, -0.21,
-0.16, -0.06,
0.71, -0.69,
-0.04, -0.63,
0.39, 0.70,
-0.52, -0.42,
-0.59, 0.38,
0.58, -0.35];


variable currFitCase = 0;
variable sumFitCaseTimes = 0.0;
variable hitCount = 0;
variable maxTime = 7.5;
variable overMaxTimePenalty = 10.0;
variable maxHitEuclError = 0.01;
variable currEuclError = 0.0;

variable timeStep = 0.02;
variable posForceVelChange;
variable negForceVelChange;
variable velocityChange = 0.0;


define resetCart()
{
  currTime = 0.0;
  if (currFitCase < numFitCase)
  {
    X = startValuesArray[currFitCase * 2];
    V = startValuesArray[(currFitCase * 2) + 1];
  }
  currEuclError = sqrt((X * X) + (V * V));
}

define initCart()
{
  variable forceToMassRatio = 0.5;
  posForceVelChange = (forceToMassRatio * timeStep);
  negForceVelChange = ((-1.0) * posForceVelChange);
  currFitCase = 0;
  sumFitCaseTimes = 0.0;
  hitCount = 0;
}


% define readStartValues(fname)
% {
%   variable i = 0;
%   variable line;
% 
%   variable ifs;
%   ifs=fopen(fname,"r");
%   if (ifs==NULL)
%     verror ("%s failed to open", fname);
%   
%   while(ifs != NULL)
%   {
%     if (-1 != fgets(&line, ifs))
%     {
% 	fprintf(stdout,
%                 "val %d = %s\n",
%                 i,	
%                 line);
%       % Need to onvert line to double.
%       % ??
%
%         i++;
%     }
%     else
%     {
%        verror("Error reading from file.");
%     }
%   }
% 
%   fclose(fname);
% }

define stepSim()
{
  X += (V * timeStep);
  V += velocityChange;
  currTime += timeStep;
  currEuclError = sqrt((X * X) + (V * V));

%  % stack overflow error occurred without the () = here.
%  () = printf("%f %f %f %f %f\n",
%         currTime,
%  	 X,
%  	 velocityChange,
%         V,
%         currEuclError);

  if (currEuclError <= maxHitEuclError)
  {
     if (currTime <= maxTime)
     {
       sumFitCaseTimes += currTime;
       ++hitCount;
       ++currFitCase;
       resetCart();
     }
  }
  else
  {
    if (currTime >= maxTime)
    {
      sumFitCaseTimes += overMaxTimePenalty;
      ++currFitCase;
      resetCart();
    }
  }
}

define DIV(n, d){
  if(d != 0.0){
    return (n/d);
  }
  return (1.0);
};

define GT(lhs, rhs){
  if(lhs>rhs){
    return (1.0);
  }
  return (-1.0);
};

define ABS(x){
  if(x<0){
    return (x*(-1));
  }
  return (x);
};
