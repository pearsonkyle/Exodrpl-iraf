# Calculates Planetary Parameters plus errors
# Created by Kyle Pearson

# GNU PUBLIC LISENCSE v3.0
from PlanetMass import *
from PlanetRadius import *
from PlanetDensity import *
from PlanetTemp import *
from PlanetMagneticField import *
from SafronovNum import *
from SurfaceGrav import *
from VidottoTiming import *

def start():
	print "Which planetary parameter would you like to calculate?"
	print " 1. Mass "
	print " 2. Radius "
	print " 3. Density "
	print " 4. Temperature "
	print " 5. Magnetic Field "
	print " 6. Safronov Number "
	print " 7. Surface Gravity " 
	print " 8. Vidotto Timing Difference (without B ratio)"
	print " 9. Vidotto Timing Difference (with B ratio)"
	var = input("Your answer: ")
	if var == 1:
		PlanetMass()
	elif var == 2:
		PlanetRadius()
	elif var == 3:		
		PlanetDensity()
	elif var == 4:
		eqTemp()
	elif var == 5:
		PlanetMagneticField()
	elif var == 6:
		SafronovNum()
	elif var == 7:
		SurfaceGrav()
	elif var == 8:
		VidottoTime()
	elif var == 9:
		VidottoTimeWith()
	else:
		print "I do not understand your request...try again"
		start() 

