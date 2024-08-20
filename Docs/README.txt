 Exoplanet Data Reduction Pipeline v2.0
 
GNU General Public License v3

 * Copyright 2013 Kyle Pearson <pearsonk@email.arizona.edu>
 *
 * These programs (ExoDRPL.cc, display.cc, display.h, UI.cc, UI.h, ExoFunctions.h, ExoFunctions.cc, ExoAnalysis.cc, ExoExtras.cc, ExoMainScripts.cc ) are free 
 *  software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>

 
INTENT:
    This program creates a series of IRAF scripts for an arbitrary planet that will calibrate your images then perform aperture photometry. This automated pipeline is designed to run in two stages, preliminary and main. The preliminary run is designed to do a quick reduction and analysis of your images in order for you to find out how many ingress and egress data points you have so you can get optimal results in the analysis and main run. This pipeline runs through a user specified amount of apertures and tests every combination of reference stars at each aperture to find the combination that yields the minimum scatter (STDEV) in the out of transit baseline. 
 
 
HOW TO INSTALL:
	Untar the package in your data directory like such:
         tar -xvzf Exo_DRPL.tar.gz


AUTO-COMPILE + RUN:
	Type in terminal: ./compile+run

	         
REQUIREMENTS:
	Extended FITS images of the format:
		'exoplanet'.####.fits
		'exoplanet'####.fits
		bias.####.fits
		bias.U.####.fits
		flat.####.fits
		flat.U.####.fits
	'exoplanet' is arbitrary and if you have images of other types 
	re-name them like such or else you may get the wrong images 
	reduced because the iraf script targets all of the images like 
	such, 'exoplanet'*.fits , * stands for anything with that prefix.
	The U just refers to the filter being used. 

	IRAF
	     For installation info open SourceInfo.txt
		
	xgterm
	     For installation info open SourceInfo.txt

	DS9
	     For installation info open SourceInfo.txt


DATA REDUCTION:
	This program uses the reduction methods in http://adsabs.harvard.edu/abs/2013MNRAS.428..678T and http://adsabs.harvard.edu/abs/2013MNRAS.431.1669T. For exact instructions please visit https://sites.google.com/a/email.arizona.edu/ua-extrasolar-planet-project/data-reduction


HOW TO USE:
	1. Open and follow the instructions in ExoDRPL/README/REF_STAR_README.txt
	2. Compile + Run the program: ./compile+run
	3. Run through the Preliminary Reduction Run
	4. Update Ingress + Egress Values
	5. Rerun through Main Reduction Run


For a visual guide on how to run and use ExoDRPL visit: 
 	https://sites.google.com/a/email.arizona.edu/kyle-pearson/exodrpl


