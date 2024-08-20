# Specific Parameters for the mont4k CCD on Kuiper 1.5m telescope

imcombine.rdnoise = "5.7"
imcombine.gain = "3.1"
imcombine.snoise = "0."

ccdhedit.parameter = "filter"
ccdhedit.value = "Schott-8612"


setairmass.observatory = ")_.observatory"
setairmass.intype = "beginning"
setairmass.outtype = "effective"
setairmass.ra = "ra"
setairmass.dec = "dec"
setairmass.equinox = "epoch"
setairmass.st = "st"
setairmass.ut = "ut"
setairmass.date = "date-obs"
setairmass.exposure = "exptime"
setairmass.airmass = "airmass"
setairmass.utmiddle = "utmiddle"

setjd.observatory = ")_.observatory"
setjd.date = "date-obs"
setjd.time = "utmiddle"
setjd.exposure = ""
setjd.ra = "ra"
setjd.dec = "dec"
setjd.epoch = "epoch"
setjd.jd = "jd"
setjd.hjd = "hjd"
setjd.ljd = "ljd"

datapars.noise = "constant"
datapars.ccdread = "rdnoise"
datapars.gain = "gain"
datapars.readnoise = INDEF
datapars.epadu = INDEF
datapars.exposure = "exptime"
datapars.airmass = "airmass"
datapars.filter = "filter"
datapars.obstime = "hjd"


