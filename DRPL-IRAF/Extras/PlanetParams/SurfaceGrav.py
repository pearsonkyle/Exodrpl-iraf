# Surface Graviational Acceleration by Southworth, Wheatley, Sams 2007

# Propagation when converting the error from cm/s to a log of cgs units may be incorrect
# If you have any 

from math import sin, pi, sqrt, log10, log
from mpmath import cot, csc

R_s = 6.955e10 # solar radius in [cm]
R_J = 7.1492e9 # jupiter radius in [cm]

def getRp():
	R = []
	R.append(input("Enter (R_p) Planet Radius(Jup radii) = ")*R_J)
	R.append(input("Enter (R_p) Planet Radius ERROR = ")*R_J)
	return R

def geta():
	A = []
	A.append(input("Enter (a) Distance to Planet (AU) = ")*1.49597871e13)
	A.append(input("Enter (a) Distance to Planet ERROR = ")*1.49597871e13)
	return A
	
def geti():
	I = []
	I.append(input("Enter (i) inclination(deg) = ")*2*pi/360) 
	I.append(input("Enter (i) inclination ERROR = ")*2*pi/360)
	return I
	
def getPeriod():
	P = []
	P.append(input("Enter (P) orbital period(days) = ")*24*60*60)
	P.append(input("Enter (P) orbital period ERROR = ")*24*60*60)
	return P

def gete():
	E = []
	E.append(input("Enter (e) eccentricity = "))
	E.append(input("Enter (e) eccentricity ERROR = "))
	return E
	
def getK():
	K = []
	K.append(input("Enter (K*) stellar velocity amp (m/s) = ")*100)
	K.append(input("Enter (K*) stellar velocity amp ERROR = ")*100)
	return K

def SurfaceGrav():
	a = geta()			# cm
	Rp = getRp()		# cm
	i = geti() 	 		# in radians
	P = getPeriod()	 	# in seconds
	e = gete()
	K = getK()			# in cm/s
	
	gb = []
	
	t1 = (2.*pi)/P[0]
	aR = a[0]/Rp[0]
	t2 = aR**2
	t3 = K[0]*sqrt(1-e[0]**2)/sin(i[0])
	
	Perr = (-2*pi*a[0]*a[0]*sqrt(1-e[0]*e[0])*K[0]/(P[0]*P[0]*Rp[0]*Rp[0]*sin(i[0])))**2
	aerr = (2*a[0]*2*pi*sqrt(1-e[0]*e[0])*K[0]/(P[0]*Rp[0]*Rp[0]*sin(i[0])))**2
	Rerr = (-2*2*pi*a[0]*a[0]*sqrt(1-e[0]*e[0])*K[0]/((Rp[0]**3.)*P[0]*sin(i[0])))**2
	eerr = (2*pi*a[0]*a[0]*K[0]*-1.*e[0]/(P[0]*Rp[0]*Rp[0]*sin(i[0])*sqrt(1-e[0]*e[0])))**2
	Kerr = (2*pi*a[0]*a[0]*sqrt(1-e[0]*e[0])/(P[0]*Rp[0]*Rp[0]*sin(i[0])))**2
	ierr = (2*pi*a[0]*a[0]*sqrt(1-e[0]*e[0])*K[0]*-1.*cot(i[0])*csc(i[0])/(P[0]*Rp[0]*Rp[0]))**2
	
	error = sqrt(Perr*(P[1]**2.) + aerr*(a[1]**2.) + Rerr*(Rp[1]**2.) + eerr*(e[1]**2.) + Kerr*(K[1]**2.) + ierr*(i[1]**2.))
	
	gb.append(t1*t2*t3)
	gb.append(error)
	
	print "Your surface gravitational accel =",gb[0],"+-",gb[1],"(cm/s^2)"
	print "Your log(g) =", log10(gb[0]),"+-",sqrt(1./(gb[1]*log(10))), "(cgs)"
