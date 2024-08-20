# calculate the timing difference between optical and near-uv ingress
# based on Vidotto et al 2011

from math import cos, pi, sqrt, pow

R_s = 6.955e5 # solar radius in [km]
R_J = 7.1492e4 #jupiter radius in [km]
AU = 149597871 # Astronomical unit in [km]


def getRp():
    return input("Enter R_p (Jup radii) = ")

def getRstar():
	return input("Enter radius of the host star(solar radii) = ")
	
def geta():
	return input("Enter distance from star->planet (au) = ")
	
def geti():
	return input("Enter inclination(i) = ")
	
def getTransitTime():
	return input("Enter transit duration(minutes) = ")

def getStarBfield():
	return input("Enter star's magnetic field magnitude(G) = ")

def getBfield():
	return input("Enter planets's magnetic field magnitude(G) = ")
	
def getBratio():
	return input("Enter the Magnetic field ratio from Vidotto's paper (f) % = ")

def VidottoTime():
	Rp = getRp()*R_J
	Rs = getRstar()*R_s
	a = geta()*AU
	i = geti()
	td = getTransitTime()*60
	Bs = float(getStarBfield())
	Bp = float(getBfield())
	
	BR = Bp/Bs
	
	top = pow(BR,(1./3.))*a*Rp*td/Rs - Rp*td
	bot = 2*(sqrt(Rs**2-(a*cos(i)/Rs)**2)+Rp)
	
	
	print "Your Vidotto timing difference between Optical and near-uv =",top/bot,"(seconds)"
	print "Your Vidotto timing difference between Optical and near-uv =",(top/bot)/60,"(minutes)"
	
def VidottoTimeWith():
	Rp = getRp()*R_J
	Rs = getRstar()*R_s
	a = geta()*AU
	i = geti()
	td = getTransitTime()*60
	f = getBratio()/100
	
	top = (f)**(1./3.)*a*Rp*td/Rs - Rp*td
	bot = 2*(sqrt(Rs**2-(a*cos(i)/Rs)**2)+Rp)
	
	print "Your Vidotto timing difference between Optical and near-uv =",top/bot,"(seconds)"
	print "Your Vidotto timing difference between Optical and near-uv =",(top/bot)/60,"(minutes)"
