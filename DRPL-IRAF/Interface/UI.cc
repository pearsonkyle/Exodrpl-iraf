using namespace std;

void User_Interface::StartMenu()
{	
	char Input[5], *pNext;	
	char LS[] = "ls", EXIT[] = "exit", QUIT[] = "quit", HELP[] = "help", PWD[] = "pwd";
	int in; float val;
	// Check for Results
	FILE *fp1 = fopen("ExoDRPL/.Settings/.temp", "r");
	fscanf(fp1,"%f",&val); fclose(fp1);
	
	Display.StartMenu();
	
	printf(" > "); scanf("%s",Input);
	
	if(strcmp(Input, LS) == 0)
	{
		system("ls");
		StartMenu();
	}
	else if(strcmp(Input, PWD) == 0)
	{
		system("pwd");
		StartMenu();
	}
	else if(strcmp(Input, EXIT) == 0)
	{
		exit(1);
	}
	else if(strcmp(Input, QUIT) == 0)
	{
		exit(1);
	}
	else if(strcmp(Input, HELP) == 0)
	{
		Display.HelpMenu();
		HelpMenu();
	}

	in = strtol(Input, &pNext, 10); // convert char* to int(input, *next char, base)
	
	if(in == 99) exit(1);
	switch (in) {
  		case 1:
    		Display.InitialPhotMenu();
    		InitialPhotMenu();
    		StartMenu();
    		break;
    	case 2:
    		Display.SettingsMenu();
    		SettingsMenu();
    		StartMenu(); // when they exit settings they will be brought back to start menu
    		break;
    	case 3:
    		Display.AdvSettings();
    		AdvSettings();
    		StartMenu();
    		break;
    	case 4:
			if(val == 0) // no Results
			{
				cout << "value unknown... \n";
    			StartMenu();
			}
			else if(val == 1)
			{
				system("more Results/ExoResults.txt");
				StartMenu();
			}
			break;
    	case 5:
    		Display.ExtrasMenu();
    		ExtrasMenu();
    		StartMenu();
    		break;
    	case 6:
    		Display.HelpMenu();
			HelpMenu();
			StartMenu();
    		break;
    	case 7:
    		cout << "Quirying Internet...\n";
    		Display.CheckUpdate();
    		HelpMenuInput(8);
    		StartMenu();
  		default:
    		cout << "value unknown... \n";
    		StartMenu();
    		//free(in);
    		//exit(1);
    		break;
  }
  
}

void User_Interface::InitialPhotMenu()
{
	char LS[] = "ls", EXIT[] = "exit", QUIT[] = "quit", HELP[] = "help", PWD[] = "pwd";
	char REFSTAR[] = "refstar-readme";
	char Input[5], *pNext;
	int in, check;
	
	printf("Phot > "); scanf("%s",Input);
	
	if(strcmp(Input, LS) == 0)
	{
		system("ls");
		Display.InitialPhotMenu();
		InitialPhotMenu();
	}
	else if(strcmp(Input, PWD) == 0)
	{
		system("pwd");
		Display.InitialPhotMenu();
		InitialPhotMenu();
	}
	else if(strcmp(Input, EXIT) == 0)
	{
		exit(1);
	}
	else if(strcmp(Input, QUIT) == 0)
	{
		exit(1);
	}
	else if(strcmp(Input, HELP) == 0)
	{
		Display.CreatePipelineHelp();
		HelpMenuInput(1);
		Display.InitialPhotMenu();
    	InitialPhotMenu();
	}
	else if(strcmp(Input, REFSTAR) == 0)
	{
		system("more ExoDRPL/README/REF_STAR_README.txt");
		Display.InitialPhotMenu();
		InitialPhotMenu();
	}
	else
	{
		in = strtol(Input, &pNext, 10); // convert char* to int

		if(in != 99) // exit settings right away
		{
		// FIXME
			switch (in) {
  			case 1:
  				// Check Settings before running preliminary script
    			check = CheckSettings(1); // 1chill, 2Settings, 3AdvSettings
    			if(check == 1)
    			{
    				Func.CreateReductionScript(0); // 0 for Preliminary Reduction Script
    				Display.PrelimCreated();
    				HelpMenuInput(7);
    			}
    			else if(check == 2) 
    			{
    				Display.SettingsMenu();
    				SettingsMenu();
    			}
    			else if(check == 3)
    			{
    				Display.AdvSettings();
    				AdvSettings();
    			}
    			break;
    		case 2:
    			// Check settings before running Main script
    			check = CheckSettings(1); // 1chill, 2Settings, 3AdvSettings
    			if(check == 1)
    			{
    				Func.CreateReductionScript(1); // 0 for Preliminary Reduction Script
    				Display.MainCreated();
    				HelpMenuInput(7);
    			}
    			else if(check == 2) 
    			{
    				Display.SettingsMenu();
    				SettingsMenu();
    			}
    			else if(check == 3)
    			{
    				Display.AdvSettings();
    				AdvSettings();
    			}
    			break;
    		case 3:
    			check = CheckSettings(1); // 1 check everything, 2 check data reducton, ?
    			if(check == 1) printf("hey checksettings = 1...continue on all good \n");
    			else if(check == 2) 
    			{
    				Display.SettingsMenu();
    				SettingsMenu();
    			}
    			else if(check == 3)
    			{
    				Display.AdvSettings();
    				AdvSettings();
    			}
    			break;
	  		default:
				cout << "Unknown Value...\n";
				break;
  			}
		Display.InitialPhotMenu();
  		InitialPhotMenu();
		} // end if 99
	} // end else
}


int User_Interface::CheckSettings(int I) // I for check settings for different parts of program, plotting, preliminary, check files
{
	int in, NumIssues = 0; char Input[5], *pNext;
	char Planet[20] = {'\0'}, New[20] = {'\0'}, RA[20] = {'\0'}, Dec[20] = {'\0'};
	char trim[20] = {'\0'}, flat[20] = {'\0'}, bias[20] = {'\0'}, sky[20] = {'\0'};
	char LS[] = "ls", EXIT[] = "exit", QUIT[] = "quit", HELP[] = "help", PWD[] = "pwd";
	float settings[8], settings2[8], newSetting;
	string InFile = "ExoDRPL/.Settings/.Settings.dat";
	//string InFile2 = "ExoDRPL/.Settings/.AdvSettings.dat";
	string InTEST, Issue1="", Issue2="", Issue3="1", Issue4="1", Issue5="1", Issue6="1", Issue7 =""; 
	FILE *fp1, *fpTEST;

	Func.ReadSettings(Planet, RA, Dec, settings);
	Func.ReadAdvSettings(trim, flat, bias, sky, settings2);
	
  // GET ISSUES
	
	// Check for Zero Values
	if(strlen(Planet) == 0 || strlen(Planet) == 1) {
		NumIssues += 1; 
		Issue1 = "Warning: Low values detected. Check Planet Name."; }
		// Check that sKy annulus is greater than current aperture
	if(settings[3] < settings[1]){
		NumIssues += 1; 
		Issue2 = "Sky Annulus should be larger than Max Aperture so no light from star is included"; }
		// check to see if it can open a flat,bias,image 
	
	// Check for sky section
	if (strcmp(sky, "x1:x2,y1:y2") == 0) {
		NumIssues += 1;
		 Issue7 = "Error: SkySection is not set\n"; }
	
	//Check if Files Exist
	system("ls > FileList.txt");
	InFile = "FileList.txt";
	fp1 = fopen(InFile.c_str(), "r");
	//cout << InFile << " was opened \n";
    if(fp1 == (FILE *) NULL) cerr << "Check/AdvSettings1: problem opening file \"" << InFile <<"\"\n";

	while(!feof(fp1)){
		fgets(New,20,fp1);
		if (New[strlen(New)-1] == '\n' || New[strlen(New)-1] == '\r') New[strlen(New)-1] = '\0';
		
		// Check for Planet images
		if(Issue3.length() != 0) {
			if( strncmp(New,Planet,strlen(Planet)) == 0) Issue3 = "";
			else Issue3 = "Warning: No Planet Images Detected\n"; }	
		
		// Check for flat images
		if(Issue4.length() != 0) {
    		if( strncmp(New, flat, strlen(flat)) == 0) Issue4 = "";
    		else Issue4 = "Warning: No Flat Images Detected\n"; }
		
		// Check for bias images
		if(Issue5.length() != 0) {
    		if( strncmp(New, bias, strlen(bias)) == 0) Issue5 = "";
    		else Issue5 = "Warning: No Bias Images Detected\n"; }
    	
    	// Check for xyfile
    	if(Issue6.length() != 0) {
    		if (strncmp(New, "xyfile", strlen("xyfile")) == 0) Issue6 = "";
    		else Issue6 = "Warning: No xyfile file detected\n"; }
		   
    } // End While
    // Count issues
    if(Issue3.length() > 0) NumIssues+=1;
    if(Issue4.length() > 0) NumIssues+=1;
    if(Issue5.length() > 0) NumIssues+=1;
    if(Issue6.length() > 0) NumIssues+=1;
    if(Issue7.length() > 0) NumIssues+=1;
    fclose(fp1);

	// Collect Issues to Send to Display
	//cout << "Num Issues = " << NumIssues << "\n";
	if(NumIssues == 0) NumIssues = 1; // just for allocation purposes
	string Issues[NumIssues];
	NumIssues = 0;

	// Warning low value for planet name
	if(strlen(Planet) == 0 || strlen(Planet) == 1){ 
		Issues[NumIssues] = Issue1; 
		NumIssues += 1;  }
		 
	// Checks sky annulus vs max aperture
	if(settings[3] < settings[1]){
		Issues[NumIssues] = Issue2;
		NumIssues += 1; }
	
	// Check for sky section
	if (strcmp(sky, "x1:x2,y1:y2") == 0) {
		Issues[NumIssues] = Issue7;
		NumIssues += 1; } 
	
	InFile = "FileList.txt";
	fp1 = fopen(InFile.c_str(), "r");
    if(fp1 == (FILE *) NULL) cerr << "Check/AdvSettings1: problem opening file \"" << InFile <<"\"\n";
    
	while(!feof(fp1)){
		fgets(New,20,fp1);
		if (New[strlen(New)-1] == '\n' || New[strlen(New)-1] == '\r') New[strlen(New)-1] = '\0';
		
		// Check for Planet images
		if(Issue3.length() != 0) {
			if( strncmp(New,Planet,strlen(Planet)) == 0) Issue3 = "";
			else Issue3 = "Warning: No Planet Images Detected\n"; }	
		
		// Check for flat images
		if(Issue4.length() != 0) {
    		if( strncmp(New, flat, strlen(flat)) == 0) Issue4 = "";
    		else Issue4 = "Warning: No Flat Images Detected\n"; }
		
		// Check for bias images
		if(Issue5.length() != 0) {
    		if( strncmp(New, bias, strlen(bias)) == 0) Issue5 = "";
    		else Issue5 = "Warning: No Bias Images Detected\n"; }
    	
    	// Check for xyfile
    	if(Issue6.length() != 0) {
    		if (strncmp(New, "xyfile", strlen("xyfile")) == 0) Issue6 = "";
    		else Issue6 = "Warning: No xyfile file detected\n"; }
    		  	
    } // End While
    
    
    // Organize Issues from while loop to be sent to display
    if(Issue3.length() > 0) {
    	Issues[NumIssues] = Issue3;
    	NumIssues += 1; }
    	
    if(Issue4.length() > 0) {
    	Issues[NumIssues] = Issue4;
    	NumIssues += 1; }
    
    if(Issue5.length() > 0) {
    	Issues[NumIssues] = Issue5;
    	NumIssues += 1; }
    	
    if(Issue6.length() > 0) {
    	Issues[NumIssues] = Issue6;
    	NumIssues += 1; }
    	
    	
    fclose(fp1); //Close FileList.txt
    system("rm -rf FileList.txt");

	// send issue info to display
	Display.CheckSettings(Issues, NumIssues);
	
	// Input Stuff
	printf("Check > "); scanf("%s",Input);
	
	if(strcmp(Input, LS) == 0)
	{
		system("ls");
		Display.InitialPhotMenu();
		InitialPhotMenu();
	}
	else if(strcmp(Input, PWD) == 0)
	{
		system("pwd");
		Display.InitialPhotMenu();
		InitialPhotMenu();
	}
	else if(strcmp(Input, EXIT) == 0) exit(1);
	else if(strcmp(Input, QUIT) == 0) exit(1);
	else if(strcmp(Input, HELP) == 0)
	{
		Display.HelpMenu();
		HelpMenu();
	}
	else
	{
		in = strtol(Input, &pNext, 10); // convert char* to int

		if(in != 99) // exit settings right away
		{
			switch (in) {
			// FIXME
  			case 1:
    			return 2;
    			break;
  			case 2:
  				return 3; // go to adv settings
  				break;
	  		default:
				cout << "Unknown Value...\n";
				break;
  			}
  			
		} // end if 99
	} // end else
	
	if(Issue7.length() > 0) return 4;
	return 1; //2 - Settings, 3 - Adv Setting, 4- dont do anything 
	// issue doing pwd/ls during this
}


void User_Interface::SettingsMenu()
{
	int in; char Input[5], *pNext;
	char Planet[20] = {'\0'}, New[20] = {'\0'}, RA[20] = {'\0'}, Dec[20] = {'\0'};
	char LS[] = "ls", EXIT[] = "exit", QUIT[] = "quit", HELP[] = "help", PWD[] = "pwd";
	enum{min, max, precision, ann, dann, ingress, egress}Settings;
	float settings[8], newSetting;
	string InFile = "ExoDRPL/.Settings/.Settings.dat";
	FILE *fp1;
	
	printf("Settings > "); scanf("%s",Input);
	
	if(strcmp(Input, LS) == 0)
	{
		system("ls");
		Display.SettingsMenu();
		SettingsMenu();
	}
	else if(strcmp(Input, PWD) == 0)
	{
		system("pwd");
		Display.SettingsMenu();
		SettingsMenu();
	}
	else if(strcmp(Input, EXIT) == 0) exit(1);
	else if(strcmp(Input, QUIT) == 0) exit(1);
	else if(strcmp(Input, HELP) == 0)
	{
		Display.HelpMenu();
		HelpMenu();
	}
	else
	{
	in = strtol(Input, &pNext, 10); // convert char* to int
	
if(in != 99) // exit settings right away
	{
	// Read in settings file
	fp1 = fopen(InFile.c_str(), "r");
    if(fp1 == (FILE *) NULL) cerr << "UI/Settings_Input1: problem opening file \"" << InFile <<"\"\n";
	fgets(Planet,20,fp1); fgets(RA,20,fp1); fgets(Dec,20,fp1);
	// removes new line at end of c.string that was read in
    if (Planet[strlen(Planet)-1] == '\n' || Planet[strlen(Planet)-1] == '\r') Planet[strlen(Planet)-1] = '\0';
    if (RA[strlen(RA)-1] == '\n' || RA[strlen(RA)-1] == '\r') RA[strlen(RA)-1] = '\0';
    if (Dec[strlen(Dec)-1] == '\n' || Dec[strlen(Dec)-1] == '\r') Dec[strlen(Dec)-1] = '\0';
    int i=0;
	while(!feof(fp1)){
		fscanf(fp1, "%f", &settings[i]);
		i++;
	}
	fclose(fp1);
	
	// Change Settings
	switch (in) {
  		case 1:
    		cout << "Planet Name = ";
			cin >> New;
			strcpy(Planet, New);
    		break;
    	case 2:
    		cout << "Planet RA (XX:XX:XX.X) = ";
    		cin >> New;
    		strcpy(RA, New);
    		break;
    	case 3:
    		cout << "Planet Dec (XX:XX:XX.X) = ";
    		cin >> New;
    		strcpy(Dec, New);
    		break;
 		case 4: 
 			cout << "Min Aperture = ";
			cin >> newSetting;
			settings[min] = newSetting;
    		break;
    	case 5: 
    		cout << "Max Aperture = ";
    		cin >> newSetting;
			settings[max] = newSetting;
    		break;
    	case 6: 
    		cout << "Aperture Precision = ";
    		cin >> newSetting;
			settings[precision] = newSetting;
    		break;
    	case 7: 
    		cout << "Annulus = ";
    		cin >> newSetting;
			settings[ann] = newSetting;
    		break;
    	case 8: 
    		cout << "Dannulus = ";
    		cin >> newSetting;
			settings[dann] = newSetting;
    		break;
    	case 9: 
    		cout << "Ingress Points = ";
    		cin >> newSetting;
			settings[ingress] = newSetting;
    		break;
    	case 10: 
    		cout << "Egress Points = ";
    		cin >> newSetting;
			settings[egress] = newSetting;
    		break;

  		default:
    		cout << "value unknown.. \n";
    		break;
  	}
  	
  	// Write Settings to file
  	fp1 = fopen(InFile.c_str(), "w");
    if(fp1 == (FILE *) NULL) cerr << "UI/Settings_Input2: problem opening file \"" << InFile <<"\"\n";
   // printf("planet to write: %s \n",Planet);
	fprintf(fp1,"%s\n%s\n%s\n",Planet,RA,Dec);	
	for(int j =0;j<7;j++)
	{
		fprintf(fp1,"%f",settings[j]);
		if(j != 6)fprintf(fp1,"\n"); // no new line on last line
	}
	fclose(fp1);

  	Display.SettingsMenu();
  	SettingsMenu();
	} //end if(99)
	} //end else
} // End Settings Input


void User_Interface::AdvSettings()
{
	int in=0; char Input[5], *pNext;
	float settings[8], newSetting;
	char New[20]={'\0'},trim[20]={'\0'},flat[20]={'\0'},bias[20]={'\0'},sky1[20]={'\0'},sky3[20]={'\0'},sky2[20]={'\0'};
	char LS[] = "ls", EXIT[] = "exit", QUIT[] = "quit", HELP[] = "help", PWD[] = "pwd";
	string InFile = "ExoDRPL/.Settings/.AdvSettings.dat";
	FILE *fp1;
	
	printf("AdvSettings > "); scanf("%s",Input);
	
	if(strcmp(Input, LS) == 0)
	{
		system("ls");
		Display.AdvSettings();
		AdvSettings();
	}
	else if(strcmp(Input, PWD) == 0)
	{
		system("pwd");
		Display.AdvSettings();
		AdvSettings();
	}
	else if(strcmp(Input, EXIT) == 0) exit(1);
	else if(strcmp(Input, QUIT) == 0) exit(1);
	else if(strcmp(Input, HELP) == 0)
	{
		Display.HelpMenu();
		HelpMenu();
		//StartMenu();
	}
	else
	{
	in = strtol(Input, &pNext, 10); // convert char* to int
	
	
	if(in != 99) // exit settings right away
	{

		// Read in settings file // FIXME
		fp1 = fopen(InFile.c_str(), "r");
    	if(fp1 == (FILE *) NULL) cerr << "UI/AdvSettings1: problem opening file \"" << InFile <<"\"\n";
    	
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
		
		
		// Change Settings
	switch (in) {
    	case 1:
    		cout << "Name of Flatfield images = ";
    		cin >> New;
    		strcpy(flat, New);
    		break;
    	case 2:
    		cout << "Name of Bias images = ";
    		cin >> New;
    		strcpy(bias, New);
    		break;
    	case 3:
    		cout << "Average FWHM = ";
    		cin >> newSetting;
    		settings[1] = newSetting;
    		break;
    	case 4:
    		cout << "Trim Toggled \n";
			//if(settings[0] == 0) settings[0] = 1;
			//else settings[0] = 0;
			
			if(settings[0] < 7) settings[0]++;
			else settings[0] = 0;
			
			// 0 - Off
			// 1 - Trim all images
			// 2 - Trim Planet images only
			// 3 - Trim bias images only
			// 4 - Trim flat images only
			// 5 - Trim P+B only
			// 6 - Trim P+F only
			// 7 - Trim B+F only
			
    		break;
    	case 44:
    		cout << "Trim Section = ";
    		cin >> New;
    		strcpy(trim, New);
    		break;
    	case 5:
    		cout << "Sky Section = ";
    		cin >> New;
    		strcpy(sky1, New);
    		break;
    	case 6:
    		cout << "Sky Section2 = ";
    		cin >> New;
    		strcpy(sky2, New);
    		break;
    	case 7:
    		cout << "Sky Section3 = ";
    		cin >> New;
    		strcpy(sky3, New);
    		break;
  		default:
    		cout << "value unknown... \n";
    		break;
  	}
	
		// Write New settings to file
		fp1 = fopen(InFile.c_str(), "w");
    	if(fp1 == (FILE *) NULL) cerr << "UI/AdvSettings2: problem opening file \"" << InFile <<"\"\n";
    	
    	fprintf(fp1,"%0.0f\n",settings[0]);
    	fprintf(fp1,"%s\n",trim);
    	fprintf(fp1,"%s\n",flat);
    	fprintf(fp1,"%s\n",bias);
    	fprintf(fp1,"%0.2f\n",settings[1]);
    	fprintf(fp1,"%s\n",sky1);
    	fprintf(fp1,"%s\n",sky2);
    	fprintf(fp1,"%s\n",sky3);
    	// Add more Here, alter display as well
    	
		fclose(fp1);
	
	Display.AdvSettings();
  	AdvSettings();
	} // end if 99
	} // end else
}

void User_Interface::HelpMenu()
{
	char LS[] = "ls", EXIT[] = "exit", QUIT[] = "quit", HELP[] = "help", PWD[] = "pwd";
	char Input[5], *pNext;
	int in;
	
	printf("Menu > "); scanf("%s",Input);
	
	if(strcmp(Input, LS) == 0)
	{
		system("ls");
		Display.HelpMenu();
		HelpMenu();
	}
	else if(strcmp(Input, PWD) == 0)
	{
		system("pwd");
		Display.HelpMenu();
		HelpMenu();
	}
	else if(strcmp(Input, EXIT) == 0) exit(1);
	else if(strcmp(Input, QUIT) == 0) exit(1);
	else if(strcmp(Input, HELP) == 0)
	{
		Display.HelpMenu();
		HelpMenu();
	}
	else
	{
		in = strtol(Input, &pNext, 10); // convert char* to int
	
		if(in != 99) // exit settings right away
		{
			switch (in) {
  			case 1:
    			Display.CreatePipelineHelp();
    			HelpMenuInput(in);
    			break;
    		case 2:
    			Display.ExtrasHelp();
    			HelpMenuInput(in);
    			break;
    		case 3: 
				Display.SettingsHelp();
				HelpMenuInput(in);
				break;
			case 4:
				Display.AvailableCmds();
				HelpMenuInput(in);
				break;	
			case 5:
				cout << "Display Info on something?\n";
				// FIXME
				break;
			case 6:
				cout << "Display Info About the Creator\n";
				Display.AboutCreator();
				HelpMenuInput(in);
				break;
			
	  		default:
				cout << "Unknown Value...\n";
				break;
  			}
		Display.HelpMenu();
  		HelpMenu();
		} // end if 99
	} // end else
}

void User_Interface::ExtrasMenu()
{
	char LS[] = "ls", EXIT[] = "exit", QUIT[] = "quit", HELP[] = "help", PWD[] = "pwd";
	char Input[5], *pNext;
	int in;
	
	printf("Extras > "); scanf("%s",Input);
	
	if(strcmp(Input, LS) == 0)
	{
		system("ls");
		Display.ExtrasMenu();
		ExtrasMenu();
	}
	else if(strcmp(Input, PWD) == 0)
	{
		system("pwd");
		Display.ExtrasMenu();
		ExtrasMenu();
	}
	else if(strcmp(Input, EXIT) == 0) exit(1);
	else if(strcmp(Input, QUIT) == 0) exit(1);
	else if(strcmp(Input, HELP) == 0)
	{
		Display.ExtrasHelp();
   		HelpMenuInput(2);
   		Display.ExtrasMenu();
    	ExtrasMenu();
	}
	else
	{
		in = strtol(Input, &pNext, 10); // convert char* to int
	
		if(in != 99) // exit settings right away
		{
			switch (in) {
  			case 1:
				Display.PlanetParamsMenu();
				PlanetParams();
    			break;
    		case 2:
    			cout << "Radian <-> Arcmin/sec Conversion \n";
    			//Display.ExtrasHelp();
    			//ExtrasHelp();
    			break;
    		
	  		default:
				cout << "Unknown Value...\n";
				break;
  			}
		Display.ExtrasMenu();
  		ExtrasMenu();
		} // end if 99
	} // end else
}



void User_Interface::PlanetParams()
{
	char LS[] = "ls", EXIT[] = "exit", QUIT[] = "quit", HELP[] = "help", PWD[] = "pwd";
	char Input[5], *pNext;
	int in;
	
	printf("Menu > "); scanf("%s",Input);
	
	if(strcmp(Input, LS) == 0)
	{
		system("ls");
		Display.HelpMenu();
		HelpMenu();
	}
	else if(strcmp(Input, PWD) == 0)
	{
		system("pwd");
		Display.HelpMenu();
		HelpMenu();
	}
	else if(strcmp(Input, EXIT) == 0) exit(1);
	else if(strcmp(Input, QUIT) == 0) exit(1);
	else if(strcmp(Input, HELP) == 0)
	{
		Display.HelpMenu();
		HelpMenu();
	}
	else
	{
		in = strtol(Input, &pNext, 10); // convert char* to int
	
		if(in != 99) // exit settings right away
		{
			switch (in) {
  			case 1:
  				double Mb[2], i[2], P[2], Ms[2], K[2], e[2];
    			// Prompt for inputs
    			cout << "Enter (i) inclination(deg) = "; cin >> i[0];
    			cout << "Enter inclination ERROR = "; cin >> i[1];
    			i[0] *= 2.*M_PI/360.; i[1] *= 2.*M_PI/360.; // convert to radians
    			cout << "Enter (P) orbital period(days) = "; cin >> P[0];
    			cout << "Enter orbtial period ERROR = "; cin >> P[1];
    			P[0] /= 365.24; P[1] /= 365.24; // convert to years
    			cout << "Enter (M*) mass of star(solar mass) = "; cin >> Ms[0];
    			cout << "Enter mass of star ERROR = "; cin >> Ms[1];
    			cout << "Enter velocity semi-amplitude (m/s) = "; cin >> K[0];
    			cout << "Enter velocity semi-amplitude ERROR = "; cin >> K[1];
    			cout << "Enter (e) eccentricity = "; cin >> e[0];
    			cout << "Enter eccentricity ERROR = "; cin >> e[1];
    			Func.CalcMass(Mb, i, P, Ms, K, e);
    			Display.PlanetMass(Mb, i, P, Ms, K, e);
    			HelpMenuInput(8);	
    			break;
    		case 2:
    			// Prompt for inputs
    			double Rp[2], RpRs[2], Rs[2];
    			cout << "Enter Rp/R* = "; cin >> RpRs[0];
    			cout << "Enter Rp/R* ERROR = "; cin >> RpRs[1];
    			cout << "Enter radius of the host star(solar radii) = "; cin >> Rs[0];
    			cout << "Enter radius of host star ERROR = "; cin >> Rs[1];
    			Func.CalcRadius(Rp, RpRs, Rs);
    			Display.PlanetRadius(Rp, RpRs, Rs);
    			HelpMenuInput(8);
    			break;
    		case 3: 
    		// Prompt for inputs void CalcSemiMajorAxis(double *a,double *aRs,double *Rs);
                double a[2], aRs[2];
                cout << "Enter a/R* = "; cin >> aRs[0];
                cout << "Enter a/R* ERROR = "; cin >> aRs[1];
                cout << "Enter radius of the host star(solar radii) = "; cin >> Rs[0];
    			cout << "Enter radius of host star ERROR = "; cin >> Rs[1];
                Func.CalcSemiMajorAxis(a,aRs,Rs);
                Display.PlanetSemiMajor(a,aRs,Rs);
                HelpMenuInput(8);
				break;
			case 4:
                double Mp[2], pb[2];
                cout << "Enter mass of planet (M_jup) = "; cin >> Mp[0];
                cout << "Enter mass of planet ERROR = "; cin >> Mp[1];
                cout << "Enter radius of planet (R_jup) = "; cin >> Rp[0];
                cout << "Enter radius of planet ERROR = "; cin >> Rp[1];
                Func.CalcDensity(pb,Mp,Rp);
                Display.PlanetDensity(pb,Mp,Rp);
                HelpMenuInput(8);
				break;	
			case 5:
                double Teff[2], Teq[2];
                cout << "Enter effective temp of star (K) = "; cin >> Teff[0];
                cout << "Enter effective temp of star ERROR = "; cin >> Teff[1];
                cout << "Enter a/R* = "; cin >> aRs[0];
                cout << "Enter a/R* ERROR = "; cin >> aRs[1];
                Func.CalcTemp1(Teff,Teq,aRs);
                Display.PlanetTemp(Teff,Teq,aRs);
                HelpMenuInput(8);
				break;
			case 6:
                // mass, radius, semi-major, density, eq temp, safronov, surface grav, stdensity, sdensity
                double SN[2];
                cout << "Enter mass of planet (M_jup) = "; cin >> Mp[0];
                cout << "Enter mass of planet ERROR = "; cin >> Mp[1];
                cout << "Enter semi-major axis (AU) = "; cin >> a[0];
                cout << "Enter semi-major axis ERROR = "; cin >> a[1];
                cout << "Enter mass of star(solar mass) = "; cin >> Ms[0];
    			cout << "Enter mass of star ERROR = "; cin >> Ms[1];
                cout << "Enter radius of planet (R_jup) = "; cin >> Rp[0];
                cout << "Enter radius of planet ERROR = "; cin >> Rp[1];
                Func.CalcSafronovNum(SN,Mp,a,Ms,Rp);
                Display.SafronovNUM(SN,Mp,a,Ms,Rp);
                HelpMenuInput(8);
				break;
            case 7:
                double sg[2];
                cout << "Enter (P) orbital period(days) = "; cin >> P[0];
    			cout << "Enter orbtial period ERROR = "; cin >> P[1];
                cout << "Enter semi-major axis (AU) = "; cin >> a[0];
                cout << "Enter semi-major axis ERROR = "; cin >> a[1];
                cout << "Enter radius of planet (R_jup) = "; cin >> Rp[0];
                cout << "Enter radius of planet ERROR = "; cin >> Rp[1];
                cout << "Enter (i) inclination(deg) = "; cin >> i[0];
    			cout << "Enter inclination ERROR = "; cin >> i[1];
    			i[0] *= 2.*M_PI/360.; i[1] *= 2.*M_PI/360.; // convert to radians
                cout << "Enter (e) eccentricity = "; cin >> e[0];
    			cout << "Enter eccentricity ERROR = "; cin >> e[1];
                cout << "Enter velocity semi-amplitude (m/s) = "; cin >> K[0];
    			cout << "Enter velocity semi-amplitude ERROR = "; cin >> K[1];
                Func.CalcSurfaceGrav(sg,P,a,Rp,i,e,K);
                Display.SurfaceGrav(sg,P,a,Rp,i,e,K);
                HelpMenuInput(8);
                break;
            case 8:
                double ps[2];
                cout << "Enter mass of star(solar mass) = "; cin >> Ms[0];
    			cout << "Enter mass of star ERROR = "; cin >> Ms[1];
                cout << "Enter radius of the host star(solar radii) = "; cin >> Rs[0];
    			cout << "Enter radius of host star ERROR = "; cin >> Rs[1];
                Func.CalcSDensity(ps,Ms,Rs);
                Display.StellarDensity1(ps,Ms,Rs);
                HelpMenuInput(8);
                break;
			case 9:
                cout << "Enter (P) orbital period(days) = "; cin >> P[0];
                cout << "Enter orbtial period ERROR = "; cin >> P[1];
                cout << "Enter a/R* = "; cin >> aRs[0];
                cout << "Enter a/R* ERROR = "; cin >> aRs[1];
                cout << "Enter density of planet (g/cm^3) = "; cin >> pb[0];
                cout << "Enter density of planet ERROR = "; cin >> pb[1];
                cout << "Enter Rp/R* = "; cin >> RpRs[0];
    			cout << "Enter Rp/R* ERROR = "; cin >> RpRs[1];
                Func.CalcStellarDensity(ps,P,aRs,pb,RpRs);
                Display.StellarDensity2(ps,P,aRs,pb,RpRs);
                HelpMenuInput(8);
	  		default:
				cout << "Unknown Value...\n";
				break;
  			}
		Display.PlanetParamsMenu();
  		PlanetParams();
		} // end if 99
	} // end else
}





void User_Interface::HelpMenuInput(int i)
{
	char LS[] = "ls", EXIT[] = "exit", QUIT[] = "quit", HELP[] = "help", PWD[] = "pwd", UPDATE[]="update";
	char Input[5], *pNext;
	int in;
	
	printf("Menu > "); scanf("%s",Input);
	
	if(strcmp(Input, LS) == 0)
	{
		system("ls");
		if(i == 1)
		{
			Display.CreatePipelineHelp();
			HelpMenuInput(i);
		}
		else if(i == 2)
		{
    		Display.ExtrasHelp();
   			HelpMenuInput(i);
		}
		else if(i == 3)
		{
			Display.SettingsHelp();
			HelpMenuInput(i);
		}
		else if(i == 4)
		{
			Display.AvailableCmds();
			HelpMenuInput(i);
		}
		else if(i == 6)
		{
			Display.AboutCreator();
			HelpMenuInput(i);
		}
		else if(i == 7)
		{
			Display.PrelimCreated();
			HelpMenuInput(i);
		}
	}
	else if(strcmp(Input, PWD) == 0)
	{
		system("pwd");
		if(i == 1)
		{
			Display.CreatePipelineHelp();
			HelpMenuInput(i);
		}
		else if(i == 2)
		{
    		Display.ExtrasHelp();
   			HelpMenuInput(i);
		}
		else if(i == 4)
		{
			Display.AvailableCmds();
			HelpMenuInput(i);
		}
		else if(i == 6)
		{
			Display.AboutCreator();
			HelpMenuInput(i);
		}
	}
	else if(strcmp(Input, EXIT) == 0)
	{
		exit(1);
	}
	else if(strcmp(Input, QUIT) == 0)
	{
		exit(1);
	}
	else if(strcmp(Input, HELP) == 0)
	{
		Display.HelpMenu();
		HelpMenu();
	}
	else if(strcmp(Input, UPDATE) == 0 && i == 8) // type update only accessible from check update menu
	{
		cout << "Downloading Update...\n";
        Display.GetUpdate();
	}
	else
	{
		in = strtol(Input, &pNext, 10); // convert char* to int
	} // end else
}


