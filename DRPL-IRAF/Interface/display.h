// this will contain all the graphics stuff
using namespace std;

struct Graphics_Display{
	
	float Version;
	
	void StartMenu();
	void SettingsMenu(); 
	void AdvSettings();
	void ExtrasMenu();
	void HelpMenu(); // Add in help menu
	void InitialPhotMenu();
	void CheckSettings(string *issues, int num);	
	void AvailableCmds();
	void AboutCreator();
	void PrelimCreated();
	void MainCreated();
	void CheckUpdate();
	void GetUpdate();
	
	// Help Info Displays
	void CreatePipelineHelp();
	void ExtrasHelp();
	void SettingsHelp();
	void PlottingHelp();// remove
	void PythonHelp(); // remove
	
	// Display for PlanetParams
	void PlanetParamsMenu();
	void PlanetMass(double *Mb,double *i,double *P,double *Ms,double *K,double *e);
	void PlanetRadius(double *Rp,double *RpRs,double *Rs);
    void PlanetSemiMajor(double *a,double *aRs,double *Rs);
    void PlanetDensity(double *pb,double *Mp,double *Rp);
	void PlanetTemp(double *Teff,double *Teq,double *aRs);
	void SafronovNUM(double *SN,double *Mp,double *a,double *Ms,double *Rp);
    void SurfaceGrav(double *sg,double *P,double *a,double *Rp,double *i,double *e,double *K);
    void StellarDensity1(double *ps,double *Ms,double *Rs);
    void StellarDensity2(double *ps,double *P,double *aRs,double *pb,double *RpRs);

};

#include "display.cc"
