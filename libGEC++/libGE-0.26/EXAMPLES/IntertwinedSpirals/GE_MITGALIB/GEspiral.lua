
sin = math.sin
cos = math.cos
tan = math.tan
exp = math.exp


xvals = {}
yvals = {}
Class = {}
Evolved = {}
FitnessCases = 194;

function initVals()

	i = 0
  	j = 0
	angle = 0.0
  	radius = 0.0
  	varx = 0.0
  	vary = 0.0

  	for i=0,(FitnessCases/2),1 do
       		angle = i * math.pi  / 16.0;
      		radius = 6.5 * (104 - i) / 104.0;
      		varx = radius * sin(angle);
      		vary = radius * cos(angle);
      		xvals[j] = varx;
      		yvals[j] = vary;
      		Class[j] = 1;
      		j = j + 1;

      		xvals[j] = ((-1.0) * varx);
      		yvals[j] = ((-1.0) * vary);
      		Class[j]= 0;
		j = j + 1
	end

end


function AssignFitness()

	i = 0
	hits = 0

	for i=0,(FitnessCases - 1),1 do
		if ((Evolved[i] > 0) and (Class[i] == 1)) then
			hits = hits + 1
		elseif ((Evolved[i] <= 0) and (Class[i] == 0)) then
			hits = hits + 1
		end
	
  	end

	return hits;

end


function if_cond(ex1,ex2,ex3,ex4)

	if ex1 <= ex2 then
     		return ex3
    	else
     		return ex4
	end

end


function pdiv(a1,a2)

	if a2 == 0 then
		return 0
  	else
    		return a1/a2
	end

end


function myadd(a1,a2)

  return a1 + a2

end


function mysub(a1,a2)

   return  a1 - a2
end


function mymul(a1,a2)

  return  a1 * a2

end
