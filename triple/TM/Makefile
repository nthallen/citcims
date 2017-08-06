# Invoking: appgen_module IWG1 X mode=default
# Invoking: appgen_module modbus X mode=disable
# Invoking: appgen_module Zaber X mode=dual
# Invoking: appgen_module ../../ToF/Edwards_nXDS/TM/nXDS X mode=remote
# Invoking: appgen_module ../../ToF/UPS/TM/UPS X mode=remote
# Makefile Generated Sun Aug 06 09:32:22 PDT 2017
MNC=triple
SPECFILE=triple.spec
PCMFILE=triple.pcm
SRC=base.tmc herc.tmc tdrift.tmc
SRC+=/usr/local/share/huarp/cpu_usage.tmc
SRC+=/usr/local/share/huarp/tmdf.tmc
SRC+=/usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc
SRC+=../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc
SRC+=UPS.tmc IWG1.tbl dstat_conv.tmc triple.tma hrdwr.tma
SRC+=../../ToF/Edwards_nXDS/TM/nXDS_conv.tmc triple.tbl triple2.tbl
SRC+=UPSwin.tbl triple.doit fast.cdf medium.cdf triplejson.cdf
SRC+=/usr/local/share/huarp/root.cmd
SRC+=/usr/local/share/huarp/getcon.cmd herc.cmd SWStat.cmd
SRC+=../Zaber/TM/zaber.cmd Hercules_col.tmc
SRC+=/usr/local/share/huarp/cpu_usage_col.tmc
SRC+=/usr/local/share/huarp/tmdf_col.tmc ../DSDaq/dsdaq.cc
SRC+=SWData_col.tmc tdrift_col.tmc ../IWG1/TM/IWG1_col.tmc
SRC+=../../ToF/Edwards_nXDS/TM/nXDS_col.tmc
SRC+=../../ToF/UPS/TM/UPS_col.tmc triple.genui ../IWG1/TM/IWG1.genui
SRC+=zaber.genui ../../ToF/Edwards_nXDS/TM/nXDS.genui
SRC+=../../ToF/UPS/TM/UPS.genui triple.pcm
TOOL=triple.spec Makefile
SCRIPT=interact Experiment.config
OBJ=IWG1tbl.tmc IWG1disp.cc IWG1dispoui.c IWG1dispoui.o IWG1disp.o
OBJ+=IWG1tblnc.tmc IWG1dispnc.cc IWG1dispncoui.c IWG1dispncoui.o
OBJ+=IWG1dispnc.o triplealgoa.tmc triplealgo.cc triplealgooui.c
OBJ+=triplealgooui.o triplealgo.o tripletbl.tmc triple2tbl.tmc
OBJ+=UPSwintbl.tmc tripledisp.cc tripledispoui.c tripledispoui.o
OBJ+=tripledisp.o tripletblnc.tmc triple2tblnc.tmc UPSwintblnc.tmc
OBJ+=tripledispnc.cc tripledispncoui.c tripledispncoui.o
OBJ+=tripledispnc.o tripledoit.dep fastextcdf.oui fastcdf.tmc
OBJ+=fastext.cc fastextoui.c fastextoui.o fastext.o mediumextcdf.oui
OBJ+=mediumcdf.tmc mediumext.cc mediumextoui.c mediumextoui.o
OBJ+=mediumext.o triplejsonextcdf.oui triplejsoncdf.tmc
OBJ+=triplejsonext.cc triplejsonextoui.c triplejsonextoui.o
OBJ+=triplejsonext.o triplecmd.cc triplecmd.dat tripleclt.o
OBJ+=triplecltoui.c triplecltoui.o triplecltnc.o triplecltncoui.c
OBJ+=triplecltncoui.o triplesrvr.o triplesrvroui.c triplesrvroui.o
OBJ+=triplecol.cc tm.dac triplecoloui.c triplecoloui.o triplecol.o
OBJ+=dsdaq.o tripleengext.cdf tripleengextcdf.oui tripleengextcdf.tmc
OBJ+=tripleengext.cc tripleengextoui.c tripleengextoui.o
OBJ+=tripleengext.o IWG1tbl.tmc.dep IWG1tblnc.tmc.dep
OBJ+=tripletbl.tmc.dep triple2tbl.tmc.dep UPSwintbl.tmc.dep
OBJ+=tripletblnc.tmc.dep triple2tblnc.tmc.dep UPSwintblnc.tmc.dep
TGT=IWG1disp IWG1dispnc triplealgo tripledisp tripledispnc
TGT+=tripledoit fastext mediumext triplejsonext tripleclt triplecltnc
TGT+=triplesrvr triplecol tripleengext
IGNORE=SWStat_backup.cmd SWStat_new.cmd files.tar herc_new.cmd
IGNORE+=herc_old.cmd herc_old.tmc hrdwr_160402_old.tma
IGNORE+=hrdwr_160804.tma hrdwr_170119.tma hrdwr_SEAC.tma
IGNORE+=triple_160402_old.tma triple_BEFOREAUTOCALCHANGES_160501.tma
IGNORE+=triple_SEAC.tma triple_new.tma
DISTRIB=../DSDaq/Hercules ../IWG1/TM/../IWG1 ../Zaber/TM/../zaber
DISTRIB+=triple.pcm tm.dac
IDISTRIB=Experiment.config VERSION tripledoit
SRCDIST=IWG1.tbl triple.tma hrdwr.tma triple.tbl triple2.tbl
SRCDIST+=UPSwin.tbl base.tmc herc.tmc tdrift.tmc
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
GENUIBASE=triple.genui ../IWG1/TM/IWG1.genui zaber.genui
GENUIBASE+=../../ToF/Edwards_nXDS/TM/nXDS.genui
GENUIBASE+=../../ToF/UPS/TM/UPS.genui
EXTBASE=../../ToF/Edwards_nXDS/TM/nXDS_conv.tmc
SPECDEPBASE=../IWG1/TM/IWG1.agm ../IWG1/TM/IWG1.tbl.src
SPECDEPBASE+=../Modbus/TM/modbus.agm ../Zaber/TM/Zaber.agm
SPECDEPBASE+=../Zaber/TM/zaber.genui.in
SPECDEPBASE+=../../ToF/Edwards_nXDS/TM/nXDS.agm
SPECDEPBASE+=../../ToF/Edwards_nXDS/TM/nXDS.tbl.in
SPECDEPBASE+=../../ToF/UPS/TM/UPS.agm ../../ToF/UPS/TM/UPS.tmc.in
SPECDEPBASE+=../../ToF/UPS/TM/UPS.tbl.in
SPECTGTBASE=IWG1.tbl zaber.genui nXDS.tbl UPS.tmc UPS.tbl
AG_CPPFLAGS=-I ../IWG1/TM/.. -I ../Zaber/TM/.. -I
AG_CPPFLAGS+=../../ToF/Edwards_nXDS/TM/.. -I ../../ToF/UPS/TM/..
PHTGT=IWG1tbl.tmc tripletbl.tmc triple2tbl.tmc UPSwintbl.tmc
SOURCE=$(SRC) $(TOOL) $(SCRIPT)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/triple
include /usr/local/share/huarp/appgen.mk

.PHONY : all all-dist extdistribution distribution clean clean-dist check_photon

IGNOREFILE=.gitignore
all : Makefile check_photon $(TGT) $(IGNOREFILE)
all-dist : $(DSTRB) $(SRCDIST) VERSION
Makefile $(SPECTGTBASE) : triple.spec $(SPECDEPBASE)
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
-include IWG1tbl.tmc.dep
IWG1disp.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc IWG1tbl.tmc VERSION
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc IWG1tbl.tmc
IWG1dispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
IWG1dispoui.o : IWG1dispoui.c
IWG1disp.o : IWG1disp.cc
IWG1tblnc.tmc : IWG1.tbl
-include IWG1tblnc.tmc.dep
IWG1dispnc.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc IWG1tblnc.tmc VERSION
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc IWG1tblnc.tmc
IWG1dispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
IWG1dispncoui.o : IWG1dispncoui.c
IWG1dispnc.o : IWG1dispnc.cc
triplealgoa.tmc : triple.tma hrdwr.tma triplesrvr
	$(SERVER) ./triplesrvr
	$(TMCALGO) -V "`./triplesrvr -R`" triple.tma hrdwr.tma
triplealgo.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc dstat_conv.tmc triplealgoa.tmc VERSION
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc dstat_conv.tmc triplealgoa.tmc
triplealgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
triplealgooui.o : triplealgooui.c
triplealgo.o : triplealgo.cc
tripletbl.tmc : triple.tbl
-include tripletbl.tmc.dep
triple2tbl.tmc : triple2.tbl
-include triple2tbl.tmc.dep
UPSwintbl.tmc : UPSwin.tbl
-include UPSwintbl.tmc.dep
tripledisp.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc dstat_conv.tmc ../../ToF/Edwards_nXDS/TM/nXDS_conv.tmc tripletbl.tmc triple2tbl.tmc IWG1tbl.tmc UPSwintbl.tmc VERSION
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc dstat_conv.tmc ../../ToF/Edwards_nXDS/TM/nXDS_conv.tmc tripletbl.tmc triple2tbl.tmc IWG1tbl.tmc UPSwintbl.tmc
tripledispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
tripledispoui.o : tripledispoui.c
tripledisp.o : tripledisp.cc
tripletblnc.tmc : triple.tbl
-include tripletblnc.tmc.dep
triple2tblnc.tmc : triple2.tbl
-include triple2tblnc.tmc.dep
UPSwintblnc.tmc : UPSwin.tbl
-include UPSwintblnc.tmc.dep
tripledispnc.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc dstat_conv.tmc ../../ToF/Edwards_nXDS/TM/nXDS_conv.tmc tripletblnc.tmc triple2tblnc.tmc IWG1tblnc.tmc UPSwintblnc.tmc VERSION
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc dstat_conv.tmc ../../ToF/Edwards_nXDS/TM/nXDS_conv.tmc tripletblnc.tmc triple2tblnc.tmc IWG1tblnc.tmc UPSwintblnc.tmc
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
fastext.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc fastcdf.tmc VERSION
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc fastcdf.tmc
fastextoui.c : fastextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) fastextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
fastextoui.o : fastextoui.c
fastext.o : fastext.cc
mediumextcdf.oui : medium.cdf
	$(EDF2OUI) medium.cdf
mediumcdf.tmc : medium.cdf
	$(EDF2EXT) medium.cdf
mediumext.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc mediumcdf.tmc VERSION
	$(TMC) base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc mediumcdf.tmc
mediumextoui.c : mediumextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) mediumextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
mediumextoui.o : mediumextoui.c
mediumext.o : mediumext.cc
triplejsonextcdf.oui : triplejson.cdf
	$(EDF2OUI) triplejson.cdf
triplejsoncdf.tmc : triplejson.cdf
	$(EDF2EXT) triplejson.cdf
triplejsonext.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc triplejsoncdf.tmc VERSION
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
triplecol.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc Hercules_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc SWData_col.tmc tdrift_col.tmc ../IWG1/TM/IWG1_col.tmc ../../ToF/Edwards_nXDS/TM/nXDS_col.tmc ../../ToF/UPS/TM/UPS_col.tmc VERSION
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
tripleengext.cc : base.tmc herc.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc ../IWG1/TM/IWG1.tmc ../Zaber/TM/zaber2.tmc ../../ToF/Edwards_nXDS/TM/nXDS.tmc UPS.tmc ../../ToF/Edwards_nXDS/TM/nXDS_conv.tmc tripleengextcdf.tmc VERSION
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
	@for i in $(OBJECT) $(IGNORE) $(TARGET); do echo "$$i"; done >$(IGNOREFILE)
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
.PHONY : clean-nXDS
clean-dist : clean-nXDS
clean-nXDS :
	cd ../../ToF/Edwards_nXDS/TM/.. && make clean
COLFLAGS='-Haddress.h'
CPPFLAGS+= -I ../DSDaq
CXXFLAGS=-Wall -g

../DSDaq/Hercules :
	( cd ../DSDaq; make )
address.h : triplecol.cc
