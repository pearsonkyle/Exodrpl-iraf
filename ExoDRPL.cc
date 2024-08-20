/*
 Exoplanet Data Reduction Pipeline v2.1
  
 GNU General Public License v3
 
  INTENT:
    This program creates some scripts for an arbitrary planet that can then
    be executed and will perform all of the data reduction steps necessary 
    (standard image calibrations; bias, flatfield + any advanced settings enabled)
    and perform aperture photometry given a coordinate file for your stars
    afterwards your data will be ready to be modeled.
 
 REQUIREMENTS:
    the following software is not distributed with ExoDRPL
    * GCC/G++ Compiler
    * xgterm
    * DS9
    * IRAF
 
 COMPILE:
 	g++ ExoDRPL.cc
 	
 RUN:
 	./a.out
 	
 README:
 	Contained in ExoDRPL/README/
 		
*/

#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <list>
#include <omp.h>

using namespace std;

#include "Extras/Allocarray.cc" 	// Memory allocation
#include "Functions/ExoFunctions.h" // Creates Scripts
#include "Interface/display.h" 		// Display for interface
#include "Interface/UI.h" 			// Interface Input Options

#define VERSION 2.1

int main(int argc,char **argv)
{	
	// Create struct that holds the functions
	Exo_Functions Function;
	
	// Create a graphical display
	Graphics_Display Display;
	Display.Version = VERSION;
	
	// Create User Input interface with the display + functions just made
	User_Interface UI(Display, Function);
	
	
	// No Graphics. Options to access the rest of the program functions
	// char* for comparisons for runtime arguments
	char LCO[] = "LCO";
	char HELP[] = "help";
	char DELROW[] = "delrow";
	char CLEANUP[] = "cleanup";
	char PREAPS[] = "preaps", PREPHOT[] = "prephot";
	char MAINAPS[] = "mainaps", MAINPHOT[] = "mainphot";
	char PREANALYZE[] = "analyze", AFTERAN[] = "afteranalyze";
	char CHECKUPDATE[] = "checkupdate", GETUPDATE[] = "update";
    char SKYSECTION[] = "skysection", SKY1[] = "skysection1", SKY2[] = "skysection2", SKY3[] = "skysection3";
	string inFile, outFile, add;
	char cadd[25];
	if(argc == 1)
	{
		// Display StartMenu + Prompt for input
		UI.StartMenu();
	}
	else if(argc == 2)
	{
        if(strcmp(argv[1], HELP) == 0) // ./ExoFunction help
        {
        	cout << "The available cmd line arguments are: \n";
        	cout << "   delrow - Delete the first line of a file and copy it to a new file\n";
        	cout << "   skysection - Sets the skysection setting to obtain sky STDDEV later\n";
            cout << "   skysection# - # can be 1, 2 or 3 and does the same as above \n";
        	cout << "   cleanup - Creates ExoCleanUp.cl. Clean up excess file script \n";
        	cout << "   preaps - Creates Preliminary Aperture Photometry script\n";
        	cout << "   prephot - Creates Preliminary Photinfo files for photometry \n";
        	cout << "   mainaps - Creates Main Aperture Photometry script \n";
        	cout << "   mainphot - Creates Main Photinfo files for photometry \n";
        	cout << "   analyze - Analyzes data after photometry to extract best Ref Star + Aperture\n";
        	cout << "   afteranalyze - Creates a script to organize files after analyzing data \n";
        	cout << "   LCO - Light Curve Optimization, analyzes lightcurve data \n";
        	cout << "   checkupdate - Checks Web for current version of program \n";
        	cout << "   update - Downloads current version of program from website \n";
        }
        else if(strcmp(argv[1], DELROW) == 0) //ExoFunction delrow
        {
            cout << "Delete the first row routine\n";
            cout << "Enter input file name:";
            cin >> inFile;
            cout << "Enter output file name:";
            cin >> outFile;
            Function.DelRow(inFile,outFile);
        }
        else if(strcmp(argv[1], PREAPS) == 0) //ExoFunction preaps
        {
        	Function.CreateApPhotScript(0);
        }
        else if(strcmp(argv[1], PREPHOT) == 0) //ExoFunction prephot
        {
        	Function.CreatePhotInfo(0);
        }
        else if(strcmp(argv[1], MAINAPS) == 0) //ExoFunction mainaps
        {
        	Function.CreateApPhotScript(1);
        }
        else if(strcmp(argv[1], MAINPHOT) == 0) //ExoFunction mainphot
        {
        	Function.CreatePhotInfo(1);
        }
        else if(strcmp(argv[1], LCO) == 0) //ExoFunction LCO
        {
        	cout << "Enter a file to be analyzed:";
        	cin >> inFile;
        	Function.LightCurveOp(inFile);
        }
        else if(strcmp(argv[1], PREANALYZE) == 0) //ExoFunction analyze
        {
        	Function.AnalyzeResults();
        }
        else if(strcmp(argv[1], AFTERAN) == 0) //ExoFunction afteranaylze
        {
        	Function.AfterAnalyze();
        }
        else if(strcmp(argv[1], SKYSECTION) == 0) //ExoFunction skysection
        {
        	cout << "Enter a sky section (x1:x2,y1:y2) = ";
        	cin >> cadd;
            while(Function.CheckSky(cadd) == 0)
            {
                cout << "bad format...\n";
                cout << "Enter a sky section (x1:x2,y1:y2) = ";
        	    cin >> cadd;
            }       
        	Function.SetSkySection(cadd); 
        }
        else if(strcmp(argv[1], SKY1) == 0) //ExoFunction skysection1
        {
        	cout << "Enter a sky section#1 (x1:x2,y1:y2) = ";
        	cin >> cadd;
            while(Function.CheckSky(cadd) == 0)
            {
                cout << "bad format...\n";
                cout << "Enter a sky section (x1:x2,y1:y2) = ";
        	    cin >> cadd;
            }       
        	Function.SetSkySection(cadd,1); 
        }
        else if(strcmp(argv[1], SKY2) == 0) //ExoFunction skysection2
        {
        	cout << "Enter a sky section#2 (x1:x2,y1:y2) = ";
        	cin >> cadd;
            while(Function.CheckSky(cadd) == 0)
            {
                cout << "bad format...\n";
                cout << "Enter a sky section (x1:x2,y1:y2) = ";
        	    cin >> cadd;
            }       
        	Function.SetSkySection(cadd,3); 
        }
        else if(strcmp(argv[1], SKY3) == 0) //ExoFunction skysection3
        {
        	cout << "Enter a sky section#3 (x1:x2,y1:y2) = ";
        	cin >> cadd;
            while(Function.CheckSky(cadd) == 0)
            {
                cout << "bad format...\n";
                cout << "Enter a sky section (x1:x2,y1:y2) = ";
        	    cin >> cadd;
            }       
        	Function.SetSkySection(cadd,3); 
        }
        else if(strcmp(argv[1], CLEANUP) == 0) //ExoFunction cleanup
        {
        	Function.CreateCleanUp();
        }
        else if(strcmp(argv[1], CHECKUPDATE) == 0) //ExoFunction checkupdate
        {
        	cout << "Quirying Internet...\n";
        	Display.CheckUpdate();
        }
        else if(strcmp(argv[1], GETUPDATE) == 0) //ExoFunction update
        {
        	cout << "Downloading Update...\n";
        	Display.GetUpdate();
        }
        else
        {
    		cout << "Need some help? Try ./ExoFunction help \n";
        }
	}
	else if(argc == 3)
	{
		if(strcmp(argv[1], LCO) == 0 ) //ExoFunction LCO infile
		{
			Function.LightCurveOp(argv[2]);
		}
		if(strcmp(argv[1], SKYSECTION) == 0) //ExoFunction skysection x1:x2,y1:y2
		{
			if (Function.CheckSky(argv[2]) == 1) Function.SetSkySection(argv[2]);
            else cout << "bad section format, try again with this format: x1:x2,y1:y2\n";
		}
        if(strcmp(argv[1], SKY1) == 0) //ExoFunction skysection1 x1:x2,y1:y2
		{
			if (Function.CheckSky(argv[2]) == 1) Function.SetSkySection(argv[2],1);
            else cout << "bad section format, try again with this format: x1:x2,y1:y2\n";
		}
        if(strcmp(argv[1], SKY2) == 0) //ExoFunction skysection2 x1:x2,y1:y2
		{
			if (Function.CheckSky(argv[2]) == 1) Function.SetSkySection(argv[2],2);
            else cout << "bad section format, try again with this format: x1:x2,y1:y2\n";
		}
        if(strcmp(argv[1], SKY3) == 0) //ExoFunction skysection3 x1:x2,y1:y2
		{
			if (Function.CheckSky(argv[2]) == 1) Function.SetSkySection(argv[2],3);
            else cout << "bad section format, try again with this format: x1:x2,y1:y2\n";
		}
	}
	else if(argc == 4)
    {
        if (strcmp(argv[1], DELROW) == 0) //ExoFunction delrow In Out
        {
            Function.DelRow(argv[2],argv[3]);
        }
   }
	
} // end main

