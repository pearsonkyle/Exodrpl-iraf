// Rename file to display.c/cc?

using namespace std;

void Graphics_Display::StartMenu()
{
	// Option to Check for Results/
	float val;
	FILE *fp1 = fopen("ExoDRPL/.Settings/.temp", "r");
	fscanf(fp1,"%f",&val); fclose(fp1);
	
	printf(" _______________________________________________________________ \n");
	printf("                                             		v. %0.2f\n",Version);
	printf("    Exoplanet Data Reduction Pipeline				\n");
	printf("									\n");
	printf("    > 1. Create Photometry Pipeline    > 5. Extras\n");
	printf("    > 2. Settings                      > 6. Help\n");
	printf("    > 3. Advanced Settings             > 7. Check for Updates \n");
	if(val == 1) printf("    > 4. Show Results of Last Run \n");
	printf("           		\n");
	printf("	 > 99. Exit	\n");
	printf("$_______________________________________________________________$\n");
}

void Graphics_Display::SettingsMenu()
{
	char PlanetName[20], RA[20], Dec[20];
	float settings[8];
	int i = 0;
	// Read in settings file
	string InFile = "ExoDRPL/.Settings/.Settings.dat";
	FILE* fp1 = fopen(InFile.c_str(), "r");
    if(fp1 == (FILE *) NULL) cerr << "Graphics/SettingsMenu: problem opening file \"" << InFile <<"\"\n";
	
	// read in settings
	fgets(PlanetName, 20, fp1);
	fgets(RA,20,fp1);
	fgets(Dec,20,fp1);
	// removes new line at end of c.string that was read in
    if (PlanetName[strlen(PlanetName)-1] == '\n' || PlanetName[strlen(PlanetName)-1] == '\r') PlanetName[strlen(PlanetName)-1] = '\0';
    if (RA[strlen(RA)-1] == '\n' || RA[strlen(RA)-1] == '\r') RA[strlen(RA)-1] = '\0';
    if (Dec[strlen(Dec)-1] == '\n' || Dec[strlen(Dec)-1] == '\r') Dec[strlen(Dec)-1] = '\0';
	while(!feof(fp1)){
		fscanf(fp1, "%f", &settings[i]);
		i++;
	}
	//printf("done reading settings in\n");
	fclose(fp1);
	
	//system("clear");
	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n",Version);
	printf("    Settings				\n");
	printf("									\n");
	printf("	> 1.  Planet Name on images = \"%s\"  \n",PlanetName);
	printf("	> 2.  Right Ascension = %s \n",			RA);
	printf("	> 3.  Declination = %s \n",				Dec);
	printf("	> 4.  Minimum Aperture = %0.2f \n",		settings[0]);
	printf("	> 5.  Maximum Aperture = %0.2f \n",		settings[1]);
	printf("	> 6.  Aperture Increment = %0.2f \n",	settings[2]);
	printf("	> 7.  Annulus = %0.1f \n",				settings[3]);
	printf("	> 8.  Dannulus = %0.1f \n",				settings[4]);
	printf("	> 9.  Ingress Points = %0.0f \n",		settings[5]);
	printf("	>10.  Egress Points = %0.0f \n",		settings[6]);
	printf("         							\n");
	printf("	>99. Save & Go Back			\n");
	printf("$_______________________________________________________________$\n");
	
}


void Graphics_Display::AdvSettings()
{
	char trim[20],flat[20],bias[20],sky1[20],sky2[20],sky3[20];
	float settings[8];
	
	// Read in settings file
	string InFile = "ExoDRPL/.Settings/.AdvSettings.dat";
	FILE* fp1 = fopen(InFile.c_str(), "r");
    if(fp1 == (FILE *) NULL) cerr << "Graphics/AdvSettings: problem opening file \"" << InFile <<"\"\n";
    
    fscanf(fp1,"%f\n", &settings[0]);
    fgets(trim, 20, fp1);
    fgets(flat, 20, fp1);
    fgets(bias, 20, fp1);
    fscanf(fp1,"%f\n",&settings[1]); // FWHM
	fgets(sky1, 20, fp1);
    fgets(sky2, 20, fp1);
    fgets(sky3, 20, fp1);
    if (trim[strlen(trim)-1] == '\n' || trim[strlen(trim)-1] == '\r') trim[strlen(trim)-1] = '\0';
    if (flat[strlen(flat)-1] == '\n' || flat[strlen(flat)-1] == '\r') flat[strlen(flat)-1] = '\0';
    if (bias[strlen(bias)-1] == '\n' || bias[strlen(bias)-1] == '\r') bias[strlen(bias)-1] = '\0';
    if (sky1[strlen(sky1)-1] == '\n' || sky1[strlen(sky1)-1] == '\r') sky1[strlen(sky1)-1] = '\0';
    if (sky2[strlen(sky2)-1] == '\n' || sky2[strlen(sky2)-1] == '\r') sky2[strlen(sky2)-1] = '\0';
    if (sky3[strlen(sky3)-1] == '\n' || sky3[strlen(sky3)-1] == '\r') sky3[strlen(sky3)-1] = '\0';
    
	fclose(fp1);
	
	//system("clear");
	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n",Version);
	printf("    Advanced Settings			\n");
	printf("									\n");
	printf("	> 1. Prefix on Flatfield images = \"%s\"\n",	flat);
	printf("	> 2. Prefix on Bias images = \"%s\"\n",			bias);
	printf("	> 3. Average FWHM = %0.2f \n", 				settings[1]);
	printf("	  4. Trim Image - ");
	if(settings[0] == 0) printf("OFF\n");
	else if(settings[0] == 1) printf("ON - Trim ALL images\n");
	else if(settings[0] == 2) printf("ON - Trim Planet images only\n");
	else if(settings[0] == 3) printf("ON - Trim Bias images only\n");
	else if(settings[0] == 4) printf("ON - Trim Flat images only\n");
	else if(settings[0] == 5) printf("ON - Trim Planet + Bias images only\n");
	else if(settings[0] == 6) printf("ON - Trim Planet + Flat images only\n");
	else if(settings[0] == 7) printf("ON - Trim Bias + Flat images only\n");
	if(settings[0] != 0) printf("	> 44. Trim Section = %s \n", trim);
	printf("	> 5. Sky Section1 (x1:x2,y1:y2) = %s \n", sky1);
	printf("	> 6. Sky Section2 = %s \n", sky2);
	printf("	> 7. Sky Section3 = %s \n", sky3);
	
	// 0 - Off
	// 1 - Trim all images
	// 2 - Trim Planet images only
	// 3 - Trim bias images only
	// 4 - Trim flat images only
	// 5 - Trim P+B only
	// 6 - Trim P+F only
	// 7 - Trim B+F only
	
	// Add Cosmic Ray Option
	
	printf("         							\n");
	printf("	> 99. Save & Go Back			\n");
	printf("$_______________________________________________________________$\n");
	
}

void Graphics_Display::HelpMenu()
{
	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n",Version);
	printf("    Help Menu			\n");
	printf("	 What would you like info on?			\n");	
	printf("         							\n");
	printf("	> 1. Create Photometry Pipeline		\n");
	printf("	> 2. Extras	\n");
	printf("	> 3. Settings	\n");
	printf("	> 4. Available Commands \n");
	printf("	 \n");
	printf("	> 6. About the creator \n");
	printf("         							\n");
	printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");
	
}

void Graphics_Display::ExtrasMenu()
{
	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n",Version);
	printf("    Extras Menu			\n");	
	printf("         							\n");
	printf("	> 1. Calculate Planetary Parameters		\n");
	printf("	> 2. Radian <-> Arcmin/sec Conversion	\n");
	//printf("	> 3. Plot Preliminary Run Results \n");
	//printf("	> 4. Plot Final Lightcurve \n"); 		
	//printf("	> 5. Plot Reference Stars \n");
	//printf("	> 6. Plot Airmass vs Time \n");
	//printf("	> 7. Plot X+Y pos of star on CCD vs Time \n");
	printf("         							\n");
	printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");
	
}

void Graphics_Display::InitialPhotMenu()
{
	//Check if Files Exist
	string Issue1 = "1",Issue2 = "1";
	char trim[20], flat[20], bias[20], sky[20], LineIn[20];
	float settings[8];
	
	
	// Check for xyfile
	system("ls > TMPLIST.txt");
	FILE* fp1 = fopen("TMPLIST.txt", "r");
	while(!feof(fp1)){
		fgets(LineIn,20,fp1);
		if (LineIn[strlen(LineIn)-1] == '\n' || LineIn[strlen(LineIn)-1] == '\r') LineIn[strlen(LineIn)-1] = '\0';
    	
    	if(Issue1.length() != 0) {
    		if (strncmp(LineIn, "xyfile", strlen("xyfile")) == 0) Issue1 = "";
    		else Issue1 = "Error: No xyfile file detected\n"; }
    } // End While
    fclose(fp1);
    system("rm -rf TMPLIST.txt");
   
	// Check for Skysection
	// Read in Advsettings file
	fp1 = fopen("ExoDRPL/.Settings/.AdvSettings.dat", "r"); 
    fscanf(fp1,"%f\n", &settings[0]);
    fgets(trim, 20, fp1);
    fgets(flat, 20, fp1);
    fgets(bias, 20, fp1);
    fscanf(fp1,"%f\n",&settings[1]); // FWHM
    fgets(sky, 20, fp1);
    if (trim[strlen(trim)-1] == '\n' || trim[strlen(trim)-1] == '\r') trim[strlen(trim)-1] = '\0';
    if (flat[strlen(flat)-1] == '\n' || flat[strlen(flat)-1] == '\r') flat[strlen(flat)-1] = '\0';
    if (bias[strlen(bias)-1] == '\n' || bias[strlen(bias)-1] == '\r') bias[strlen(bias)-1] = '\0';
    if (sky[strlen(sky)-1] == '\n' || sky[strlen(sky)-1] == '\r') sky[strlen(sky)-1] = '\0';
	fclose(fp1);
	
	if (strcmp(sky, "x1:x2,y1:y2") == 0) Issue2 = "Error: SkySection is not set\n";
	else Issue2 = "";
	
	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n",Version);
	printf("    Create Pipeline Menu 			\n");	
	printf("         						\n");
	printf("	> 1. Preliminary Reduction + Analysis\n");
	printf("	> 2. Main Reduction + Analysis \n");
	printf("	> 3. CHECK SETTINGS	\n\n");
	//			ERROR: please create an xyfile and set skysection
	
	if(Issue1.length() != 0 && Issue2.length() != 0)
	{
		printf("  WARNING: No xyfile detected \n");
		printf("  ERROR: No Skysection Set...follow instructions below \n");
		printf("	Open REF_STAR_README.txt in dir: ExoDRPL/README/ \n");
	}
	else if(Issue1.length() != 0)
	{
		printf("  WARNING: No xyfile detected \n");
		printf("	Open REF_STAR_README.txt in dir: ExoDRPL/README/ \n");
	}
	else if(Issue1.length() == 0)
	{
		if(Issue2.length() != 0)
		{
		printf("  ERROR: No Skysection Set...follow instructions below \n");
		printf("	Open REF_STAR_README.txt in dir: ExoDRPL/README/ \n");
		}
	}
	if(Issue1.length() != 0 || Issue2.length() != 0)
	{
		printf("	OR to view it here type: refstar-readme \n");
	}
	
	
	printf("         							\n");
	printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");
}

void Graphics_Display::AboutCreator()
{
	printf(" _______________________________________________________________ \n");
	printf("                                         	ExoDRPL v. %0.2f \n",Version);
	printf("    About the Creator 			\n");	
	printf("    	Kyle Pearson			\n");
	printf("				\n");
	printf("	University of Arizona \n");
	printf("		Astronomy and Mathematics		\n");
	printf("				\n");
	printf("	Email: pearsonk@email.arizona.edu \n");
	printf("	Website: https://sites.google.com/a/email.arizona.edu/kyle-pearson/ \n");
	printf("	Exoplanet Project: goo.gl/kDn5s \n");
	printf("        							\n");
	printf("	> 99. Go Back			\n");
	printf("^_______________________________________________________________^\n");
}

void Graphics_Display::AvailableCmds()
{
	printf(" _______________________________________________________________ \n");
	printf("                                         	ExoDRPL v. %0.2f \n",Version);
	printf("    Available Commands 			\n");	
	printf("    	these cmds are available to execute at any time	\n");
	printf("    			\n");
	printf("	help - Brings up the help menu		\n");
	printf("	ls - lists files in current directory\n");
	printf("	pwd - lists path to current directory\n");
	printf("	exit/quit - terminate the exodrpl program\n");
	printf("	 OR  exit and type: \n");
	printf("	./ExoFunction help \n");
	printf("        			\n");
	printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");
}

void Graphics_Display::CheckSettings(string *issues, int num)
{
	int i = 0;
	printf(" _______________________________________________________________ \n");
	printf("                                         	ExoDRPL v. %0.2f \n",Version);
	printf("    Settings Checked! 			\n");	
	printf("    	Issues: \n");
	printf("        	\n");
	
	if(num == 0) printf("		NONE \n");
	else for(int i=0;i<num;i++) printf("	%i. %s",i+1,issues[i].c_str());
	
	printf("	\n");
	printf("	> 1.  Go To Settings	\n");
	printf("	> 2.  Go To AdvSettings \n");
	printf("	> 99. Proceed			\n");
	printf("$_______________________________________________________________$\n");
}


void Graphics_Display::CreatePipelineHelp()
{
	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n",Version);
	printf("    Help Menu - Create Photometry Pipeline			\n");
	printf("         							\n");
	printf("    This option will create a series of IRAF scripts that can \n");
	printf("	 then be executed and will do everything from calibrate your\n");
	printf("	 images to performing aperture photometry and plotting results\n\n");
	printf(" 		Menu Options	\n");
	printf(" Preliminary Reduction + Analysis - A quick reduction and photometric analysis\n");
	printf("  to to determine how many ingress + egress points you have. \n\n");
	printf(" Main Reduction + Analysis - A thorough reduction and analysis, runs through \n");
	printf("  all of the apertures specified in settings.  \n\n");
	printf(" Check Settings - Checks settings to make sure you have the necessary param's\n");
	printf("  and files needed to create and run the script with no errors. \n\n");
	printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");
}

void Graphics_Display::ExtrasHelp() 
{
	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n",Version);
	printf("    Help Menu - Extras Menu			\n\n");
	printf("    This option has a bunch of extra features that you can use to\n");
	printf("	enchance your science\n\n");
	printf(" Calculate Planetary Parameters - Calculate radius, mass, density\n");
	printf("  temperature, safronov number, or surface gravity with error bars\n\n");
	printf(" Radian <-> Arc min/sec Conversion - Convert radians <-> Arcmin <-> Arcsec\n\n");
	printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");
}

void Graphics_Display::PrelimCreated()
{
	//FIXME Add another check to makesure the script was created after the program
	
	// Read in settings file to get planet name
	char PlanetName[20];	
	string InFile = "ExoDRPL/.Settings/.Settings.dat";
	FILE* fp1 = fopen(InFile.c_str(), "r");
    if(fp1 == (FILE *) NULL) cerr << "Graphics/SettingsMenu: problem opening file \"" << InFile <<"\"\n";
	fgets(PlanetName, 20, fp1);
    if (PlanetName[strlen(PlanetName)-1] == '\n' || PlanetName[strlen(PlanetName)-1] == '\r') PlanetName[strlen(PlanetName)-1] = '\0';
	fclose(fp1);

	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n",Version);
	printf("	Your Preliminary Data Reduction Script was Created! \n");
	printf("					\n");
	printf("	You must execute this script in IRAF \n");
	// Create xyfile + skyfile
	printf("	To do so type: cl < Pre-%s.cl 	\n", PlanetName);
	printf("					\n");
	printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");
}
	
void Graphics_Display::MainCreated()
{
	//FIXME Add another check to makesure the script was created after the program
	
	// Read in settings file to get planet name
	char PlanetName[20];	
	string InFile = "ExoDRPL/.Settings/.Settings.dat";
	FILE* fp1 = fopen(InFile.c_str(), "r");
    if(fp1 == (FILE *) NULL) cerr << "Graphics/SettingsMenu: problem opening file \"" << InFile <<"\"\n";
	fgets(PlanetName, 20, fp1);
    if (PlanetName[strlen(PlanetName)-1] == '\n' || PlanetName[strlen(PlanetName)-1] == '\r') PlanetName[strlen(PlanetName)-1] = '\0';
	fclose(fp1);

	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n",Version);
	printf("	Your Preliminary Data Reduction Script was Created! \n");
	printf("					\n");
	printf("	You must execute this script in IRAF \n");
	// Create xyfile + skyfile
	printf("	To do so type: cl < Main-%s.cl 	\n", PlanetName);
	printf("					\n");
	printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");
}

void Graphics_Display::PlanetParamsMenu()
{
	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n",Version);
	printf("   Planetary Parameters Menu           \n");
	printf("    What would you like to calculate? (errors included) \n\n");	
	printf("                          What you need      ----------- KEY ------------\n");
	printf("  > 1. Mass of Planet      i,P,M*,K,e       | a - semi-major axis        |\n");
	printf("  > 2. Radius              Rp/R*,R*         | e - eccentricity           |\n");
    printf("  > 3. Semi-major Axis     a/R*,R*          | i - inclination            |\n");
    printf("  > 4. Density of Planet   Mp,Rp            | K - Vel. semi-amp.         |\n");
    printf("  > 5. Equilibrium Temp    Teff,a/R*        | P - Period                 |\n");
    printf("  > 6. Safronov Number     Mp,a,M*,Rp       | pp - density of planet     |\n");
    printf("  > 7. Surface Gravity     P,a,Rp,i,e,K     | Mp,Rp-Mass,Radius of planet|\n"); 
    printf("  > 8. Stellar Density     M*,R*            | M*,R*-Mass,Radius of star  |\n");
    printf("  > 9. Stellar Density     P,a/R*,pp,Rp/R*  | a/R* + Rp/R* you know      |\n");
   	printf("                                             ----------------------------\n");
	printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");	
}


void Graphics_Display::PlanetMass(double *Mb,double *i,double *P,double *Ms,double *K,double *e)
{
	double M_j = 1.89865e30; // jupiter radii in [g]
	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n\n",Version);
	printf("    Your Planetary Mass = %f +- %f M_jup \n\n", Mb[0], Mb[1]);
	
	printf("	Inclination      %f +- %f (deg) \n",    i[0]*360/(2.*M_PI), i[1]*360/(2.*M_PI));
	printf("	Orbital Period   %f +- %f (days) \n",   P[0]*365.24, P[1]*365.24);
	printf("	Stellar Mass     %f +- %f (M_sun) \n",  Ms[0],Ms[1]);
	printf("    Vel. Semi-Amp    %f +- %f (m/s) \n",    K[0], K[1]);
	printf("	Eccentricity     %f +- %f \n\n",        e[0], e[1]);

	printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");	
}

void Graphics_Display::PlanetRadius(double *Rp,double *RpRs,double *Rs)
{
	//R_s = 6.955e5 # solar radius in [km]
	//R_J = 7.1492e4 #jupiter radius in [km]
	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n\n",Version);
	printf("    Your Planetary Radius = %f +- %f R_Jup\n\n", Rp[0],Rp[1]);
	printf("	Planet to Star Ratio  %f +- %f \n",           RpRs[0], RpRs[1]);
	printf("	Stellar Radius        %f +- %f (R_sun) \n\n", Rs[0], Rs[1]);
	printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");	
}

void Graphics_Display::PlanetSemiMajor(double *a,double *aRs,double *Rs)
{
    printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n\n",Version);
    printf("    Planet's semi major axis = %f +- %f AU \n\n", a[0],a[1]);
    printf("    Scaled semi-major axis (a/R*)  %f +- %f \n",aRs[0],aRs[1]);
    printf("    Stellar Radius                 %f +- %f (R_sun) \n\n",Rs[0],Rs[1]);
	printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");	
}
void Graphics_Display::PlanetDensity(double *pb,double *Mp,double *Rp)
{
    printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n\n",Version);
    printf("    Planet's Density = %f +- %f g/cm^3 \n\n",pb[0],pb[1]);
	printf("    Planetary Radius  %f +- %f R_Jup\n", Rp[0],Rp[1]);
    printf("    Planetary Mass    %f +- %f M_Jup\n\n",Mp[0],Mp[1]);
    printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");	
}
void Graphics_Display::PlanetTemp(double *Teff,double *Teq,double *aRs)
{
    printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n\n",Version);
    printf("    Equilibrium Temp of Planet = %f +- %f Kevlin \n\n",Teq[0],Teq[1]);
    printf("    Effective Temp of Star        %f +- %f K  \n",Teff[0],Teff[1]);
    printf("    Scaled semi-major axis (a/R*) %f +- %f \n\n",aRs[0],aRs[1]);  
    printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");	
}
void Graphics_Display::SafronovNUM(double *SN,double *Mp,double *a,double *Ms,double *Rp)
{
    printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n\n",Version);
    printf("    Safronov Number = %f +- %f \n\n",SN[0],SN[1]);
    printf("    Planetary Mass    %f +- %f M_Jup\n\n",Mp[0],Mp[1]);
    printf("    Planet's semi major axis  %f +- %f AU \n\n", a[0],a[1]);
    printf("	Stellar Mass     %f +- %f (M_sun) \n",  Ms[0],Ms[1]);
    printf("    Planetary Radius  %f +- %f R_Jup\n\n", Rp[0],Rp[1]);
    printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");
}
void Graphics_Display::SurfaceGrav(double *sg,double *P,double *a,double *Rp,double *i,double *e,double *K)
{
    printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n\n",Version);
    printf("    Surface Gravity = %f +- %f (cm/s^2) \n", sg[0] , sg[1]); 
    sg[1] = sg[1]/(log(10)*sg[0]);
    printf("                    = %f +- %f log(g) (cgs) \n\n", log10(sg[0]), sg[1]);
    printf("	Orbital Period   %f +- %f (days) \n",   P[0], P[1]);
    printf("    Planet's semi major axis  %f +- %f AU \n", a[0],a[1]);
    printf("    Planetary Radius  %f +- %f R_Jup\n\n", Rp[0],Rp[1]);
    printf("	Inclination      %f +- %f (deg) \n",    i[0]*360/(2.*M_PI), i[1]*360/(2.*M_PI));
    printf("    Vel. Semi-Amp    %f +- %f (m/s) \n",    K[0], K[1]);
    printf("	Eccentricity     %f +- %f \n\n",        e[0], e[1]);
    printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");
}
void Graphics_Display::StellarDensity1(double *ps,double *Ms,double *Rs)
{
    printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n\n",Version);
    printf("    Stellar Density = %f +- %f \n",ps[0],ps[1]);
    printf("	Stellar Mass     %f +- %f (M_sun) \n",  Ms[0],Ms[1]);
    printf("    Stellar Radius                 %f +- %f (R_sun) \n\n",Rs[0],Rs[1]);
    printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");
}
void Graphics_Display::StellarDensity2(double *ps,double *P,double *aRs,double *pb,double *RpRs)
{
    printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n\n",Version);
    printf("    Stellar Density = %f +- %f \n",ps[0],ps[1]);
    printf("	Orbital Period   %f +- %f (days) \n",   P[0], P[1]);
    printf("    Scaled semi-major axis (a/R*) %f +- %f \n\n",aRs[0],aRs[1]);  
    printf("    Planet's Density   %f +- %f g/cm^3 \n\n",pb[0],pb[1]);
    printf("	Planet to Star Ratio  %f +- %f \n\n",           RpRs[0], RpRs[1]);
    printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");
}

void Graphics_Display::SettingsHelp() 
{
	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n\n",Version);
	printf("	Settings Help \n");
	printf(" Planet Name on images - See video tutorial for additional info \n"); 
	printf(" Right Ascension - This option will add the RA to image header of reduced images \n");
	printf(" Declination - Option to add the DEC to the image header of reduced images \n");
	printf(" Min. Aperture - Min. aperture (in pixels) used when performing aperture photometry \n");
	printf(" Max. Aperture - Max. aperture (in pixels) used when performing aperture photometry \n");
	printf(" Aperture Increment - By how much do you want to increase next aperture size by \n");
	printf(" Annulus - Inner radius of sky annulus in pixels \n");
	printf(" Dannulus - Width of the sky annulus in pixels \n");
	printf(" Ingress Points - How many ingress data points are in your lightcurve, used for analysis \n");
	printf(" Egress Points - How many egress data points are in your lightcurve, used for analysis \n\n");
	printf("	Advanced Settings Help\n");
	printf(" Prefix on Flatfield images - See video tutorial for additional info \n");
	printf(" Prefix on Bias images - See video tutorial for additional info \n");
	printf(" Average FWHM - Average full width at half maximum of all images \n");
	printf(" Trim Image - Option to trim images before calibrations. \n");
	printf(" Sky Section - Section of sky that will be used to obtain STDDEV of sky for error bars \n\n");
	printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");
}

void Graphics_Display::CheckUpdate()
{
	float CheckVersion;
	system("rm -rf UpdateVersion.dat");
	system("wget -nv -O UpdateVersion.dat https://sites.google.com/a/email.arizona.edu/kyle-pearson/exodrpl/UpdateVersion.dat");
	FILE* fp = fopen("UpdateVersion.dat", "r");
	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n",Version);
	printf("	Version Checked\n\n");
	if(fp == (FILE *) NULL) cerr << "Can't open \"" << "UpdateVersion.dat" <<"\"\n Please Check Website for Updates \n";
	else 
	{ 
		fscanf(fp, "%f", &CheckVersion);
		if(CheckVersion == Version) printf("	Your program is up to date!\n\n");	
		else
		{
	 	 printf("	Your Version = %0.2f\n", Version);
	 	 printf("	Current Version = %0.2f\n", CheckVersion);
	 	 if(CheckVersion != 0) printf("	To update type: update (or ./ExoFunction update)\n	Or");
	 	 printf(" check website and download update manually (goo.gl/TLLZX)\n\n");
		}
	}
	printf("	> 99. Go Back			\n");
	printf("$_______________________________________________________________$\n");
	
	fclose(fp);
	system("rm -rf UpdateVersion.dat");
}

void Graphics_Display::GetUpdate()
{
	system("rm -rf Exo_DRPL.tar.gz");
	system("wget -nv -O Exo_DRPL.tar.gz https://sites.google.com/a/email.arizona.edu/kyle-pearson/exodrpl/Exo_DRPL.tar.gz");
	
	//Check if File Downloaded Successfully
	string Issue="Exo_DRPL.tar.gz Not Detected";
	char New[30] = {'\0'};
	char FileCheck[] = "Exo_DRPL.tar.gz";
	system("rm -rf FileList.txt");
	system("ls > FileList.txt");
	FILE *fp1 = fopen("FileList.txt", "r");
	while(!feof(fp1)){
		fgets(New,30,fp1);
		if (New[strlen(New)-1] == '\n' || New[strlen(New)-1] == '\r') New[strlen(New)-1] = '\0';
		if(Issue.length() != 0) { // Not Detected Yet
			if( strncmp(New,FileCheck,strlen(FileCheck)) == 0) Issue = ""; // New download detected
			else Issue = "Exo_DRPL.tar.gz Not Detected \n"; }	
    } // End While
    
    fclose(fp1);
	system("rm -rf FileList.txt");
	
	// New Download Detected
	if(Issue.length() == 0) 
	{
		system("rm -rf OLDVERSION/");
		system("rm -rf compile+run");
		system("mv ExoDRPL OLDVERSION/");
		system("tar -xvzf Exo_DRPL.tar.gz");
	}
	
	printf(" _______________________________________________________________ \n");
	printf("                                          	ExoDRPL v. %0.2f \n\n",Version);
	printf("	Program was "); 
	if(Issue.length() != 0) printf("not ");
	printf("downloaded\n");

	if(Issue.length() == 0)
	{
		printf("	Please recompile and run \n");
		printf("	type: ./compile+run \n\n");
	}
	else
	{
		printf("Check internet connection or Download update from \n");
		printf("	https://sites.google.com/a/email.arizona.edu/kyle-pearson/exodrpl/ \n");
	}
	printf("	exiting...			\n");
	printf("$_______________________________________________________________$\n");
	exit(1);
}



void Graphics_Display::PlottingHelp() {}
void Graphics_Display::PythonHelp() {}
//void Graphics_Display::AfterAnalyze/File Directory with a quick execute option

