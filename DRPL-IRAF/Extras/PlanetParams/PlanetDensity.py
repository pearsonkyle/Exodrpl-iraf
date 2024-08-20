# Calculate density of planet
from math import pi, sqrt

M_j = 1.89865e30 # jupiter radii in [g]
R_J = 7149200000 #jupiter radius in [cm]

def getMp():
	M = []
	M.append(input("Enter (M_b) mass of planet(jupiter mass) = ")*M_j)
	M.append(input("Enter (M_b) mass of planet ERROR = ")*M_j)
	return M
	
def getRp():
	R = []
	R.append(input("Enter (R_p) Planet Radius(Jup radii) = ")*R_J)
	R.append(input("Enter (R_p) Planet Radius ERROR = ")*R_J)
	return R
	
def PlanetDensity():
	print "Calculating planetary density..."
	Rp = getRp()
	Mp = getMp()
	
	dens = []
	
	d = Mp[0]/((4./3.)*pi*Rp[0]**3.)
	dens.append(d)
	
	Merr = 1/((4./3.)*pi*Rp[0]**3.)
	Rerr = -3.*Mp[0]/((4./3.)*pi*Rp[0]**4)
	
	error = sqrt( Merr**2*Mp[1]**2 + Rerr**2*Rp[1] )
	dens.append(error)
	
	print "Your density =",dens[0],"+-",dens[1],"g/cm^3"
	
