# Makefile Generated Sun Feb 21 18:01:35 PST 2016
MNC=GPStest
SPECFILE=GPStest.spec
PCMFILE=GPStest.pcm
SRC=GPStest.tmc GPStest.tbl GPStesteng.cdf GPStest.doit
TOOL=GPStest.spec Makefile
SCRIPT=interact
OBJ=GPStest.tbl GPStesttbl.tmc GPStestdisp.cc GPStestdispoui.c
OBJ+=GPStestdispoui.o GPStestdisp.o GPStesttblnc.tmc GPStestdispnc.cc
OBJ+=GPStestdispncoui.c GPStestdispncoui.o GPStestdispnc.o
OBJ+=GPStestextcdf.oui GPStestengext.tmc GPStestext.cc
OBJ+=GPStestextoui.c GPStestextoui.o GPStestext.o doit.dep
OBJ+=GPStestcmd.cc GPStestcmd.dat GPStestclt.o GPStestcltoui.c
OBJ+=GPStestcltoui.o GPStestcltnc.o GPStestcltncoui.c
OBJ+=GPStestcltncoui.o GPStestsrvr.o GPStestsrvroui.c
OBJ+=GPStestsrvroui.o GPStestcol.cc GPStest.pcm tm.dac
OBJ+=GPStestcoloui.c GPStestcoloui.o GPStestcol.o
TGT=GPStestdisp GPStestdispnc GPStestext doit GPStestclt
TGT+=GPStestcltnc GPStestsrvr GPStestcol
DISTRIB=../gpsd_client GPStest.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit
SRCDIST=GPStest.tbl GPStest.tmc ../TM/gpsd.tmc
SRCDIST+=/usr/local/share/huarp/cpu_usage.tmc
SRCDIST+=/usr/local/share/huarp/flttime.tmc
TMCBASE=GPStest.tmc ../TM/gpsd.tmc
TMCBASE+=/usr/local/share/huarp/cpu_usage.tmc
TMCBASE+=/usr/local/share/huarp/flttime.tmc
CMDBASE=/usr/local/share/huarp/root.cmd
CMDBASE+=/usr/local/share/huarp/getcon.cmd
COLBASE=/usr/local/share/huarp/cpu_usage_col.tmc ../TM/gpsd_col.tmc
SWSBASE=
QCLIBASE=
PHTGT=GPStesttbl.tmc
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/GPStest
include /usr/local/share/huarp/appgen.mk

.PHONY : all extdistribution distribution clean check_photon

all : Makefile check_photon $(TGT) .cvsignore
Makefile : GPStest.spec
	appgen GPStest.spec
VERSION=`cat VERSION`
extdistribution : $(DSTRB) $(SRCDIST) VERSION
	@[ -d $(TGTDIR)/bin ] || mkdir $(TGTDIR)/bin
	@[ -d $(TGTDIR)/bin/$(VERSION) ] || mkdir $(TGTDIR)/bin/$(VERSION)
	@[ -d $(TGTDIR)/bin/$(VERSION)/Base ] || mkdir $(TGTDIR)/bin/$(VERSION)/Base
	@[ ! -f $(TGTDIR)/bin/$(VERSION)/$(PCMFILE) ] || \
	  cmp -s $(TGTDIR)/bin/$(VERSION)/$(PCMFILE) $(PCMFILE) || \
	  ( echo "$(PCMFILE) changed without VERSION update"; false )
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION) $(DSTRB)
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION)/Base $(SRCDIST)
distribution : extdistribution
	@distribute $(FORCE) $(TGTDIR) $(IDISTRIB)
check_photon :
ifeq ($(WPHOTON),YES)
	@for tgt in $(PHTGT); do \
	  cmp -s $$tgt /usr/local/share/huarp/nulltbl.tmc && echo Remaking $$tgt && rm -f $$tgt; \
	done; true
endif
GPStestdisp : GPStestdisp.o GPStestdispoui.o
	$(LINK.normCXX) GPStestdisp.o GPStestdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) GPStestdispoui.c
GPStestdispnc : GPStestdispnc.o GPStestdispncoui.o
	$(LINK.normCXX) GPStestdispnc.o GPStestdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) GPStestdispncoui.c
GPStestext : GPStestext.o GPStestextoui.o
	$(LINK.normCXX) GPStestext.o GPStestextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) GPStestextoui.c
doit : GPStest.doit
	mkdoit3 -o doit  GPStest.doit
GPStestclt : GPStestclt.o GPStestcltoui.o
	$(LINK.normCXX) GPStestclt.o GPStestcltoui.o -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) GPStestcltoui.c
GPStestcltnc : GPStestcltnc.o GPStestcltncoui.o
	$(LINK.normCXX) GPStestcltnc.o GPStestcltncoui.o -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) GPStestcltncoui.c
GPStestsrvr : GPStestsrvr.o GPStestsrvroui.o
	$(LINK.privCXX) GPStestsrvr.o GPStestsrvroui.o -ltmpp -ltm -lnort
	$(OUIUSE) GPStestsrvroui.c
	$(PROMOTE) GPStestsrvr
GPStestcol : GPStestcol.o GPStestcoloui.o
	$(LINK.privCXX) GPStestcol.o GPStestcoloui.o -ltmpp -ltm -lnort
	$(OUIUSE) GPStestcoloui.c
	$(PROMOTE) GPStestcol
GPStesttbl.tmc : GPStest.tbl
GPStestdisp.cc : GPStest.tmc ../TM/gpsd.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/flttime.tmc ../TM/gpsd_conv.tmc GPStesttbl.tmc
	$(TMC) GPStest.tmc ../TM/gpsd.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/flttime.tmc ../TM/gpsd_conv.tmc GPStesttbl.tmc
GPStestdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
GPStestdispoui.o : GPStestdispoui.c
GPStestdisp.o : GPStestdisp.cc
GPStesttblnc.tmc : GPStest.tbl
GPStestdispnc.cc : GPStest.tmc ../TM/gpsd.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/flttime.tmc ../TM/gpsd_conv.tmc GPStesttblnc.tmc
	$(TMC) GPStest.tmc ../TM/gpsd.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/flttime.tmc ../TM/gpsd_conv.tmc GPStesttblnc.tmc
GPStestdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
GPStestdispncoui.o : GPStestdispncoui.c
GPStestdispnc.o : GPStestdispnc.cc
GPStestextcdf.oui : GPStesteng.cdf
	$(EDF2OUI) GPStesteng.cdf
GPStestengext.tmc : GPStesteng.cdf
	$(EDF2EXT) GPStesteng.cdf
GPStestext.cc : GPStest.tmc ../TM/gpsd.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/flttime.tmc GPStestengext.tmc
	$(TMC) GPStest.tmc ../TM/gpsd.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/flttime.tmc GPStestengext.tmc
GPStestextoui.c : GPStestextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) GPStestextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
GPStestextoui.o : GPStestextoui.c
GPStestext.o : GPStestext.cc
doit.dep : GPStest.doit
	mkdoit3 -M -o doit  GPStest.doit
-include doit.dep
GPStestcmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd
	$(CMDGEN) -d GPStestcmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd
GPStestclt.o : GPStestcmd.cc
	$(COMPILE.clt) GPStestcmd.cc
GPStestcltoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
GPStestcltoui.o : GPStestcltoui.c
GPStestcltnc.o : GPStestcmd.cc
	$(COMPILE.cltnc) GPStestcmd.cc
GPStestcltncoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
GPStestcltncoui.o : GPStestcltncoui.c
GPStestsrvr.o : GPStestcmd.cc
	$(COMPILE.srvr) GPStestcmd.cc
GPStestsrvroui.c : $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
GPStestsrvroui.o : GPStestsrvroui.c
GPStestcol.cc : GPStest.tmc ../TM/gpsd.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/flttime.tmc /usr/local/share/huarp/cpu_usage_col.tmc ../TM/gpsd_col.tmc
	$(TMC.col) GPStest.tmc ../TM/gpsd.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/flttime.tmc /usr/local/share/huarp/cpu_usage_col.tmc ../TM/gpsd_col.tmc
GPStestcoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
GPStestcoloui.o : GPStestcoloui.c
GPStestcol.o : GPStestcol.cc

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
.cvsignore : Makefile
	@for i in $(OBJECT) $(TARGET); do echo "$$i"; done >.cvsignore
CPPFLAGS += -I ../
GENUISRCS = genui.txt
GENUISRCS += ../TM/gpsd.genui

GPStest.tbl : ../TM/gpsd.tbl GPStest_foot.tbl
	cat ../TM/gpsd.tbl GPStest_foot.tbl >GPStest.tbl

GPStesteng.cdf : $(GENUISRCS)
	genui -d eng -c $(GENUISRCS)

../gpsd_client :
	cd .. && make
