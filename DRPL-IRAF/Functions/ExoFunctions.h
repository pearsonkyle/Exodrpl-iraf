
using namespace std;

struct Exo_Functions{

	// Useful Functions (ExoFunctions)
	void ReadSettings(char *Planet, char *RA, char *DEC, float *settings);
	void ReadAdvSettings(char *trim, char *flat, char *bias, float *Advsettings);
	void ReadAdvSettings(char *trim, char *flat, char *bias, char *sky, float *Advsettings); 
	void ReadAdvSettings3(char *trim, char *flat, char *bias, char *sky1, char *sky2, char *sky3, float *Advsettings);
    void SetSkySection(string section, int NUM); // Sets the sky section in adv settings from runtime args	    
    void SetSkySection(string section); // Sets the sky section in adv settings from runtime args
    void DelRow(string IN, string OUT); // reads in a file, copies it to a new file without the first line
	void CreateCleanUp();               // Creates ExoCleanUp.cl to remove excess files
	int GetHJD();                       // reads in hjd and returns first line as an integer
	int FileSize(string InFile);        // returns the size of a file
    int CheckSky(string section);       // returns 0 for bad section, 1 for good format sky section
	float GetSkySigma();                // reads in skysigma.dat and returns the STDEV 
	
	
	// Data Reduction + Photometry Functions (ExoMainScripts) 
												// Identifier: 0 = Preliminary, 1 = Main
	void CreateReductionScript(int Identifier);	// Creates the main data reduction + ap photometry script 
	void CreatePhotInfo(int Identifier);        // Creates Photinfo files for main aperture photometry	
	void CreateApPhotScript(int Identifier);    // Creates Script to do the aperture photometry 
	
	
	// Analysis Functions (ExoAnalysis)
	void AnalyzeResults();              // Analyze ExoPreResults to determine best aperture + reference star combo + gets Errors
	void AfterAnalyze();                // Creates a Script to clean up your files and then graph your lightcurve
	void LightCurveOp(string filename); // Finds the best reference star combo given a certain allflux file
	void CalcSTDEV(double *data,int images,double *STDEV); // Calculates STDEV for ingress, egress and both
	

	// Extras Functions (ExoExtras)
	// Calculate Planetary Parameters
	void CalcSDensity(double *p,double *m,double *r);	        // Calc Stellar Density of Star thru M/V
	void CalcRadius(double *Rp,double *RpRs,double *Rs);        // Radius of Planet
    void CalcDensity(double *pb,double *Mp,double *Rp);         // Density of Planet
    void CalcTemp1(double *Teff,double *Teq,double *aRs);       // Equilibrium Temperature
    void CalcSemiMajorAxis(double *a,double *aRs,double *Rs);   // Semi-major axis of planet
    void CalcSafronovNum(double *SN,double *Mb,double *a,double *Ms,double *Rb);  // Safronov Number
    void CalcMass(double *Mb,double *i,double *P,double *Ms,double *K,double *e); // Mass of Planet
    void CalcStellarDensity(double *ps,double *P,double *aRs,double *pb,double *RpRs); // Stellar Density derived from Kepler's 3rd
    void CalcSurfaceGrav(double *sg,double *P,double *a,double *Rp,double *i,double *e,double *K); // Surface Gravity of Planet
    
};

#include "ExoFunctions.cc"
#include "ExoAnalysis.cc"
#include "ExoMainScripts.cc"
#include "ExoExtras.cc"

// Finish Planetary Parameters
// ExoDRPL, ExoFunctions, ExoExtras, UI.cc, display.h, display.cc
