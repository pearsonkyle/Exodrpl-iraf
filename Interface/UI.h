using namespace std;

struct User_Interface {
	
	Graphics_Display Display;
	Exo_Functions Func;
	
	// Constructor
	User_Interface(Graphics_Display display, Exo_Functions func)
	{ 
		Display = display; 
		Func = func;
	}
	
	// Input Options for each Menu
	void StartMenu();
	void InitialPhotMenu();
	void SettingsMenu();
	void AdvSettings();
	void HelpMenu();
	void ExtrasMenu();
	void PlanetParams();
	void HelpMenuInput(int i);
	int CheckSettings(int I);
	
};

#include "UI.cc"


