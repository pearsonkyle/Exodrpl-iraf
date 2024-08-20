# Calculate Mass of Planet from Seager (2011)
from math import sin, pi, sqrt
from mpmath import cot, csc


yr  = 365.24	 # year in [days]
M_s = 1.988547e33  # solar mass in [g]
M_j = 1.89865e30 # jupiter radii in [g]

	
def geti():
	I = []
	I.append(input("Enter (i) inclination(deg) = ")*(2*pi/360)) 
	I.append(input("Enter (i) inclination ERROR = ")*(2*pi/360))
	return I
	
def getPeriod():
	P = []
	P.append(input("Enter (P) orbital period(days) = ")/yr)
	P.append(input("Enter (P) orbital period ERROR = ")/yr)
	return P
	
def getM():
	M = []
	M.append(input("Enter (M*) mass of star(solar mass) = "))
	M.append(input("Enter (M*) mass of star ERROR = "))
	return M
	
def getK():
	K = []
	K.append(input("Enter (K*) stellar velocity amp (m/s) = "))
	K.append(input("Enter (K*) stellar velocity amp ERROR = "))
	return K
	
def gete():
	E = []
	E.append(input("Enter (e) eccentricity = "))
	E.append(input("Enter (e) eccentricity ERROR = "))
	return E

def PlanetMass():
	i = geti()				 	# [radians]
	P = getPeriod()				# unitless normalized by year[days] above
	M = getM()					# unitless normalized by solar mass in eq
	K = getK()					# [m/s]
	e = gete()	
	
	Mb = []

	t1 = sqrt(1-e[0]**2.0)/28.4329
	t2 = K[0]/sin(i[0])
	t3 = P[0]**(1./3.)
	t4 = M[0]**(2./3.)
	Mb.append(t1*t2*t3*t4)
	
	kerr = (P[0]*(1./3.)*M[0]**(2./3.)/(28.4329*sin(i[0])))**2 # check this
	ierr = (K[0]*P[0]**(1./3.)*M[0]**(2./3.)*-1.*cot(i[0])*csc(i[0])/28.4329)**2
	Perr = (K[0]*P[0]**(-2./3)*M[0]**(2./3.)/(3*28.4329*sin(i[0])))**2
	Merr = (2*K[0]*P[0]**(1./3.)*M[0]**(-1./3.)/(3*28.4329*sin(i[0])))**2
	eerr = (-1*e[0]*K[0]*P[0]**(1./3.)*M[0]**(2./3.)/(sqrt(1-e[0]*e[0])*28.4329*sin(i[0])))**2
	
	error = sqrt( kerr*(K[0]**2) + ierr*(i[1]**2) + Perr*(P[1]**2) + Merr*(M[1]**2) )
	
	Mb.append(error)
	print "Your Planet mass =",Mb[0]*M_j,"+-",Mb[1]*M_j, "(g)"
	print "Your P_m =", Mb[0],"+-",Mb[1], "(M_jupiter)"
	

