# Calculate the Safronov Number from Southworth 2010

from math import sqrt

M_s = 1.988547e33  # solar mass in [g]
M_j = 1.89865e30 # jupiter radii in [g]
R_J = 7149200000 #jupiter radius in [cm]

def getMs():
	M = []
	M.append(input("Enter (M*) mass of star(solar mass) = ")*M_s)
	M.append(input("Enter (M*) mass of star ERROR = ")*M_s)
	return M
	
def getMp():
	M = []
	M.append(input("Enter (M_b) mass of planet(jupiter mass) = ")*M_j)
	M.append(input("Enter (M_b) mass of planet ERROR = ")*M_j)
	return M
	
def geta():
	A = []
	A.append(input("Enter (a) Distance to Planet (AU) = ")*1.49597871e13)
	A.append(input("Enter (a) Distance to Planet ERROR = ")*1.49597871e13)
	return A
	
def getRp():
	R = []
	R.append(input("Enter (R_p) Planet Radius(Jup radii) = ")*R_J)
	R.append(input("Enter (R_p) Planet Radius ERROR = ")*R_J)
	return R
	
def SafronovNum():
	print "Calculating Safronov Number..."
	Ms = getMs()
	Mp = getMp()
	a = geta()
	Rp = getRp()
	
	Safronov = []
	
	saf = Mp[0]*a[0]/(Ms[0]*Rp[0])
	Safronov.append(saf)
	
	Mperr = a[0]/(Ms[0]*Rp[0])
	Mserr = -1.*Mp[0]*a[0]/(Rp[0]*Ms[0]*Ms[0])
	aerr = Mp[0]/(Ms[0]*Rp[0])
	Rerr = -1.*Mp[0]*a[0]/(Ms[0]*Rp[0]*Rp[0])
	
	error = sqrt(Mp[1]**2*Mperr**2 + Ms[1]**2*Mserr**2 + a[1]**2*aerr**2 + Rp[1]**2*Rerr**2 )
	
	Safronov.append(error)
	print "Safronov Num =",Safronov[0],"+-",Safronov[1]
	


