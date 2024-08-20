# Exoplanet Data Reduction Pipeline v2.0

This program creates a series of IRAF scripts for an arbitrary planet that will calibrate your images then perform aperture photometry. This automated pipeline is designed to run in two stages, preliminary and main. The preliminary run is designed to do a quick reduction and analysis of your images in order for you to find out how many ingress and egress data points you have so you can get optimal results in the analysis and main run. This pipeline runs through a user specified amount of apertures and tests every combination of reference stars at each aperture to find the combination that yields the minimum scatter (STDEV) in the out of transit baseline.

## How to Install

Untar the package in your data directory like such:
```bash
tar -xvzf Exo_DRPL.tar.gz
```

## Auto-Compile and Run

Type in terminal:
```bash
./compile+run
```

## Requirements

* Extended FITS images of the format:
	+ `exoplanet`.####.fits
	+ `exoplanet`####.fits
	+ bias.####.fits
	+ bias.U.####.fits
	+ flat.####.fits
	+ flat.U.####.fits
* IRAF
* xgterm
* DS9

For installation information, please open `SourceInfo.txt`.

## Data Reduction

This program uses the reduction methods in [Tamineh et al. (2013)](http://adsabs.harvard.edu/abs/2013MNRAS.428..678T) and [Tamineh et al. (2013)](http://adsabs.harvard.edu/abs/2013MNRAS.431.1669T). For exact instructions, please visit <https://sites.google.com/a/email.arizona.edu/ua-extrasolar-planet-project/data-reduction>.

## How to Use

1. Open and follow the instructions in `ExoDRPL/README/REF_STAR_README.txt`.
2. Compile and run the program:
```bash
./compile+run
```
3. Run through the Preliminary Reduction Run.
4. Update Ingress + Egress Values.
5. Rerun through Main Reduction Run.

## Youtube tutorial

https://www.youtube.com/watch?v=IenOiCSt90Q

If you're looking for an updated version of this pipeline, please visit the python package [EXOTIC](github.com/rzellem/EXOTIC).