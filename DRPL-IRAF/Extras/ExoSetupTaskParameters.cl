# to execute: cl < setTaskParameters.cl
# if you want to find out what each parameter does 
#  specifically type: lpar 'taskname'

imexam.input = ""
imexam.frame = 1
imexam.image = " "
imexam.output = ""
imexam.ncoutput = 101
imexam.nloutput = 101
imexam.logfile = ""
imexam.keeplog = no
imexam.defkey = "a"
imexam.autoredraw = yes
imexam.allframes = no
imexam.nframes = 1
imexam.ncstat = 100
imexam.nlstat = 100
imexam.graphcur = ""
imexam.imagecur = ""
imexam.wcs = "logical"
imexam.xformat = ""
imexam.yformat = ""
imexam.graphics = "stdgraph"
imexam.display = "display(image='$1',frame=$2)"
imexam.use_display = yes
imexam.mode = "ql"

rimexam.banner = yes
rimexam.title = ""
rimexam.xlabel = "Radius"
rimexam.ylabel = "Pixel Value"
rimexam.fitplot = yes
rimexam.fittype = "moffat"
rimexam.center = yes
rimexam.background = yes
rimexam.background = yes
rimexam.radius = 10.
rimexam.buffer = 4.
rimexam.width = 7.
rimexam.iterations = 5
rimexam.xorder = 0
rimexam.yorder = 0
rimexam.magzero = 25.
rimexam.beta = INDEF
rimexam.rplot = 17.
rimexam.x1 = INDEF
rimexam.x2 = INDEF
rimexam.y1 = INDEF
rimexam.y2 = INDEF
rimexam.pointmode = yes
rimexam.marker = "plus"
rimexam.szmarker = 1.
rimexam.logx = no
rimexam.logy = no
rimexam.box = yes
rimexam.ticklabels = yes
rimexam.majrx = 5
rimexam.minrx = 5
rimexam.majry = 5
rimexam.minry = 5
rimexam.round = no
rimexam.mode = "ql"

imstat.images = ""
imstat.fields = "image,npix,mean,stddev,min,max"
imstat.lower = INDEF
imstat.upper = INDEF
imstat.nclip = 0
imstat.lsigma = 3.
imstat.usigma = 3.
imstat.binwidth = 0.1
imstat.format = yes
imstat.cache = no
imstat.mode = "ql"

imcombine.input = ""
imcombine.output = ""
imcombine.headers = ""
imcombine.bpmasks = ""
imcombine.rejmasks = ""
imcombine.nrejmasks = ""
imcombine.expmasks = ""
imcombine.sigmas = ""
imcombine.imcmb = "$I"
imcombine.logfile = "STDOUT"
imcombine.combine = "median"
imcombine.reject = "avsigclip"
imcombine.project = no
imcombine.outtype = "real"
imcombine.outlimits = ""
imcombine.offsets = "none"
imcombine.masktype = "none"
imcombine.maskvalue = 0.
imcombine.blank = 0.
imcombine.scale = "none"
imcombine.zero = "none"
imcombine.weight = "none"
imcombine.statsec = "[100:1265,100:1265]"
imcombine.expname = "exptime"
imcombine.lthreshold = INDEF
imcombine.hthreshold = INDEF
imcombine.nlow = 1
imcombine.nhigh = 1
imcombine.nkeep = 1
imcombine.mclip = yes
imcombine.lsigma = 3.
imcombine.hsigma = 3.

# FIXME 
imcombine.rdnoise = "5.7"
imcombine.gain = "3.1"
imcombine.snoise = "0."
imcombine.sigscale = 0.1
imcombine.pclip = 0.5
imcombine.grow = 0.
imcombine.mode = "ql"

hselect.images = ""
hselect.fields = "hjd"
hselect.expr = "yes"
hselect.missing = INDEF
hselect.mode = "ql"

hedit.images = ""
hedit.fields = ""
hedit.value = "1"
hedit.add = no
hedit.addonly = no
hedit.delete = no
hedit.verify = no
hedit.show = no
hedit.update = yes
hedit.mode = "ql"

ccdhedit.images = ""
ccdhedit.parameter = "filter"
ccdhedit.value = "Schott-8612"
ccdhedit.type = "string"
ccdhedit.mode = "ql"

display.image = ""
display.frame = 1
display.bpmask = "BPM"
display.bpdisplay = "none"
display.bpcolors = "red"
display.overlay = ""
display.ocolors = "green"
display.erase = yes
display.border_erase = no
display.select_frame = yes
display.repeat = no
display.fill = no
display.zscale = yes
display.contrast = 0.25
display.zrange = yes
display.zmask = ""
display.nsample = 1000
display.xcenter = 0.5
display.ycenter = 0.5
display.xsize = 1.
display.ysize = 1.
display.xmag = 0.75
display.ymag = 0.75
display.order = 0
display.z1 = 128.
display.z2 = 4000.
display.ztrans = "linear"
display.lutfile = ""
display.mode = "ql"

setairmass.images = ""
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
setairmass.scale = 750.
setairmass.show = yes
setairmass.update = yes
setairmass.override = yes
setairmass.mode = "ql"

setjd.images = ""
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
setjd.utdate = yes
setjd.uttime = yes
setjd.listonly = no
setjd.mode = "ql"

fixpix.images = ""
fixpix.mask = "badpix.3x3.pl"
fixpix.linterp = "1"
fixpix.cinterp = "2"
fixpix.verbose = no
fixpix.pixels = no
fixpix.mode = "ql"

cosmicrays.input = ""
cosmicrays.output = ""
cosmicrays.answer = "no"
cosmicrays.crmasks = "crmask"
cosmicrays.threshold = 20.
cosmicrays.fluxratio = 5.
cosmicrays.npasses = 500
cosmicrays.window = "7"
cosmicrays.interactive = no
cosmicrays.train = no
cosmicrays.objects = ""
cosmicrays.savefile = ""
cosmicrays.plotfile = ""
cosmicrays.graphics = "stdgraph"
cosmicrays.cursor = ""
cosmicrays.mode = "ql"

datapars.scale = 1.
datapars.fwhmpsf = 4.
datapars.emission = yes
datapars.sigma = 8.4
datapars.datamin = -60.
datapars.datamax = 150000.
datapars.noise = "constant"
datapars.ccdread = "rdnoise"
datapars.gain = "gain"
datapars.readnoise = INDEF
datapars.epadu = INDEF
datapars.exposure = "exptime"
datapars.airmass = "airmass"
datapars.filter = "filter"
datapars.obstime = "hjd"
datapars.itime = INDEF
datapars.xairmass = INDEF
datapars.ifilter = INDEF
datapars.otime = INDEF
datapars.mode = "ql"

#centerpars@.calgorithm = "centroid"
#centerpars@.cbox = 15.0
#centerpars@.cthreshold = 0.
#centerpars@.minsnratio = 1.
#centerpars@.cmaxiter = 10
#centerpars@.maxshift = 0.05
#centerpars@.clean = no
#centerpars@.rclean = 1.
#centerpars@.rclip - 2.
#centerpars@.kcliean = 3.
#centerpars@.mkcenter = no
#centerpars@.mode = "ql"

fitskypars.salgorithm = "median"
fitskypars.annulus = 20.
fitskypars.dannulus = 10.
fitskypars.skyvalue = 0.
fitskypars.smaxiter = 10
fitskypars.sloclip = 0.
fitskypars.shiclip = 0.
fitskypars.snreject = 50
fitskypars.sloreject = 3.
fitskypars.shireject = 3.
fitskypars.khist = 3.
fitskypars.binsize = 0.1
fitskypars.smooth = no
fitskypars.rgrow = 0.
fitskypars.mksky = no
fitskypars.mode = "ql"

photpars.weighting = "constant"
photpars.apertures = "16"
photpars.zmag = 23.2
photpars.mkapert = no
photpars.mode = "ql"

phot.image = ""
phot.skyfile = "xyfile"
phot.coords = "xyfile"
phot.output = "default"
phot.plotfile = ""
phot.datapars = ""
phot.centerpars = ""
phot.fitskypars = ""
phot.photpars = ""
phot.interactive = no
phot.radplots = no
phot.icommands = ""
phot.gcommands = ""
phot.wcsin = ")_.wcsin"
phot.wcsout = ")_.wcsout"
phot.cache = ")_.cache"
phot.verify = no
phot.update = no
phot.verbose = no
phot.graphics = "stdgraph"
phot.display = "stdimage"
phot.mode = "ql"

txdump.textfiles = ""
txdump.fields = "image,xc,yc,ifilter,xairmass,otime,mag,merr"
txdump.expr = "(id==1)"
txdump.headers = yes
txdump.parameters = yes
txdump.mode = "ql"
