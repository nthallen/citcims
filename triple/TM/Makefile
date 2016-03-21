# Invoking: appgen_module IWG1 X mode=default
# Invoking: appgen_module modbus X mode=disable
# Invoking: appgen_module Zaber X mode=dual
# Invoking: appgen_module ../../ToF/Edwards_nXDS/TM/nXDS X mode=remote
# Invoking: appgen_module ../../ToF/UPS/TM/UPS X mode=remote
# Makefile Generated Sun Mar 20 19:20:02 PDT 2016
MNC=triple
SPECFILE=triple.spec
PCMFILE=triple.pcm
SRC=base.tmc herc.tmc tdrift.tmc IWG1.tbl UPS.tmc dstat_conv.tmc
SRC+=triple.tma hrdwr.tma triple.tbl triple2.tbl UPS.tbl triple.doit
SRC+=fast.cdf medium.cdf triplejson.cdf herc.cmd SWStat.cmd
SRC+=Hercules_col.tmc SWData_col.tmc tdrift_col.tmc triple.genui
SRC+=zaber.genui
TOOL=triple.spec Makefile
SCRIPT=interact Experiment.config
OBJ=IWG1tbl.tmc IWG1disp.cc IWG1dispoui.c IWG1dispoui.o IWG1disp.o
OBJ+=IWG1tblnc.tmc IWG1dispnc.cc IWG1dispncoui.c IWG1dispncoui.o
OBJ+=IWG1dispnc.o triplealgoa.tmc triplealgo.cc triplealgooui.c
OBJ+=triplealgooui.o triplealgo.o tripletbl.tmc triple2tbl.tmc
OBJ+=UPStbl.tmc tripledisp.cc tripledispoui.c tripledispoui.o
OBJ+=tripledisp.o tripletblnc.tmc triple2tblnc.tmc UPStblnc.tmc
OBJ+=tripledispnc.cc tripledispncoui.c tripledispncoui.o
OBJ+=tripledispnc.o tripledoit.dep fastextcdf.oui fastcdf.tmc
OBJ+=fastext.cc fastextoui.c fastextoui.o fastext.o mediumextcdf.oui
OBJ+=mediumcdf.tmc mediumext.cc mediumextoui.c mediumextoui.o
OBJ+=mediumext.o triplejsonextcdf.oui triplejsoncdf.tmc
OBJ+=triplejsonext.cc triplejsonextoui.c triplejsonextoui.o
OBJ+=triplejsonext.o triplecmd.cc triplecmd.dat tripleclt.o
OBJ+=triplecltoui.c triplecltoui.o triplecltnc.o triplecltncoui.c
OBJ+=triplecltncoui.o triplesrvr.o triplesrvroui.c triplesrvroui.o
OBJ+=triplecol.cc triple.pcm tm.dac triplecoloui.c triplecoloui.o
OBJ+=triplecol.o dsdaq.o tripleengext.cdf tripleengextcdf.oui
OBJ+=tripleengextcdf.tmc tripleengext.cc tripleengextoui.c
OBJ+=tripleengextoui.o tripleengext.o
TGT=IWG1disp IWG1dispnc triplealgo tripledisp tripledispnc
TGT+=tripledoit fastext mediumext triplejsonext tripleclt triplecltnc
TGT+=triplesrvr triplecol tripleengext
DISTRIB=../DSDaq/Hercules ../IWG1/TM/../IWG1 ../Zaber/TM/../zaber
DISTRIB+=triple.pcm tm.dac
IDISTRIB=Experiment.config VERSION tripledoit
SRCDIST=IWG1.tbl triple.tma hrdwr.tma triple.tbl triple2.tbl UPS.tbl
SRCDIST+=base.tmc herc.tmc tdrift.tmc
SRCDIST+=/usr/local/share/huarp/cpu_usage.tmc
SRCDIST+=/usr/local/share/huarp/tmdf.tmc
SRCDIST+=/usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc
SRCDIST+=../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc
SRCDIST+=UPS.tmc
TMCBASE=base.tmc herc.tmc tdrift.tmc
TMCBASE+=/usr/local/share/huarp/cpu_usage.tmc
TMCBASE+=/usr/local/share/huarp/tmdf.tmc
TMCBASE+=/usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc
TMCBASE+=../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc
TMCBASE+=UPS.tmc
CMDBASE=/usr/local/share/huarp/root.cmd
CMDBASE+=/usr/local/share/huarp/getcon.cmd herc.cmd SWStat.cmd
CMDBASE+=../Zaber/TM/zaber.cmd
COLBASE=Hercules_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc
COLBASE+=/usr/local/share/huarp/tmdf_col.tmc ../DSDaq/dsdaq.cc
COLBASE+=SWData_col.tmc tdrift_col.tmc ../IWG1/TM/IWG1_col.tmc
COLBASE+=../../ToF/Edwards_nXDS/TM/nXDS_col.tmc
COLBASE+=../../ToF/UPS/TM/UPS_col.tmc
SWSBASE=
QCLIBASE=
AG_CPPFLAGS=-I ../IWG1/TM/.. -I ../Zaber/TM/.. -I
AG_CPPFLAGS+=../../ToF/Edwards_nXDS/TM/.. -I ../../ToF/UPS/TM/..
PHTGT=IWG1tbl.tmc tripletbl.tmc triple2tbl.tmc UPStbl.tmc
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/triple
include /usr/local/share/huarp/appgen.mk

.PHONY : all all-dist extdistribution distribution clean clean-dist check_photon

IGNOREFILE=.gitignore
all : Makefile check_photon $(TGT) $(IGNOREFILE)
all-dist : $(DSTRB) $(SRCDIST) VERSION
Makefile : triple.spec
	appgen triple.spec
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
IWG1disp : IWG1disp.o IWG1dispoui.o
	$(LINK.normCXX) IWG1disp.o IWG1dispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) IWG1dispoui.c
IWG1dispnc : IWG1dispnc.o IWG1dispncoui.o
	$(LINK.normCXX) IWG1dispnc.o IWG1dispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) IWG1dispncoui.c
triplealgo : triplealgo.o triplealgooui.o
	$(LINK.normCXX) triplealgo.o triplealgooui.o -ltmpp -ltm -lnort
	$(OUIUSE) triplealgooui.c
tripledisp : tripledisp.o tripledispoui.o
	$(LINK.normCXX) tripledisp.o tripledispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) tripledispoui.c
tripledispnc : tripledispnc.o tripledispncoui.o
	$(LINK.normCXX) tripledispnc.o tripledispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) tripledispncoui.c
tripledoit : triple.doit
	mkdoit3 -o tripledoit  triple.doit
fastext : fastext.o fastextoui.o
	$(LINK.normCXX) fastext.o fastextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) fastextoui.c
mediumext : mediumext.o mediumextoui.o
	$(LINK.normCXX) mediumext.o mediumextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) mediumextoui.c
triplejsonext : triplejsonext.o triplejsonextoui.o
	$(LINK.normCXX) triplejsonext.o triplejsonextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) triplejsonextoui.c
tripleclt : tripleclt.o triplecltoui.o
	$(LINK.normCXX) tripleclt.o triplecltoui.o -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) triplecltoui.c
triplecltnc : triplecltnc.o triplecltncoui.o
	$(LINK.normCXX) triplecltnc.o triplecltncoui.o -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) triplecltncoui.c
triplesrvr : triplesrvr.o triplesrvroui.o
	$(LINK.privCXX) triplesrvr.o triplesrvroui.o -ltmpp -ltm -lnort
	$(OUIUSE) triplesrvroui.c
	$(PROMOTE) triplesrvr
triplecol : triplecol.o dsdaq.o triplecoloui.o
	$(LINK.privCXX) triplecol.o dsdaq.o triplecoloui.o -ltmpp -ltm -lnort
	$(OUIUSE) triplecoloui.c
	$(PROMOTE) triplecol
tripleengext : tripleengext.o tripleengextoui.o
	$(LINK.normCXX) tripleengext.o tripleengextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) tripleengextoui.c
IWG1tbl.tmc : IWG1.tbl
IWG1disp.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc IWG1tbl.tmc
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc IWG1tbl.tmc
IWG1dispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
IWG1dispoui.o : IWG1dispoui.c
IWG1disp.o : IWG1disp.cc
IWG1tblnc.tmc : IWG1.tbl
IWG1dispnc.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc IWG1tblnc.tmc
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc IWG1tblnc.tmc
IWG1dispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
IWG1dispncoui.o : IWG1dispncoui.c
IWG1dispnc.o : IWG1dispnc.cc
triplealgoa.tmc : triple.tma hrdwr.tma triplesrvr
	$(SERVER) ./triplesrvr
	$(TMCALGO) -V "`./triplesrvr -R`" triple.tma hrdwr.tma
triplealgo.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc dstat_conv.tmc triplealgoa.tmc
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc dstat_conv.tmc triplealgoa.tmc
triplealgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
triplealgooui.o : triplealgooui.c
triplealgo.o : triplealgo.cc
tripletbl.tmc : triple.tbl
triple2tbl.tmc : triple2.tbl
UPStbl.tmc : UPS.tbl
tripledisp.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc dstat_conv.tmc ../../ToF/Edwards_nXDS/TM/nXDS_conv.tmc tripletbl.tmc triple2tbl.tmc IWG1tbl.tmc UPStbl.tmc
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc dstat_conv.tmc ../../ToF/Edwards_nXDS/TM/nXDS_conv.tmc tripletbl.tmc triple2tbl.tmc IWG1tbl.tmc UPStbl.tmc
tripledispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
tripledispoui.o : tripledispoui.c
tripledisp.o : tripledisp.cc
tripletblnc.tmc : triple.tbl
triple2tblnc.tmc : triple2.tbl
UPStblnc.tmc : UPS.tbl
tripledispnc.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc dstat_conv.tmc ../../ToF/Edwards_nXDS/TM/nXDS_conv.tmc tripletblnc.tmc triple2tblnc.tmc IWG1tblnc.tmc UPStblnc.tmc
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc dstat_conv.tmc ../../ToF/Edwards_nXDS/TM/nXDS_conv.tmc tripletblnc.tmc triple2tblnc.tmc IWG1tblnc.tmc UPStblnc.tmc
tripledispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
tripledispncoui.o : tripledispncoui.c
tripledispnc.o : tripledispnc.cc
tripledoit.dep : triple.doit
	mkdoit3 -M -o tripledoit  triple.doit
-include tripledoit.dep
fastextcdf.oui : fast.cdf
	$(EDF2OUI) fast.cdf
fastcdf.tmc : fast.cdf
	$(EDF2EXT) fast.cdf
fastext.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc fastcdf.tmc
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc fastcdf.tmc
fastextoui.c : fastextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) fastextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
fastextoui.o : fastextoui.c
fastext.o : fastext.cc
mediumextcdf.oui : medium.cdf
	$(EDF2OUI) medium.cdf
mediumcdf.tmc : medium.cdf
	$(EDF2EXT) medium.cdf
mediumext.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc mediumcdf.tmc
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc mediumcdf.tmc
mediumextoui.c : mediumextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) mediumextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
mediumextoui.o : mediumextoui.c
mediumext.o : mediumext.cc
triplejsonextcdf.oui : triplejson.cdf
	$(EDF2OUI) triplejson.cdf
triplejsoncdf.tmc : triplejson.cdf
	$(EDF2EXT) triplejson.cdf
triplejsonext.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc triplejsoncdf.tmc
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc triplejsoncdf.tmc
triplejsonextoui.c : triplejsonextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) triplejsonextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
triplejsonextoui.o : triplejsonextoui.c
triplejsonext.o : triplejsonext.cc
triplecmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd herc.cmd SWStat.cmd ../Zaber/TM/zaber.cmd
	$(CMDGEN) -d triplecmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd herc.cmd SWStat.cmd ../Zaber/TM/zaber.cmd
tripleclt.o : triplecmd.cc
	$(COMPILE.clt) triplecmd.cc
triplecltoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
triplecltoui.o : triplecltoui.c
triplecltnc.o : triplecmd.cc
	$(COMPILE.cltnc) triplecmd.cc
triplecltncoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
triplecltncoui.o : triplecltncoui.c
triplesrvr.o : triplecmd.cc
	$(COMPILE.srvr) triplecmd.cc
triplesrvroui.c : $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
triplesrvroui.o : triplesrvroui.c
triplecol.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc Hercules_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc SWData_col.tmc tdrift_col.tmc ../IWG1/TM/IWG1_col.tmc ../../ToF/Edwards_nXDS/TM/nXDS_col.tmc ../../ToF/UPS/TM/UPS_col.tmc
	$(TMC.col) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc Hercules_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc SWData_col.tmc tdrift_col.tmc ../IWG1/TM/IWG1_col.tmc ../../ToF/Edwards_nXDS/TM/nXDS_col.tmc ../../ToF/UPS/TM/UPS_col.tmc
triplecoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
triplecoloui.o : triplecoloui.c
triplecol.o : triplecol.cc
dsdaq.o : ../DSDaq/dsdaq.cc
	$(COMPILE.cc) ../DSDaq/dsdaq.cc
tripleengext.cdf : triple.genui ../IWG1/TM/IWG1.genui zaber.genui ../../ToF/Edwards_nXDS/TM/nXDS.genui ../../ToF/UPS/TM/UPS.genui
	$(GENUI2ENG) triple.genui ../IWG1/TM/IWG1.genui zaber.genui ../../ToF/Edwards_nXDS/TM/nXDS.genui ../../ToF/UPS/TM/UPS.genui
tripleengextcdf.oui : tripleengext.cdf
	$(EDF2OUI) tripleengext.cdf
tripleengextcdf.tmc : tripleengext.cdf
	$(EDF2EXT) tripleengext.cdf
tripleengext.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc ../../ToF/Edwards_nXDS/TM/nXDS_conv.tmc tripleengextcdf.tmc
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc ../../ToF/Edwards_nXDS/TM/nXDS_conv.tmc tripleengextcdf.tmc
tripleengextoui.c : tripleengextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) tripleengextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
tripleengextoui.o : tripleengextoui.c
tripleengext.o : tripleengext.cc

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
clean-dist : clean
$(IGNOREFILE) : Makefile
	@for i in $(OBJECT) $(TARGET); do echo "$$i"; done >$(IGNOREFILE)
../IWG1/TM/../IWG1 :
	cd ../IWG1/TM/.. && make IWG1
.PHONY : clean-IWG1
clean-dist : clean-IWG1
clean-IWG1 :
	cd ../IWG1/TM/.. && make clean
.PHONY : clean-modbus
clean-dist : clean-modbus
clean-modbus :
	cd ../Modbus/TM/.. && make clean
../Zaber/TM/../zaber :
	cd ../Zaber/TM/.. && make
.PHONY : clean-zaber
clean-dist : clean-zaber
clean-zaber :
	cd ../Zaber/TM/.. && make clean
COLFLAGS='-Haddress.h'
CPPFLAGS+= -I ../DSDaq
CXXFLAGS=-Wall -g

../DSDaq/Hercules :
	( cd ../DSDaq; make )
address.h : triplecol.cc
