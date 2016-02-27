SCRIPTS=doreport doreport.pm
TGTDIR=/home/tof/bin/anal
distribution :
	@[ -d $(TGTDIR) ] || mkdir $(TGTDIR) || \
	  echo Could not create $(TGTDIR)
	@distribute $(TGTDIR) $(SCRIPTS)
