#Calculate Planet radius from Rp/R* and R*
from math import sqrt

R_s = 6.955e5 # solar radius in [km]
R_J = 7.1492e4 #jupiter radius in [km]

def getRpRs():
    return input("Enter R_p/R* = ")

def getRpRsError():
	return input("Enter R_p/R* error = ")

def getRstar():
	return input("Enter radius of the host star(solar radii) = ")
	
def getRstarError():
	return input("Enter error on the radius of host star = ")

def PlanetRadius():
	ratio = getRpRs()
	ratioError = getRpRsError() 
	rstar = getRstar()*R_s #km
	rstarError = getRstarError()*R_s #km
	
	rplanet = ratio*rstar #in km
	
	term1 = (rstar**2)*(ratioError**2)
	term2 = (ratio**2)*(rstarError**2)
	radius = rplanet*(1/R_J) # in jup radii
	error = sqrt(term1+term2)*(1/R_J) # in jup radii
	print "Your planet radius =",radius,"+-",error, "R_J "
	



	
	
