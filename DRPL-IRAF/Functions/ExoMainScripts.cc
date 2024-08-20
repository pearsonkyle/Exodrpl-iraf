void Exo_Functions::CreateReductionScript(int Identifier)
{
	// Variables For Reading in Settings
	char Planet[20] = {'\0'}, RA[20] = {'\0'}, Dec[20] = {'\0'}, trim[20] = {'\0'};
	char flat[20]={'\0'},bias[20]={'\0'},New[20]={'\0'},sky1[20]={'\0'},sky2[20]={'\0'},sky3[20]={'\0'};
	float settings[8], Advsettings[8], skysigma;
	string InFile, newFileName;
	FILE *fp1, *fp2;
	
	// Read Settings
	ReadSettings(Planet, RA, Dec, settings);
    ReadAdvSettings3(trim,flat,bias,sky1,sky2,sky3,Advsettings);
	
	// Variables for Creating Script
	if(Identifier == 0) // Preliminary Script
	{
		newFileName = "Pre-"; 
		newFileName = newFileName.append(Planet);
		newFileName = newFileName.append(".cl");
	}
	else if(Identifier == 1) // Main Script
	{
		newFileName = "Main-"; 
		newFileName = newFileName.append(Planet);
		newFileName = newFileName.append(".cl");
	}
	else
	{
		printf("Yo this identifier is not 0(pre) or 1(main), check yo self\n");
		exit(1);
	}
	
	//printf("new File name is %s \n", newFileName.c_str());
	fp1 = fopen(newFileName.c_str(), "w+");
	if(fp1 == (FILE *) NULL) cerr << "CreateScript: problem opening file \"" << newFileName <<"\"\n";
	
	// Prefix for images that have been altered
	string imgPrefix = "B"; // be cautious b.c photinfo files need the exact name of the names being reduced (FB)
    		
    fprintf(fp1,"#TO EXECUTE: cl < %s.cl\n", Planet);
    fprintf(fp1,"\n#OTHER SCRIPTS USED:\n");
    fprintf(fp1,"#  stcoox.cl	(appends the header of images with some information)\n\n");
    fprintf(fp1,"##################### LOAD PRELIMINARY PROGRAMS ################\n");
    fprintf(fp1,"print(\"LOADING PRELIMINARY PROGRAMS...\")\n");
    fprintf(fp1,"!g++ ExoDRPL/ExoDRPL.cc -o ExoFunction \n");
    //fprintf(fp1,"!./compile-run \n");
    fprintf(fp1,"print(\"ExoFunctions Loaded!\")\n");
    fprintf(fp1,"cl < ExoDRPL/Extras/ExoSetupTaskParameters.cl\n");
    fprintf(fp1,"print(\"Initial Parameters Set\") \n");
    fprintf(fp1,"print(\"Cleaning up old files\")\n");
    fprintf(fp1,"cl < ExoDRPL/Extras/ExoCleanUp.cl\n\n"); // Make this file
    
    if(Advsettings[0] == 1)
    {
    	// have it append T on to the name of the images or something
		// Add Trim options for images,flats,bias
		fprintf(fp1,"##################### TRIM IMAGES #####################\n");	
    } 
    // 0 - Off
	// 1 - Trim all images
	// 2 - Trim Planet images only
	// 3 - Trim bias images only
	// 4 - Trim flat images only
	// 5 - Trim P+B only
	// 6 - Trim P+F only
	// 7 - Trim B+F only
   
    fprintf(fp1,"##################### CREATE A SUPER BIAS #####################\n");
    fprintf(fp1,"print(\"CREATING A SUPER BIAS...\")\n");
    fprintf(fp1,"mkdir bias				# makes directory to put bias fits in\n");
    fprintf(fp1,"cp %s*.fits bias			# copies biases into bias dir/folder\n",bias);
    fprintf(fp1,"cd bias					# changes directory to bias folder\n");
    fprintf(fp1,"ls %s*.fits > bias.list		# creates a list of all the bias fits files\n",bias);
    fprintf(fp1,"imcombine @bias.list superbias.fits	# combine bias files into superbias file\n");
    fprintf(fp1,"cp superbias.fits ../			# copies superbias up a directory\n");
    fprintf(fp1,"cd ../					# changes directory, goes up a directory\n");
    fprintf(fp1,"print(\"SUPER BIAS CREATED.\")\n\n");
    fprintf(fp1,"##################### SUBTRACT SUPERBIAS FROM ALL THE IMAGES #####################\n");
    fprintf(fp1,"ls %s*.fits > %s.list				#creates a list of all the %s*.fits\n", Planet, Planet, Planet);
    fprintf(fp1,"touch B%s.list						#creates a blank list for B%s*.fits\n", Planet, Planet);
   //fprintf(fp1,"!./ExoAppend Append %s.list B%s.list B\n", Planet.c_str(), Planet.c_str(), Planet.c_str());
    fprintf(fp1,"!awk '{d=$1; print\"B\"d}' %s.list > B%s.list\n", Planet,Planet);
    fprintf(fp1,"print(\"SUBTRACTING SUPERBIAS FROM ALL IMAGES...\")\n");
    fprintf(fp1,"imarith @%s.list - superbias.fits @B%s.list		#subtracts superbias from all images, new files \n", Planet, Planet);
    fprintf(fp1,"print(\"QUIRYING IMAGE STATS\")\n");
    fprintf(fp1,"imstat %s*0001.fits					#used to check if STDEV is different\n", Planet);
    fprintf(fp1,"imstat B%s*0001.fits	#used to check if STDEV is different\n\n", Planet);
    fprintf(fp1,"###################### SUBTRACT SUPERBIAS FROM FLATS ######################\n");
    fprintf(fp1,"mkdir flats							# makes directory for flat files\n");
    fprintf(fp1,"cp flat.*.fits flats						# copies flat fits into flats dir\n");
    fprintf(fp1,"cp superbias.fits flats					# copies superbias to flats dir\n");
    fprintf(fp1,"ls flat.*.fits > flat.list					# creates a list of all the flat fits\n");
    fprintf(fp1,"cp flat.list flats						# copies flat list into flats\n");
    fprintf(fp1,"touch Bflat.list						# creates a blank list for Bflat files\n");
    //fprintf(fp1,"!./ExoAppend Append flat.list Bflat.list B\n");
    fprintf(fp1,"!awk '{d=$1; print\"B\"d}' flat.list > Bflat.list\n");
    //fprintf(fp1,"cp ExoDel flats							# copy DelRow to flats dir\n");
    //fprintf(fp1,"cp ExoAppend flats							# copy AppendChar to flats dir\n");
    fprintf(fp1,"cp ExoFunction flats							# copy ExoFunctions to flats dir\n");
    fprintf(fp1,"cp Bflat.list flats						# copy Bflat list to flats dir\n");
    fprintf(fp1,"cd flats							# changes to flats directory\n");
    fprintf(fp1,"print(\"SUBTRACTING SUPERBIAS FROM FLATS...\")\n");
    fprintf(fp1,"imarith @flat.list - superbias.fits @Bflat.list			# subtracts superbias from flats, new files\n\n");
    fprintf(fp1,"###################### CREATE A SUPERFLAT ###################### \n");
    fprintf(fp1,"unlearn imstat\n");
    fprintf(fp1,"imstat @Bflat.list > statflat.list				# creates a list of stats about bias images\n");
    fprintf(fp1,"!awk '{d=$3;print d}' statflat.list > temp.list\n");
    fprintf(fp1,"touch averageflat \n");
    fprintf(fp1,"!./ExoFunction delrow temp.list averageflat\n"); 
    fprintf(fp1,"touch ABflat.list						# creates a blank list for Bflat files\n");
    //fprintf(fp1,"!./ExoAppend Append Bflat.list ABflat.list A\n");
    fprintf(fp1,"!awk '{d=$1; print\"A\"d}' Bflat.list > ABflat.list\n");
    fprintf(fp1,"print(\"NORMALIZING EACH FLAT...\")\n");
    fprintf(fp1,"imarith @Bflat.list / @averageflat @ABflat.list\n");
    fprintf(fp1,"print(\"NORMALIZATION COMPLETE\")\n");
    fprintf(fp1,"print(\"COMBINING ALL FLATS...\")\n");
    fprintf(fp1,"imcombine @ABflat.list superflat.fits\n");
    fprintf(fp1,"print(\"SUPER FLAT CREATED.\")\n");
    fprintf(fp1,"print(\"CHECKING THE MEAN...\")\n");
    fprintf(fp1,"imstat superflat.fits\n");
    fprintf(fp1,"print(\"IS IT 1?\")\n");
    fprintf(fp1,"#pull mean from file \n");
    fprintf(fp1,"imarith superflat.fits / 1 Nsuperflat.fits\n");
    fprintf(fp1,"cp Nsuperflat.fits ../\n");
    fprintf(fp1,"cd ../\n\n");
    fprintf(fp1,"###################### FLATFIELD YOUR IMAGES ####################\n");
    fprintf(fp1,"touch FB%s.list						# creates a blank list for Bflat files\n",Planet);
    fprintf(fp1,"!rm B%s.list	\n",Planet);
    fprintf(fp1,"ls B%s*.fits > B%s.list 	#update list just incase some images werent made\n",  Planet, Planet);	
    //fprintf(fp1,"!./ExoAppend Append B%s.list FB%s.list F \n", Planet.c_str(), Planet.c_str());
    fprintf(fp1,"!awk '{d=$1; print\"F\"d}' B%s.list > FB%s.list\n",Planet, Planet);
    fprintf(fp1,"print(\"FLATFIELDING YOUR IMAGES...\")\n");
    fprintf(fp1,"imarith @B%s.list / Nsuperflat.fits @FB%s.list\n",Planet, Planet);
    fprintf(fp1,"print(\"QUIRYING IMAGE STATS\")\n");
    fprintf(fp1,"imstat B%s*0080.fits\n",Planet);
    fprintf(fp1,"imstat FB%s*0080.fits\n\n",Planet);
    fprintf(fp1,"!mkdir ExoStuff\n");
    fprintf(fp1,"!mv B%s*.fits ExoStuff\n\n",Planet);
	// awk '{d=$1; print "a"d}' input > output
	fprintf(fp1,"###################### OTHER CALIBRATIONS #####################\n");
    fprintf(fp1,"task stcoox = ExoDRPL/Extras/stcoox.cl\n"); //FIXME
    fprintf(fp1,"astutil\n");
    fprintf(fp1,"proto\n");
    fprintf(fp1,"imred\n");
    fprintf(fp1,"ccdred\n");
    fprintf(fp1,"astutil\n");
    fprintf(fp1,"proto\n");
    //fprintf(fp1,"task stcoox = stcoox.cl\n");
    
    fprintf(fp1,"stcoox FB%s*.fits no \"%s\" \"%s\" 2000",Planet,RA,Dec); 
    fprintf(fp1,"\nsetairmass.images = \"FB%s*.fits\"\n",Planet);
    fprintf(fp1,"setairmass.observatory = \"mtbigelow\"\n");
    fprintf(fp1,"setjd.time = \"ut\"\n");
    fprintf(fp1,"print(\"just hit enter for the value...it will assign it later\")\n");
    fprintf(fp1,"hedit FB%s*.fits airmass add+\n",Planet);
    fprintf(fp1,"hedit FB%s*.fits jd add+\n",Planet);
    fprintf(fp1,"hedit FB%s*.fits filter add+ \n",Planet);
    // fprintf(fp1,"setfilter FB%s*.fits\n",Planet.c_str());
    fprintf(fp1,"setairmass FB%s*.fits\n",Planet);
    fprintf(fp1,"setjd FB%s*.fits\n",Planet);
    fprintf(fp1,"print(\"Airmass set\")\n");
    fprintf(fp1,"print(\"Julian Date Set\")\n\n");
    fprintf(fp1,"print(\"DATA REDUCTION FINISHED!\")\n\n");
    fprintf(fp1,"print(\"INITIATING PHOTOMETRY SEQUENCE\")\n");
    //fprintf(fp1,"print(\"opening your first image with ds9...wait for it...\")\n");
   // fprintf(fp1,"!ds9 FB%s*0001.fits &\n",Planet);
    fprintf(fp1,"hselect FB%s*.fits filename,ut yes > UT.txt", Planet);
    fprintf(fp1,"\n#parameters needed for photometry\n");
    fprintf(fp1,"datapars.ccdread = \"rdnoise1\"\n");
    fprintf(fp1,"datapars.gain = \"gain1\"\n");
    fprintf(fp1,"#need this to determine largest aperture by hand\n");
    fprintf(fp1,"#phot.interactive = yes\n");
    //fprintf(fp1,"cl < ExoPhotPt1.cl\n\n");   
	fprintf(fp1,"#Create the Reduced-HJD file\n");
    fprintf(fp1,"hselect FB%s*.fits hjd yes > hjd \n", Planet);
    fprintf(fp1,"# Create the Preliminary Aperture Photometry Script \n");
    //phot info files need FBlist to be made
      // move this to preaps
    fprintf(fp1,"imstat.fields = \"stddev\"\n");
    fprintf(fp1,"imstat.format = no\n");
    
    //Check if Files Exist - Gets image
	system("ls > FileList.txt");
	fp2 = fopen("FileList.txt", "r");
	while(!feof(fp2)){
		fgets(New,20,fp2);
		if (New[strlen(New)-1] == '\n' || New[strlen(New)-1] == '\r') New[strlen(New)-1] = '\0';
		// Check for Planet images
		if( strncmp(New,Planet,strlen(Planet)) == 0){
		 	//printf("lets break %s \n",New);
		 	break; 
		 	}
		 }// end while
	fclose(fp2);
	
    fprintf(fp1,"imstat FB%s[%s] > skysigma1.dat\n",New,sky1);
    if(strcmp(sky2, "x1:x2,y1:y2") != 0) fprintf(fp1,"imstat FB%s[%s] > skysigma2.dat\n",New,sky2);
    if(strcmp(sky3, "x1:x2,y1:y2") != 0) fprintf(fp1,"imstat FB%s[%s] > skysigma3.dat\n",New,sky2);    

    if(Identifier == 0)
    {
    	fprintf(fp1,"!./ExoFunction prephot \n");
    	fprintf(fp1,"!./ExoFunction preaps \n");
    	fprintf(fp1,"cl < ExoPreAPS.cl \n");
    	// set data pars script
    }
    else if(Identifier == 1)
    {
    	fprintf(fp1,"!./ExoFunction mainphot \n");
    	fprintf(fp1,"!./ExoFunction mainaps \n");
    	fprintf(fp1,"cl < ExoMainAPS.cl \n");
    }
    
    fprintf(fp1,"#Created via ExoDRPL "); 

    fclose(fp1);
	cout << newFileName << " was created.\n";
    // if(Advsettings[3] == 1)
	// Add Cosmic Ray options   	
    

}


// ***************************************************************
// ********* Creates the Photinfo files for ap photometry ********
// ***************************************************************
void Exo_Functions::CreatePhotInfo(int Identifier)
{
	// Read Settings to get planet, min+max aperture, ann, dann
	char Planet[20] = {'\0'}, RA[20] = {'\0'}, Dec[20] = {'\0'};
	float settings[8], Advsettings[8];
	ReadAdvSettings(Planet, RA, Dec, Advsettings); // only need the average fwhm info from adv settings
	ReadSettings(Planet, RA, Dec, settings);
	enum{min, max, precision, ann, dann, ingress, egress}Settings;
	
	int aperNum = 3;
	if(Identifier == 1) aperNum = (settings[max]-settings[min])/settings[precision];
	float aperList[aperNum];
	
	// Make the List of Apertures to use
	if(Identifier == 0) // Preliminary
	{
		float MidAperture = settings[min]+(settings[max] - settings[min])/2.; 
		aperList[0] = settings[min];
		aperList[1] = MidAperture;
		aperList[2] = settings[max];
	}
	else if(Identifier == 1)
	{
		aperList[0] = settings[min];
		for(int i=1;i<aperNum;i++) aperList[i]=aperList[i-1]+settings[precision];
	}
	else
	{
		printf("CreatePhot/ Identifier is not 0 or 1\n"); exit(1);
	}
	
	
	// Variables for creating phot info name
	string prefix = "photinfo_", suffix = ".txt", photfile;
	char tostring[4];
	
	// Create filename to open planet.list to obtain all the images
	string PlanetList = "FB";
	PlanetList = PlanetList.append(Planet);
	PlanetList = PlanetList.append(".list");
	
	// more variables needed for phot info file
	int numimages = FileSize(PlanetList), slen;
    string planetlist[numimages], coordfile = "xyfile";
    char fLine[100];    // used to read a line in
	FILE *fPList, *fPhot; // PlanetList file and Photinfo File
	
	/*
		Could add something to read in auto_plot.log for Mont4k data
	*/
	
	for(int i=0; i<aperNum; i++) // loop over 3 apertures
	{
		photfile = prefix;
		
		if(settings[precision] >= 0.1) sprintf(tostring, "%0.1f", aperList[i]); //converts aperture float to char*
		else sprintf(tostring, "%0.2f", aperList[i]);
		
		photfile = photfile.append(tostring); // add # to photinfo file name
		photfile = photfile.append(suffix);	// add suffix to photinfo file name
		
		// Opens PlanetList and Photinfo file
		fPList = fopen(PlanetList.c_str(), "r"); 
    	if(fPList == (FILE *) NULL) cerr << "EF/PrePhot: problem opening file \"" <<  PlanetList <<"\"\n";
    	fPhot = fopen(photfile.c_str(), "w+");
    	
    	//do loop to read in each image from FBexoplanet.list and print out a line in phot info file
    	do { 
            fgets(fLine, 100, fPList); // reads in planet list
            slen = strlen(fLine);
            //removes new line at end of c.string that was read in
            if (fLine[slen-1] == '\n' || fLine[slen-1] == '\r') fLine[slen-1] = '\0';
            // planet image, xyfile, average fwhm, annulus, dannulus, aperture
			if(!feof(fPList)) fprintf(fPhot, "%s %s %0.2f %0.0f %0.0f %0.2f \n", fLine, coordfile.c_str(),Advsettings[1],settings[ann],settings[dann],aperList[i]);
        } while(!feof(fPList));
        
        fclose(fPList); // close planet list
        fclose(fPhot);	// close photinfo_#
        cout << photfile << " was created \n";
	} // end for
}



// ***************************************************************
// *********** Creates the aperture photometry script ************
// ***************************************************************
void Exo_Functions::CreateApPhotScript(int Identifier)
{
	// Read Settings In
	enum{min, max, precision, ann, dann, ingress, egress}Settings;
	char Planet[20] = {'\0'}, RA[20] = {'\0'}, Dec[20] = {'\0'};
	float settings[8], sigma;
	
	ReadSettings(Planet, RA, Dec, settings);
	sigma = GetSkySigma();
	
	// Make the List of Apertures to use
	int aperNum = 3;
	if(Identifier == 1) aperNum = (settings[max]-settings[min])/settings[precision];
	float aperList[aperNum];
	if(Identifier == 0) // Preliminary
	{
		float MidAperture = settings[min]+(settings[max] - settings[min])/2.; 
		aperList[0] = settings[min];
		aperList[1] = MidAperture;
		aperList[2] = settings[max];
	}
	else if(Identifier == 1) // Main
	{
		aperList[0] = settings[min];
		for(int i=1;i<aperNum;i++) aperList[i]=aperList[i-1]+settings[precision];
	}
	else
	{
		printf("CreatePhot/ Identifier is not 0 or 1\n"); exit(1);
	}
	
	
	// Get the non-decimal portion of HJD
	int HJD = GetHJD();
	
	// Create Photometry script
	string FileName = "ExoPreAPS.cl"; 
	if(Identifier == 1) FileName = "ExoMainAPS.cl";
	
	FILE* fp1 = fopen(FileName.c_str(),"w+");
    if(fp1 == (FILE *) NULL) cerr << "EF/PreApPhot: problem opening file \"" << FileName <<"\"\n";
	int STARS = FileSize("xyfile");
	
	fprintf(fp1,"#Reset the parameters just in case \n");
	fprintf(fp1,"#This is the last part of the photometry it will go through all of the phot info files and create your allfluxes \n");
    fprintf(fp1,"#It will then analyze all of the allfluxes using the LCO routine\n\n");
    fprintf(fp1,"#Create the reduced HJD file, used for modeling\n"); 
    fprintf(fp1,"!awk \'{d=$1-%i ; print d}\' hjd > rhjd \n", HJD);
    fprintf(fp1,"datapars.sigma = %0.2f\n\n",sigma);
    
    // Do something to get datapars.sigma = #
    
    fprintf(fp1,"string img, coord, aper \n");
    fprintf(fp1,"real fwhm, ann, dann \n");
    fprintf(fp1,"struct *list \n");
    fprintf(fp1," \n");
	//FOR LOOP OVER APERTURES
    for (int i = 0; i < aperNum; i++)
    {
		fprintf(fp1,"print(\"Creating mag files\") \n");
	    
        if(settings[precision] >= 0.1) fprintf(fp1,"list = \"photinfo_%0.1f.txt\" \n",aperList[i]);
		else fprintf(fp1,"list = \"photinfo_%0.2f.txt\" \n",aperList[i]);
		
        
        fprintf(fp1,"while (fscan (list, img, coord, fwhm, ann, dann, aper) != EOF) { \n");
        fprintf(fp1,"phot (img, coord, fwhm=fwhm, ann=ann, dann=dann, aper=aper) \n");
        //change fwhm?
        fprintf(fp1,"} \n\n");
        fprintf(fp1,"!mkdir mag_%0.1f \n", aperList[i]);
        fprintf(fp1,"!cp FB%s*.mag.1 mag_%0.1f \n",Planet, aperList[i]);
        fprintf(fp1,"!rm FB%s*.mag.1 \n",Planet);
        fprintf(fp1,"!cp rhjd mag_%0.1f \n", aperList[i]);
        fprintf(fp1,"cd mag_%0.1f \n", aperList[i]);
        fprintf(fp1," \n");
        
        //FOR LOOP OVER STARS
	for (int j=0;j<STARS;j++) fprintf(fp1,"txdump FB%s*.mag.1 flux,epadu,stdev,nsky,area '(id == %d)' > star%dparamhead \n", Planet, j+1, j+1);
        fprintf(fp1," \n");
        
	for (int j=0;j<STARS;j++) fprintf(fp1,"fields star%iparamhead field=1,2,3,4,5 > star%iparam \n",j+1, j+1);
        fprintf(fp1," \n");
        
	for (int j=0;j<STARS;j++) fprintf(fp1,"txdump FB%s*.mag.1 xcenter,ycenter,xairmass '(id == %d)' > star%dextrahead \n", Planet, j+1, j+1);
        fprintf(fp1," \n");
        
	for (int j = 0; j < STARS; j++) fprintf(fp1,"fields star%iextrahead field=1,2,3 > star%iExtraParams \n",j+1, j+1);
        fprintf(fp1," \n");
        
	for (int j = 0; j < STARS; j++)
	{   
           // fprintf(fp1,"!awk '{ d = 10^($1/-2.5); print d}' star%imag > star%iflux \n\n", j+1, j+1);
		fprintf(fp1,"!awk '{ print $1 }' star%dparam > star%dflux \n", j+1, j+1);
		fprintf(fp1,"!awk '{ error = sqrt(($1/$2)+($5*($3*$3))+($5*$5*$3*$3)/$4) ; print error}' star%dparam > star%dfluxerr \n", j+1, j+1);
           // fprintf(fp1,"!awk '{ merr = -1.0857*$1/$2 ; print merr}' step%dmagerr > star%dmagerr \n\n", j+1, j+1);
	}

        fprintf(fp1," \n");

		fprintf(fp1,"join ");
		    for (int j = 0; j < STARS+1; j++)
		    {
				if(j+1 <= STARS)
				{
					fprintf(fp1,"star%iflux",j+1);
					fprintf(fp1,",");
				}
			}
		fprintf(fp1," > allflux%0.1f \n\n", aperList[i]);	

		fprintf(fp1,"join ");
		for (int j = 0; j < STARS+1; j++)
			{
			if(j+1 <= STARS)
				{
					fprintf(fp1,"star%ifluxerr",j+1);
					fprintf(fp1,",");
				}
			}
		fprintf(fp1," > allfluxerr%0.1f \n", aperList[i]);		

		fprintf(fp1," \n");
		fprintf(fp1,"!cp allflux%0.1f ../ \n", aperList[i]);
		fprintf(fp1,"!cp allfluxerr%0.1f ../ \n",aperList[i]);
		fprintf(fp1,"cd ../ \n\n");
		if(i < aperNum-1) fprintf(fp1,"print(\"processing next aperture %0.1f \") \n\n",aperList[i+1]); //APERATURES
    } // End loop over apertures
    
    // Creates a new ExoPreResults.txt file
    string ResultsFile = "ExoPreResults.txt";
	FILE *fp = fopen(ResultsFile.c_str(), "w+"); 
	fclose(fp);
    
    // FOR LOOP ALL APERTURES RUN THRU LCO
    for (int i = 0; i < aperNum; i++)
    {
        if(settings[precision] >= 0.1) fprintf(fp1,"!./ExoFunction LCO allflux%0.1f \n", aperList[i]);
		else fprintf(fp1,"!./ExoFunction LCO allflux%0.2f \n", aperList[i]);
    }   
    
    fprintf(fp1,"!./ExoFunction analyze \n"); // Analyze to find best results
    fprintf(fp1,"!./ExoFunction afteranalyze \n"); // Create script to organizing stuff after analyzing
    fprintf(fp1,"cl < AfterAnalyze.cl\n"); // Organizes files
    fprintf(fp1,"cl < PlotLC2.cl\n");
    
    fprintf(fp1," \n");
    fprintf(fp1,"#Created by ExoDRPL \n");
    
    fclose(fp1);
    cout << FileName << " was created.\n"; 
}
