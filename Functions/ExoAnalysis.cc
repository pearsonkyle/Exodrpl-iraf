
// Analyze ExoPreResults to determine best aperture + reference star combo + gets Errors
void Exo_Functions::AnalyzeResults()
{
	system("rm -rf Results");
	system("mkdir Results");
	// Read Settings to get planet
	char Planet[20] = {'\0'}, RA[20] = {'\0'}, Dec[20] = {'\0'};
	float settings[8];
	ReadSettings(Planet, RA, Dec, settings);
	enum{min, max, precision, ann, dann, ingress, egress}Settings;
	
	// Create filename to open planet.list to obtain all the images
	string PlanetList = "FB";
	PlanetList = PlanetList.append(Planet);
	PlanetList = PlanetList.append(".list");
	
	// more variables needed for array allocation
	int numimages = FileSize(PlanetList), slen;
	int stars = FileSize("xyfile");
	
	// *********************************************
	// *********** GET REFERENCE STARS *************
	// ********************************************* 
	
	// Stores Best Combo for ingress, egress + both
	int iBest[6], eBest[6], bBest[6], iCom[6], eCom[6], bCom[6]; 
	for(int i=0;i<6;i++) // Zero this just in case 
	{
		iCom[i] = 0; eCom[i] = 0; bCom[i] = 0;
		iBest[i] = 0; eBest[i] = 0; bBest[0] = 0; 
	}

	float STDEV[3] = {0,0,0};
	float minSTD[3] = {10,10,10};
	char iFile[20], eFile[20], bFile[20]; // stores best allflux file
	char ReadLine[32], FileLine[25]; // To Read Past lines in ExoPreResults
	
	string ResultsFile = "ExoPreResults.txt";
	FILE *fp = fopen(ResultsFile.c_str(),"r"); // Reads in ExoPreResults.txt
	if(fp == (FILE *) NULL) cerr << "EF/PreAnalyze: problem opening file \"" << ResultsFile <<"\"\n";
	
	do
	{
	fgets(ReadLine,7,fp); //fgets(FileLine, 25, fp); 
	fscanf(fp, "%s \n", FileLine);
	if (FileLine[strlen(FileLine)-1] == '\n' || FileLine[strlen(FileLine)-1] == '\r') FileLine[strlen(FileLine)-1] = '\0';
	fgets(ReadLine, 20, fp); fscanf(fp, "%d %d %d %d %d %d\n", &iCom[0], &iCom[1], &iCom[2], &iCom[3], &iCom[4], &iCom[5]); //i Combo	
	fgets(ReadLine, 25, fp); 
	fscanf(fp, "%f\n", &STDEV[0]); // Reads in Ingress STDEV
	fgets(ReadLine, 19, fp); fscanf(fp, "%d %d %d %d %d %d\n", &eCom[0], &eCom[1], &eCom[2], &eCom[3], &eCom[4], &eCom[5]); //e Combo
	fgets(ReadLine, 24, fp); fscanf(fp, "%f\n", &STDEV[1]); // Reads in Egress STDEV
	fgets(ReadLine, 27, fp); fscanf(fp, "%d %d %d %d %d %d\n", &bCom[0], &bCom[1], &bCom[2], &bCom[3], &bCom[4], &bCom[5]); //i+e Combo
	fgets(ReadLine, 32, fp); fscanf(fp, "%f\n", &STDEV[2]); // Reads in Ingress+Egress STDEV

		// Compares for Lowest STDEV
		for(int i=0;i<3;i++)
		{
			if(STDEV[i] != 0) // to avoid errors
			{
				if(STDEV[i] < minSTD[i])
				{
					minSTD[i] = STDEV[i];
					for(int j=0;j<6;j++) // stores to best combo
					{
						if(i == 0) { iBest[j] = iCom[j]; strcpy(iFile,FileLine); }
						else if(i == 1){ eBest[j] = eCom[j]; strcpy(eFile,FileLine); }
						else if(i == 2){ bBest[j] = bCom[j]; strcpy(bFile,FileLine); } 
						else cout << "Chump error \n";
					}
				}
			}
		}
	}while(!feof(fp));
	
	fclose(fp); // Close ExoPreResults.txt
	
	printf(" _______________________________________________________________ \n");
	printf("                                             		ExoDRPL \n");
	printf("    Results have been analyzed!				\n\n");
	cout << "	FILE: " << iFile << "\n";
	cout << "	Minimum Ingress STDEV: " << minSTD[0] << "\n";
	cout << "	Ingress Ref Star Combo: ";
	for(int i=0;i<6;i++) if(iBest[i] != 0) cout << iBest[i] << " ";
	cout << "\n\n";
	
	cout << "	FILE: " << eFile << "\n";
	cout << "	Minimum Egress STDEV: " << minSTD[1] << "\n";
	cout << "	Egress Ref Star Combo: ";
	for(int i=0;i<6;i++) if(eBest[i] != 0) cout << eBest[i] << " ";
	cout << "\n\n";
	
	cout << "	FILE: " << bFile << "\n";
	cout << "	Minimum Ingress+Egress STDEV: " << minSTD[2] << "\n";
	cout << "	Ingress+Egress Ref Star Combo: ";
	for(int i=0;i<6;i++) if(bBest[i] != 0) cout << bBest[i] << " ";
	cout << "\n\n";

	// Write results to File
	ResultsFile = "ExoResults.txt";
	fp = fopen(ResultsFile.c_str(),"w+"); // Reads in ExoPreResults.txt
	
	fprintf(fp,"FINAL REFERENCE STAR RESULTS\n\n");
	fprintf(fp,"FILE: %s \nMinimum Ingress STDEV: %f\nIngress Ref Star Combo: ",iFile, minSTD[0]);
	for(int i=0;i<6;i++) 
	{ 
		if(iBest[i] != 0){
	 		fprintf(fp, "%d",iBest[i]);
	 		if(iBest[i] == 1) fprintf(fp, "st ");
	 		if(iBest[i] == 2) fprintf(fp, "nd ");
	 		if(iBest[i] == 3) fprintf(fp, "rd ");
	 		if(iBest[i] >= 4) fprintf(fp, "th ");
	 	}
	}
	//fprintf(fp,"\nPossible Variable Reference Stars:");
	fprintf(fp,"\n\n");
	fprintf(fp,"FILE: %s \nMinimum Egress STDEV: %f\nEgress Ref Star Combo: ",eFile, minSTD[1]);
	for(int i=0;i<6;i++) 
	{ 
		if(eBest[i] != 0){
	 		fprintf(fp, "%d",eBest[i]);
	 		if(eBest[i] == 1) fprintf(fp, "st ");
	 		if(eBest[i] == 2) fprintf(fp, "nd ");
	 		if(eBest[i] == 3) fprintf(fp, "rd ");
	 		if(eBest[i] >= 4) fprintf(fp, "th ");
	 	}
	}
	fprintf(fp,"\n\n");
	fprintf(fp,"FILE: %s \nMinimum Ingress+Egress STDEV: %f\nIngress+Egress Ref Star Combo: ",bFile, minSTD[2]);
	for(int i=0;i<6;i++) 
	{ 
		if(bBest[i] != 0){
	 		fprintf(fp, "%d",bBest[i]);
	 		if(bBest[i] == 1) fprintf(fp, "st ");
	 		if(bBest[i] == 2) fprintf(fp, "nd ");
	 		if(bBest[i] == 3) fprintf(fp, "rd ");
	 		if(bBest[i] >= 4) fprintf(fp, "th ");
	 	}
	}
	fprintf(fp,"\n\n");
	fprintf(fp,"INFO: Your 1st reference star corresponds to the second column in your allflux file\n");
	fprintf(fp,"Suggestion: Go with the combo that reduces the scatter at the highest airmass\n");
	fclose(fp);

	cout << "	Results are summarized in: "<< ResultsFile << "\n";
	
	// *********************************************
	// *********** PREPARE LIGHTCURVE **************
	// ********************************************* 
	
	// Read in RHJD
	float rhjd[numimages];
	fp = fopen("rhjd","r");
	if( fp == (FILE *) NULL) cerr << "EF/Analyze:problem opening file \"" << "rhjd" <<"\"\n";
    int q = 0; // keeps track of rows in allflux
   	do{
		fscanf(fp, "%f\n", &rhjd[q]);
		q++;
   		} while(!feof(fp));
    fclose(fp);
    
	
	// Files names for allflux, allfluxerr, Lightcurve + NLC
	string Allflux[] = {iFile, eFile, bFile}, Allfluxerr[3], prefix, suffix, LCfile[3], NLCfile[3];
	string PlotFile[3] = {"PlotLC1.cl","PlotLC2.cl","PlotLC3.cl"}, Modelfile[3];
	for(int i=0;i<3;i++)
	{
		prefix = Allflux[i].substr(0,7);
		suffix = Allflux[i].substr(7,5);
		Allfluxerr[i] = prefix.append("err");
		Allfluxerr[i] = Allfluxerr[i].append(suffix);
		prefix = "ExoLC";
		LCfile[i] = prefix.append(suffix);
		LCfile[i] = LCfile[i].append(".txt");
		
		prefix = "ExoNLC";
		NLCfile[i] = prefix.append(suffix);
		NLCfile[i] = NLCfile[i].append(".txt");
		
		prefix = "ModelLC";
		Modelfile[i] = prefix.append(suffix);
		Modelfile[i] = Modelfile[i].append(".dat");
	}
		
	// initialize array to store allflux data
	double **allflux, **allfluxerr;
	allflux = AllocArray<double>(stars,numimages);
	allfluxerr = AllocArray<double>(stars,numimages);
	
	// Reallocate Memory for optimization
	double LightCurve[3][numimages], NormLC[3][numimages]; // Lightcurve + normalized lightcurve
	double ErrorBars[3][numimages], NormError[3][numimages];
	int RefStar[3][6];
	for(int j=0;j<3;j++) for(int i=0;i<6;i++) RefStar[j][i] = iBest[i];
	FILE *fpA[3];
	FILE *fpE[3];
	
	#pragma omp parallel for schedule(dynamic,1)
	for(int i=0;i<3;i++)
	{
	
		// Read in Allflux data store to array
		fpA[i] = fopen(Allflux[i].c_str(),"r");
		if( fpA[i] == (FILE *) NULL) cerr << "EF/Analyze:problem opening file \"" << Allflux[i] <<"\"\n";
        int k = 0; // keeps track of rows in allflux
   		do{
   			for(int j=0;j<stars;j++) fscanf(fpA[i], "%le", &allflux[j][k]);
   			k++;
   		} while(!feof(fpA[i]));
    	fclose(fpA[i]);
    	
    	// Read in Allfluxerr data store to array
    	fpE[i] = fopen(Allfluxerr[i].c_str(),"r");
		if( fpE[i] == (FILE *) NULL) cerr << "EF/Analyze:problem opening file \"" << Allfluxerr[i] <<"\"\n";
        k = 0; // keeps track of rows in allflux
   		do{
   			for(int j=0;j<stars;j++) fscanf(fpE[i], "%le", &allfluxerr[j][k]);
   			k++;
   		} while(!feof(fpE[i]));
    	fclose(fpE[i]);
    	
    	for(int n=0;n<numimages;n++) LightCurve[i][n] = 0; // cleanse before computation...just in case
    	
    	// loop through RefStar[i][#] for # ref stars
        // Calculations error bars and lightcurve
    	k = 0;
    	while(RefStar[i][k] != 0) k++; // tells you how many stars for combination
    	
    	for(int j=0;j<k;j++) // loop thru ref stars to get total flux from ref stars
    	{
    		for(int n=0;n<numimages;n++)
    		{
    			LightCurve[i][n] += allflux[(RefStar[i][j])][n]; 
		    }	
    	}

        for(int j=0;j<k;j++) // loop thru ref stars to calc error bars 
    	{
    		for(int n=0;n<numimages;n++)
    		{
                if(j == 0)
                {
                    ErrorBars[i][n] = k*k*allfluxerr[0][n]*allfluxerr[0][n]/(LightCurve[i][n]*LightCurve[i][n]);
		            ErrorBars[i][n]+= k*k*allflux[0][n]*allflux[0][n]*allfluxerr[(RefStar[i][j])][n]*allfluxerr[(RefStar[i][j])][n]/pow(LightCurve[i][n],4.);
                }
                else ErrorBars[i][n]+= k*k*allflux[0][n]*allflux[0][n]*allfluxerr[(RefStar[i][j])][n]*allfluxerr[(RefStar[i][j])][n]/pow(LightCurve[i][n],4.);
            }
        }

    	// Create Light Curve + Errors
    	for(int n=0;n<numimages;n++) 
    	{
    		ErrorBars[i][n] = sqrt(ErrorBars[i][n]);
    		LightCurve[i][n] = allflux[0][n]/(LightCurve[i][n]/k); // divide host flux by all ref star flux
    	}
    	
    	// Get Out of Transit Baseline Average
		for(int n=numimages-settings[egress];n<numimages;n++) STDEV[i] += LightCurve[i][n]; // reuse this variable as average
		STDEV[i] /= settings[egress];
		for(int n=0;n<numimages;n++) 
		{
			NormLC[i][n] = LightCurve[i][n]/STDEV[i];
    		NormError[i][n] = ErrorBars[i][n]/STDEV[i];
    	}
    	
    	// Creates Plotting Files
    	fpA[i] = fopen(LCfile[i].c_str(),"w+");
    	for(int n=0;n<numimages;n++) fprintf(fpA[i],"%i %f\n",n+1,LightCurve[i][n]);
    	fclose(fpA[i]);
    	
    	fpA[i] = fopen(NLCfile[i].c_str(),"w+");
		for(int n=0;n<numimages;n++) fprintf(fpA[i],"%i %f\n",n+1,NormLC[i][n]);
    	fclose(fpA[i]);
    	
    	fpA[i] = fopen(Modelfile[i].c_str(),"w+");
    	for(int n=0;n<numimages;n++) fprintf(fpA[i],"%f %f %f\n",rhjd[n],NormLC[i][n],NormError[i][n]);
    	fclose(fpA[i]);
    	
    	// Create IRAF file to do the plotting
    	fpA[i] = fopen(PlotFile[i].c_str(), "w+");
    	if(i==0) 
    	{	
    		fprintf(fpA[i],"print(\"Plotting Data for Ingress Optimized Baseline\")\n");
    		fprintf(fpA[i], "graph Results/%s title=\"%s Ingress Optimized\" xlabel=\"Data Points\" ylab=\"Relative Flux\" point+ fill+\n",NLCfile[i].c_str(),Planet);
    	}
    	if(i==1) 
    	{
    		fprintf(fpA[i],"print(\"Plotting Data for Egress Optimized Baseline\")\n");
    		fprintf(fpA[i], "graph Results/%s title=\"%s Egress Optimized\" xlabel=\"Data Points\" ylab=\"Relative Flux\" point+ fill+\n",NLCfile[i].c_str(),Planet);
    	}
    	if(i==2) 
    	{
    		fprintf(fpA[i],"print(\"Plotting Data for Ingress+Egress Optimized Baseline\")\n");
    		fprintf(fpA[i], "graph Results/%s title=\"%s Ingress+Egress Optimized\" xlabel=\"Data Points\" ylab=\"Relative Flux\" point+ fill+\n",NLCfile[i].c_str(),Planet);
    	}
    	fclose(fpA[i]);
    	
	} //end for ingress,egress,both
	
	
	printf("									\n");
	printf("	To view your plots type: (in IRAF) \n");
	printf("	Ingress Optimized: cl < PlotLC1.cl \n");
	printf("	Egress Optimized: cl < PlotLC2.cl \n");
	printf("	Both Optimized: cl < PlotLC3.cl \n");
	printf("           							\n");
	printf("	Figure out your optimal Ingress + Egress points \n");
	printf("	Change Settings in ExoDRPL \n");
	printf("	Rerun with new settings \n\n");
	printf("	Final LightCurves are in Results/ \n");
	printf("	> 99. Exit						\n");
	printf("$_______________________________________________________________$\n");
	
	// Creates Organizing IRAF script
	fp = fopen("AfterAnalyze.cl","w+");
	fprintf(fp,"mv %s %s %s Results/\n",LCfile[0].c_str(),LCfile[1].c_str(),LCfile[2].c_str());
	fprintf(fp,"mv %s %s %s Results/\n",NLCfile[0].c_str(),NLCfile[1].c_str(),NLCfile[2].c_str());
	fprintf(fp,"mv %s %s %s Results/\n",Modelfile[0].c_str(),Modelfile[1].c_str(),Modelfile[2].c_str());
	fclose(fp);
}



// *****************************************************
// ***** Organizes Files After Photometry Analysis *****
// *****************************************************
void Exo_Functions::AfterAnalyze()
{
	// Read Settings to get planet
	char Planet[20] = {'\0'}, RA[20] = {'\0'}, Dec[20] = {'\0'};
	float settings[8];
	ReadSettings(Planet, RA, Dec, settings);
	enum{min, max, precision, ann, dann, ingress, egress}Settings;

	char appendage[5] = {'\0'};
	sprintf(appendage, "%0.1f", settings[min]);
	string magdir = "mag_";
	magdir = magdir.append(appendage);

	system("rm -rf B-images");
	system("rm -rf FB-images");
	system("rm -rf AllfluxFiles");

	FILE *fp = fopen("AfterAnalyze.cl","a");
	fprintf(fp,"cp %s/star1ExtraParams Results/XYpos+Airmass.txt \n",magdir.c_str());
	
	fprintf(fp,"!mkdir B-images\n");
	fprintf(fp,"mv B%s*.fits B-images\n",Planet);
	fprintf(fp,"mv B%s*.list B-images\n",Planet);
	fprintf(fp,"mv superbias.fits B-images\n",Planet);
	
	fprintf(fp,"!mkdir FB-images\n");
	fprintf(fp,"mv FB%s*.fits FB-images\n",Planet);
	fprintf(fp,"cp FB%s*.list FB-images\n",Planet);
	
	fprintf(fp,"!mkdir AllfluxFiles\n");
	fprintf(fp,"mv allflux* AllfluxFiles\n");
	fprintf(fp,"mv photinfo_* AllfluxFiles\n");
	
	fprintf(fp,"mv rhjd hjd Results\n");
	fprintf(fp,"mv UT.txt Results\n");
	fprintf(fp,"mv ExoPreResults.txt Results\n");
	fprintf(fp,"mv ExoResults.txt Results\n");
	fprintf(fp,"!rm -rf *.list\n");
	fclose(fp);
	
	// Allows Program to Recognize Results for menu screen option
	fp = fopen("ExoDRPL/.Settings/.temp", "w+");
	fprintf(fp,"1"); fclose(fp);
}

// *****************************************************
// ******* Finds best reference Stars + Aperture *******
// *****************************************************
void Exo_Functions::LightCurveOp(string filename)
{
	// Read in settings to get Planet name, ingress, and egress
	enum{min, max, precision, ann, dann, ingress, egress}Settings;
    char Planet[20] = {'\0'}, RA[20] = {'\0'}, Dec[20] = {'\0'};
	float settings[8];
	ReadSettings(Planet, RA, Dec, settings);
	
	// Obtain sizes of things for memory allocation
	int stars = FileSize("xyfile");
	string PlanetList = "FB";
    PlanetList = PlanetList.append(Planet);
    PlanetList = PlanetList.append(".list");
    int images = FileSize(PlanetList);
    
	// initialize array to store allflux data
	double **allflux;
	allflux = AllocArray<double>(stars,images);
	
	// Read in allflux file
	FILE *fp = fopen(filename.c_str(),"r");
    if( fp == (FILE *) NULL) cerr << "EF/LCO:problem opening file \"" << filename <<"\"\n";
        
	int j = 0; // keeps track of rows in allflux
   	do{
   		
   		for(int i=0;i<stars;i++) fscanf(fp, "%le", &allflux[i][j]);
   		j++;
   	} while(!feof(fp));
    fclose(fp);
    
    /*
    // just to make sure its storing properly
    for(int j=0; j < images; j++)
    {
    	cout << j+1 << ": ";
		for(int i=0; i < stars; i++)
		{
			printf("%0.2lf ",allflux[i][j]);
		}
		cout << "\n";
	}
	*/
	
	// Variables for finding best reference star combo
	double temp[images]; // stores the temporary lightcurve
	list<int> Combo[3]; // ingress, egress, both
	double STDEV[] = {0,0,0}; //ingress, egress, both
	double minSTD[] = {10,10,10}; //stores minimum standard deviation
	
	// One Reference Star
	for(int a=1; a<stars;a++) { 
		for(int N=0; N<images; N++)
		{
			temp[N] = allflux[0][N] / allflux[a][N];
		}
		// CheckVariableStar(temp);
		// Will need to add some if statements to evaluate ref stars
		CalcSTDEV(temp, images, STDEV);
		for(int i=0;i<3;i++)
		{
			if(STDEV[i] < minSTD[i])
			{
				minSTD[i] = STDEV[i];
				Combo[i].clear();
				Combo[i].push_back(a);
			}
		}
	}
	// Only need to evaluate if a reference star is variable above and neglect it from other
	
	if(stars > 2) //Two Reference Stars
	{
		for(int a=1; a<stars;a++) { 
		for(int b=a+1; b<stars; b++) {
			// add some if statements to neglect variable stars
			for(int N=0; N<images; N++)
			{
				temp[N] = allflux[0][N] / allflux[a][N];
			}
			CalcSTDEV(temp, images, STDEV);
			for(int i=0;i<3;i++)
			{
				if(STDEV[i] < minSTD[i])
				{
					minSTD[i] = STDEV[i];
					Combo[i].clear();
					Combo[i].push_back(a);
					Combo[i].push_back(b);
				}
			}
		}
		}
	} //end if
	
	if(stars > 3) //Three Reference Stars
	{
		for(int a=1; a<stars;a++) { 
		for(int b=a+1; b<stars; b++) {
		for(int c=b+1; c<stars; c++) {
			// add some if statements to neglect variable stars
			for(int N=0; N<images; N++)
			{
				temp[N] = allflux[0][N] / allflux[a][N];
			}
			CalcSTDEV(temp, images, STDEV);
			for(int i=0;i<3;i++)
			{
				if(STDEV[i] < minSTD[i])
				{
					minSTD[i] = STDEV[i];
					Combo[i].clear();
					Combo[i].push_back(a);
					Combo[i].push_back(b);
					Combo[i].push_back(c);
				}
			}
		}
		}
		}
	} //end if
	
	if(stars > 4) //Four Reference Stars
	{
		for(int a=1; a<stars; a++) { 
		for(int b=a+1; b<stars; b++) {
		for(int c=b+1; c<stars; c++) {
		for(int d=c+1; d<stars; d++) {
			// add some if statements to neglect variable stars
			for(int N=0; N<images; N++)
			{
				temp[N] = allflux[0][N] / allflux[a][N];
			}
			CalcSTDEV(temp, images, STDEV);
			for(int i=0;i<3;i++)
			{
				if(STDEV[i] < minSTD[i])
				{
					minSTD[i] = STDEV[i];
					Combo[i].clear();
					Combo[i].push_back(a);
					Combo[i].push_back(b);
					Combo[i].push_back(c);
					Combo[i].push_back(d);
				}
			}
		}
		}
		}
		}
	} //end if
	
	if(stars > 5) //Five Reference Stars
	{
		for(int a=1; a<stars; a++) { 
		for(int b=a+1; b<stars; b++) {
		for(int c=b+1; c<stars; c++) {
		for(int d=c+1; d<stars; d++) {
		for(int e=d+1; e<stars; e++) {
			// add some if statements to neglect variable stars
			for(int N=0; N<images; N++)
			{
				temp[N] = allflux[0][N] / allflux[a][N];
			}
			CalcSTDEV(temp, images, STDEV);
			for(int i=0;i<3;i++)
			{
				if(STDEV[i] < minSTD[i])
				{
					minSTD[i] = STDEV[i];
					Combo[i].clear();
					Combo[i].push_back(a);
					Combo[i].push_back(b);
					Combo[i].push_back(c);
					Combo[i].push_back(d);
					Combo[i].push_back(e);
				}
			}
		}
		}
		}
		}
		}
	} //end if
	
	
	// File that stores results
	string ResultsFile = "ExoPreResults.txt";
	fp = fopen(ResultsFile.c_str(), "a"); // Opens ExoPreResults for appending
	fprintf(fp,"FILE: %s \n",filename.c_str());
	
	fprintf(fp,"Best Ingress Combo: ");
  	for (list<int>::iterator it=Combo[0].begin(); it != Combo[0].end(); ++it) fprintf(fp," %i", *it);
  	fprintf(fp,"\n Ingress Baseline STDEV: %f \n", minSTD[0]);
  	
  	fprintf(fp,"Best Egress Combo: ");
  	for (list<int>::iterator it=Combo[1].begin(); it != Combo[1].end(); ++it) fprintf(fp," %i", *it);
  	fprintf(fp,"\n Egress Baseline STDEV: %f \n", minSTD[1]);
  	
  	fprintf(fp,"Best Ingress+Egress Combo: ");
  	for (list<int>::iterator it=Combo[2].begin(); it != Combo[2].end(); ++it) fprintf(fp," %i", *it);
  	fprintf(fp,"\n Ingress+Egress Baseline STDEV: %f \n\n", minSTD[2]);
  	
	fclose(fp);
}



void Exo_Functions::CalcSTDEV(double *data, int images, double *STDEV)
{
	// Read Settings to get ingress and egress
	enum{min, max, precision, ann, dann, ingress, egress}Settings;
	char Planet[20] = {'\0'}, RA[20] = {'\0'}, Dec[20] = {'\0'};
	float settings[8];
	ReadSettings(Planet, RA, Dec, settings);
	
	// Variables for finding STDEV
	double Sum, Average;
	
	// Ingress STD
    for(int i=0;i<settings[ingress];i++) Sum += data[i];
    Average = Sum / settings[ingress];
    Sum = 0;
    for(int i=0;i<settings[ingress];i++) Sum += (data[i]-Average)*(data[i]-Average);
    Average = Sum / settings[ingress];
    STDEV[0] = sqrt(Average);
    
    // Egress STD
    Sum = 0; Average = 0;
    for(int i=images-settings[egress];i<images;i++) Sum += data[i];
    Average = Sum / settings[egress];
    Sum = 0;
    for(int i=images-settings[egress];i<images;i++) Sum += (data[i]-Average)*(data[i]-Average);
    Average = Sum / settings[egress];
    STDEV[1] = sqrt(Average);
    
    // Ingress+Egress STD
    Sum = 0; Average = 0;
    for(int i=0;i<settings[ingress];i++) Sum += data[i];
    for(int i=images-settings[egress];i<images;i++) Sum += data[i];
    Average = Sum / (settings[ingress]+settings[egress]);
    Sum = 0;
    for(int i=0;i<settings[ingress];i++) Sum += (data[i]-Average)*(data[i]-Average);
    for(int i=images-settings[egress];i<images;i++) Sum += (data[i]-Average)*(data[i]-Average);
    Average = Sum / (settings[ingress]+settings[egress]);
    STDEV[2] = sqrt(Average);
}

