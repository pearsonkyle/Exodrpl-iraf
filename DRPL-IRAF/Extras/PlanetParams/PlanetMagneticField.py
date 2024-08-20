# Derived from Vidotto et al 2011
# Calculate Planet Magnetic Field
from math import cos, pi, sqrt

R_s = 6.955e5 # solar radius in [km]
R_J = 7.1492e4 #jupiter radius in [km]


def getRp():
    return input("Enter R_p (Jup radii) = ")

def getRstar():
	return input("Enter radius of the host star(solar radii) = ")
	
def geta():
	return input("Enter distance star->planet (au) = ")
	
def geti():
	return input("Enter inclination(i) = ")
	
def getcadence():
	return input("Enter cadence of images (sec) = ")
	
def getTransitTime():
	return input("Enter transit duration(minutes) = ")

def getStarBfield():
	return input("Enter star's magnetic field magnitude(G) = ")

def PlanetMagneticField():
	Rp = float(getRp()*R_J)
	Rs = float(getRstar()*R_s)
	a = float(geta()*149597871)
	i = float(geti())
	ct = float(getcadence()*2.)
	td = float(getTransitTime()*60.)
	Bs = float(getStarBfield())
	
	t1 = sqrt(Rs**2 - (a*cos(i)/Rs)**2)
	t2 = 2*(ct/td)*(t1+Rp)+Rp
	tout = (Rs/(a*Rp))**3
	BpBs = tout*t2**3
	Bp = BpBs*Bs
	
	print "Your Bp =", Bp, "(G)"
	

