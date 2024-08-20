# Calculate the equilibrium Temp of the planet

def getaR():
	A = []
	A.append(input("Enter (a/R*) Distance-Star Radius Ratio = "))
	A.append(input("Enter (a/R*) Distance-Star Radius Ratio ERROR = "))
	return A
	
def getTef():
	T = []
	T.append(input("Enter (T_ef) Effective temp of Planet (K) = "))
	T.append(input("Enter (T_ef) Effective temp of Planet ERROR = "))
	return T
	
def eqTemp():
	aR = getaR()
	Tef = getTef()
	
	Teq = []
	
	t1 = Tef[0]*(0.25)**(1./4.)*(1./sqrt(2.))*aR[0]**(-1./2.)
	Teq.append(t1)
	
	Terr = (0.25)**(1./4.)*(1./sqrt(2.))*aR[0]**(-1./2.)
	aerr = Tef[0]*(0.25)**(1./4.)*(1./sqrt(2.))*(-1./2.)*aR[0]**(-3./2.)
	
	error = sqrt( Tef[1]**2*Terr**2 + aR[1]**2*aerr**2 )
	Teq.append(error)
	
	print "T_eq =",Teq[0],"+-", Teq[1], "[K]"
