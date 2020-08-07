local sqrt = math.sqrt

X = 0.0
V = 0.0
currTime = 0.0

numFitCase = 20;
startValuesArray = {
0.50, 0.67,
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
0.58, -0.35
}

currFitCase = 0
sumFitCaseTimes = 0.0
hitCount = 0
maxTime = 7.5
overMaxTimePenalty = 10.0
maxHitEuclError = 0.01
currEuclError = 0.0

timeStep = 0.02
posForceVelChange = 0.0
netForceVelChange = 0.0
velocityChage = 0.0

function initCart()
  forceToMassRatio = 0.5
  posForceVelChange = (forceToMassRatio * timeStep)
  negForceVelChange = ((-1.0) * posForceVelChange)
  currFitCase = 0
  sumFitCaseTimes = 0.0
  hitCount = 0
end

function resetCart()
	currTime = 0.0
	if currFitCase < numFitCase then
		X = startValuesArray[(currFitCase * 2) + 1]
		V = startValuesArray[(currFitCase * 2) + 2]
	end
	currEuclError = sqrt((X * X) + (V * V))
end

function stepSim()
	X = X + (V * timeStep)
	V = V +  velocityChange
	currTime = currTime + timeStep
	currEuclError = sqrt((X * X) + (V * V))

 	-- io.write(currTime, "\t", X, "\t", velocityChange, "\t", V, "\t", currEuclError, "\n")
	
	if currEuclError <= maxHitEuclError then
		if currTime <= maxTime then
			sumFitCaseTimes = sumFitCaseTimes + currTime
			hitCount = hitCount + 1
       			currFitCase = currFitCase + 1
		        resetCart()
		end
	else
		if currTime >= maxTime then
			sumFitCaseTimes = sumFitCaseTimes + overMaxTimePenalty
			currFitCase = currFitCase + 1
			resetCart()
		end
	end
end

function DIV (x,y)
	if y == 0 then
		return 1.0
	else
		return (x / y)
	end
end

function ABS (x)
	if x > 0.0 then
		return x
	else
		return (x * -1.0)
	end
end

function GT (x,y)
	if x > y then
		return 1.0
	else
		return -1.0
	end
end


-- initCart()
-- resetCart()
-- while currFitCase < numFitCase do
-- 	if GT(((-1.0) * X), (V * (ABS(V)))) > 0.0 then
-- 		velocityChange = posForceVelChange
-- 	else
-- 		velocityChange = negForceVelChange
-- 	end
-- 	stepSim()
-- end
-- print(sumFitCaseTimes)

