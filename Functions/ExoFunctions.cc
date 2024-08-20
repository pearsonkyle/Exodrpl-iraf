#define MIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })


// Read in hjd file to obtain the non-decimal portion of hjd
int Exo_Functions::GetHJD()
{
	string InFile = "hjd";
	FILE *fp1;
	int HJD;
	fp1 = fopen(InFile.c_str(), "r");
    if(fp1 == (FILE *) NULL) cerr << "ExoFn/GetHJD: problem opening file \"" << InFile <<"\"\n";
    fscanf(fp1,"%i", &HJD);
	fclose(fp1);
	return HJD;
}

// Obtains how many lines are in your designated file
int Exo_Functions::FileSize(string InFile)	
{
    FILE* fp1 = fopen(InFile.c_str(), "r");
    if(fp1 == (FILE *) NULL) cerr << "EF/FileSize: problem opening file \"" << InFile<<"\"\n";
	int count = 0;
    float in[2]; // necessary only if reading in xyfile
    char fLine[200];
    while(!feof(fp1)){ // it does not reach end of file
        fgets(fLine, 200, fp1);
        count++;
	} 
    //must minus one cus of the way the loop works or add if(!feof(fP1)) before count++
    fclose(fp1);
    return count-1;
}

// Reads in a file and copies it without the first row to a new file
void Exo_Functions::DelRow(string IN, string OUT)
{
	char firstLine[100], readLine[100];
	int status;
	FILE *fp1 = fopen(IN.c_str(),"r");
	FILE *fp2 = fopen(OUT.c_str(),"w+");
    
	if(fp1 == (FILE *) NULL) {
		cerr << "EF/DelRow: problem opening file \"" << IN <<"\"\n";
		exit(1);
	}
	if(fp2 == (FILE *) NULL) {
		cerr << "EF/DelRow: problem opening file \"" << OUT <<"\"\n";
		exit(1);
	}
	fgets(firstLine, 100, fp1);
	while(!feof(fp1)){
		fgets(readLine, 100, fp1);
		if(!feof(fp1)) fprintf(fp2, "%s", readLine);
	}
	fclose(fp1);
	//status = remove(IN.c_str()); // this deletes the in file
	if ( status == 0 ) cout << IN << " successfully deleted. " << OUT << " was created.\n";
	fclose(fp2);
}

// Read in settings and stores it to some variables that get passed to it
void Exo_Functions::ReadSettings(char *Planet, char *RA, char *Dec, float *settings)
{
	string InFile = "ExoDRPL/.Settings/.Settings.dat";
	FILE *fp1;
	// Read in settings file(Planet, RA, DEC, settings[8])
	fp1 = fopen(InFile.c_str(), "r");
    if(fp1 == (FILE *) NULL) cerr << "ExoFn/ReadSettings: problem opening file \"" << InFile <<"\"\n";
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
}

// Reads in Advanced Settings and stores variables
void Exo_Functions::ReadAdvSettings(char *trim, char *flat, char *bias, float *Advsettings)
{
	string InFile2 = "ExoDRPL/.Settings/.AdvSettings.dat";
	FILE *fp2;
	// Read in advsettings file(TrimSection, flat, bias, Advsettings[8])
	fp2 = fopen(InFile2.c_str(), "r");
    if(fp2 == (FILE *) NULL) cerr << "ExoFn/Create Prelim: problem opening file \"" << InFile2 <<"\"\n";
    fscanf(fp2,"%f\n", &Advsettings[0]); // Trim y/n?
   	fgets(trim, 20, fp2);
   	fgets(flat, 20, fp2);
   	fgets(bias, 20, fp2);
    if (trim[strlen(trim)-1] == '\n' || trim[strlen(trim)-1] == '\r') trim[strlen(trim)-1] = '\0';
    if (flat[strlen(flat)-1] == '\n' || flat[strlen(flat)-1] == '\r') flat[strlen(flat)-1] = '\0';
    if (bias[strlen(bias)-1] == '\n' || bias[strlen(bias)-1] == '\r') bias[strlen(bias)-1] = '\0';
	fscanf(fp2,"%f", &Advsettings[1]); // Average FWHM
	fclose(fp2);
}

// Reads in Advanced Settings and stores variables
void Exo_Functions::ReadAdvSettings(char *trim, char *flat, char *bias, char *sky, float *Advsettings)
{
	string InFile2 = "ExoDRPL/.Settings/.AdvSettings.dat";
	FILE *fp2;
	// Read in advsettings file(TrimSection, flat, bias,sky, Advsettings[8])
	fp2 = fopen(InFile2.c_str(), "r");
    if(fp2 == (FILE *) NULL) cerr << "ExoFn/Create Prelim: problem opening file \"" << InFile2 <<"\"\n";
    
	fscanf(fp2,"%f\n", &Advsettings[0]); // Trim y/n?
    fgets(trim, 20, fp2);
    fgets(flat, 20, fp2);
    fgets(bias, 20, fp2);
    fscanf(fp2,"%f\n",&Advsettings[1]); // FWHM
    fgets(sky, 20, fp2);
    if (trim[strlen(trim)-1] == '\n' || trim[strlen(trim)-1] == '\r') trim[strlen(trim)-1] = '\0';
    if (flat[strlen(flat)-1] == '\n' || flat[strlen(flat)-1] == '\r') flat[strlen(flat)-1] = '\0';
    if (bias[strlen(bias)-1] == '\n' || bias[strlen(bias)-1] == '\r') bias[strlen(bias)-1] = '\0';
    if (sky[strlen(sky)-1] == '\n' || sky[strlen(sky)-1] == '\r') sky[strlen(sky)-1] = '\0';
    
	fclose(fp2);
}

// Reads in Advanced Settings and stores variables
void Exo_Functions::ReadAdvSettings3(char *trim,char *flat,char *bias,char *sky1,char *sky2,char *sky3,float *Advsettings)
{
	string InFile2 = "ExoDRPL/.Settings/.AdvSettings.dat";
	FILE *fp2;
	// Read in advsettings file(TrimSection, flat, bias,sky, Advsettings[8])
	fp2 = fopen(InFile2.c_str(), "r");
    if(fp2 == (FILE *) NULL) cerr << "ExoFn/Create Prelim: problem opening file \"" << InFile2 <<"\"\n";
    
	fscanf(fp2,"%f\n", &Advsettings[0]); // Trim y/n?
    fgets(trim, 20, fp2);
    fgets(flat, 20, fp2);
    fgets(bias, 20, fp2);
    fscanf(fp2,"%f\n",&Advsettings[1]); // FWHM
    fgets(sky1, 20, fp2);
    fgets(sky2, 20, fp2);
    fgets(sky3, 20, fp2);
    if (trim[strlen(trim)-1] == '\n' || trim[strlen(trim)-1] == '\r') trim[strlen(trim)-1] = '\0';
    if (flat[strlen(flat)-1] == '\n' || flat[strlen(flat)-1] == '\r') flat[strlen(flat)-1] = '\0';
    if (bias[strlen(bias)-1] == '\n' || bias[strlen(bias)-1] == '\r') bias[strlen(bias)-1] = '\0';
    if (sky1[strlen(sky1)-1] == '\n' || sky1[strlen(sky1)-1] == '\r') sky1[strlen(sky1)-1] = '\0';
    if (sky2[strlen(sky2)-1] == '\n' || sky2[strlen(sky2)-1] == '\r') sky2[strlen(sky2)-1] = '\0';
    if (sky3[strlen(sky3)-1] == '\n' || sky3[strlen(sky3)-1] == '\r') sky3[strlen(sky3)-1] = '\0';
    
	fclose(fp2);
}

void Exo_Functions::SetSkySection(string section)
{
	char trim[20]={'\0'},bias[20]={'\0'},flat[20]={'\0'},sky1[20]={'\0'},sky2[20]={'\0'},sky3[20]={'\0'};
	float Advsettings[8];
    int sky;
	ReadAdvSettings3(trim,flat,bias,sky1,sky2,sky3,Advsettings);
	// open adv settings and print
	
	// Write New settings to file
	FILE *fp1 = fopen("ExoDRPL/.Settings/.AdvSettings.dat", "w");
    if(fp1 == (FILE *) NULL) cerr << "EF/SetSkySect: problem opening file \"" << "advsettings" <<"\"\n";
    
    fprintf(fp1,"%0.0f\n",Advsettings[0]);
   	fprintf(fp1,"%s\n",trim);
    fprintf(fp1,"%s\n",flat);
    fprintf(fp1,"%s\n",bias);
    fprintf(fp1,"%0.2f\n",Advsettings[1]);
       
    if(strcmp("x1:x2,y1:y2", sky1) == 0) // if they are the same
    {
    	fprintf(fp1,"%s\n",section.c_str());
    	fprintf(fp1,"%s\n",sky2);
    	fprintf(fp1,"%s",sky3);
    }
    else if(strcmp("x1:x2,y1:y2", sky2) == 0)
    {
    	fprintf(fp1,"%s\n",sky1);
    	fprintf(fp1,"%s\n",section.c_str());
    	fprintf(fp1,"%s",sky3);
    }
    else if(strcmp("x1:x2,y1:y2", sky3) == 0)
    {
    	fprintf(fp1,"%s\n",sky1);
    	fprintf(fp1,"%s\n",sky2);
    	fprintf(fp1,"%s",section.c_str());
    }
    else
    {
        int check = 0; // check to make sure we have a valid answer
        while(check == 0)
        {
            cout << "which skysection do you want to set? 1,2 or 3? \n > ";       
            cin >> sky;
            if(sky == 1)
            {
                fprintf(fp1,"%s\n",section.c_str());
    	        fprintf(fp1,"%s\n",sky2);
    	        fprintf(fp1,"%s",sky3);
                check = 1; // get out of loop
            }
            else if(sky == 2)
            {
    	        fprintf(fp1,"%s\n",sky1);
    	        fprintf(fp1,"%s\n",section.c_str());
    	        fprintf(fp1,"%s",sky3);  
                check = 1;              
            }
            else if(sky == 3)
            {
                fprintf(fp1,"%s\n",sky1);
    	        fprintf(fp1,"%s\n",sky2);
    	        fprintf(fp1,"%s",section.c_str());
                check = 1;
            }
            //else repeat the steps again..
        }
    }//end else
   
    fclose(fp1);
}


void Exo_Functions::SetSkySection(string section, int NUM)
{
	char trim[20]={'\0'},bias[20]={'\0'},flat[20]={'\0'},sky1[20]={'\0'},sky2[20]={'\0'},sky3[20]={'\0'};
	float Advsettings[8];
    int sky;
	ReadAdvSettings3(trim,flat,bias,sky1,sky2,sky3,Advsettings);
	// open adv settings and print
	
	// Write New settings to file
	FILE *fp1 = fopen("ExoDRPL/.Settings/.AdvSettings.dat", "w");
    if(fp1 == (FILE *) NULL) cerr << "EF/SetSkySect: problem opening file \"" << "advsettings" <<"\"\n";
    
    fprintf(fp1,"%0.0f\n",Advsettings[0]);
   	fprintf(fp1,"%s\n",trim);
    fprintf(fp1,"%s\n",flat);
    fprintf(fp1,"%s\n",bias);
    fprintf(fp1,"%0.2f\n",Advsettings[1]);
    
    if(NUM == 1) 
    {
    	fprintf(fp1,"%s\n",section.c_str());
    	fprintf(fp1,"%s\n",sky2);
    	fprintf(fp1,"%s",sky3);
    }
    else if(NUM == 2)
    {
    	fprintf(fp1,"%s\n",sky1);
    	fprintf(fp1,"%s\n",section.c_str());
    	fprintf(fp1,"%s",sky3);
    }
    else if(NUM == 3)
    {
    	fprintf(fp1,"%s\n",sky1);
    	fprintf(fp1,"%s\n",sky2);
    	fprintf(fp1,"%s",section.c_str());
    }
    fclose(fp1);
}



void Exo_Functions::CreateCleanUp()
{
	// May need to update
	FILE *fp = fopen("ExoCleanUp.cl","w+");
	fprintf(fp,"!rm AfterAnalyze.cl\n");
	fprintf(fp,"!rm -rf AllfluxFiles/\n");
	fprintf(fp,"!rm -rf bias/\n");
	fprintf(fp,"!rm -rf bias.R.00/\n");
	fprintf(fp,"!rm -rf B-images/\n");
	fprintf(fp,"!rm -rf FB-images/\n");
	fprintf(fp,"!rm -rf flats/\n");
	fprintf(fp,"!rm -rf mag*\n");
	fprintf(fp,"!rm Nsuperflat.fits\n");
	fprintf(fp,"!rm PlotLC*\n");
	fprintf(fp,"!rm skysigma*.dat\n");
	fprintf(fp,"!rm UpdateVersion.dat\n");
	fclose(fp);
}

// reads in skyfile and returns the STDEV ./ExoDRPL skysigma  writes it out to a file
float Exo_Functions::GetSkySigma() // possibly change this to read in an arbitrary file
{
	float s1,s2,s3;  
    FILE *fp1 = fopen("skysigma1.dat", "r");
	if(fp1 != (FILE *) NULL) // scan # if file exists
    {
        fscanf(fp1,"%f",&s1);
        fclose(fp1);
    }

    fp1 = fopen("skysigma2.dat", "r");
    if(fp1 != (FILE *) NULL) 
    {
        fscanf(fp1,"%f",&s2);
        fclose(fp1);
    }

    fp1 = fopen("skysigma3.dat", "r");
    if(fp1 != (FILE *) NULL) 
    {
        fscanf(fp1,"%f",&s3);
        fclose(fp1);
    }

	return MIN(MIN(s1,s2),s3);
}

int Exo_Functions::CheckSky(string section)
{   
    float x1,x2,y1,y2; 
    sscanf(section.c_str(),"%f:%f,%f:%f",&x1,&x2,&y1,&y2);
    if(x1==0 || x2==0 || y1==0 || y2==0) return 0; //bad section
    else return 1; // all good
}

