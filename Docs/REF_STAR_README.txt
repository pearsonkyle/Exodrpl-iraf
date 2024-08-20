README for Creating a file to host coordinates of stars and sky section

1. Set your task parameters for imexam
	type (in IRAF): 
			imexam.ncstat = 100
			imexam.nlstat = 100


2. Open an image (not a flat or bias image) in ds9
ex. !ds9 exoplanet16b.0001.fits &
*note* you only need the '!' if you are trying to perform a native terminal command in IRAF


3. Type: imexam > xyfile
Press comma(,) on each star to display information on each star. This information will appear in the file 'xyfile'. Try to get at least 5 reference stars the same or brighter than your exoplanet. Make sure the star your exoplanet is orbiting around is first. Also try to get them as evenly spaced around the exoplanet as possible. Avoid using reference stars that have a close companion, close to the edge of the image or close to bad pixels/columns. It may be helpful to reference http://aladin.u-strasbg.fr/ to eliminate choosing any variable reference stars. 

 
4. Format the xyfile, type: !gedit xyfile &
	You want this file to contain ONLY the x and y coordinates for each star so delete all the excess columns and rows. It should look something like this
 602.04  671.39 (<-- host star)
 351.80 1002.94
 177.70 1197.63
1120.91 1265.30
 931.82 1297.10
1038.45  410.51
 994.69  345.20
 422.25   65.67
*Notice* there are no excess lines at the end or beginning of the file. (Do not include this line in your xyfile or the text after host star coordinates)


5. Update the datapars package
You will need to find a ~100x100 pixel area that does not have any stars in it. ExoDRPL will later obtain the stddev of the region and use it when calculating the error bars. 
	a. Do this by opening an image in ds9 (!ds9 exoplanet16b.0001.fits &)
	b. type (in IRAF): imexam
	c. Press 'm' to find a region that has a low stddev
	d. Once you found a region type: ./ExoFunction skysection x1:x2,y1:y2
		where x1,x2,y1,y2 is the region that was spit out by imexam
	e. You may set up to 3 sky sections for the script to reference
		To explicitly edit them type ./ExoFunction skysection# x1:x2,y1:y2
		Where # can be 1,2 or 3. Or go to AdvSettings 
	f. It may be useful to Press 'r' on your reference stars to show a radial plot of the fall off of light so you can determine the optimal annulus, dannulus and apertures. 
	

DEBUGGING
	If you can not get imexam to work within your ds9 window, close IRAF and your xgterm you're working in and restart it and try again. 
	Remember when you are in an IRAF window you must use an exclamation mark(!) before each command if it is not a native IRAF command, so basically anything you can type normally in the terminal except ls, pwd and cd.
