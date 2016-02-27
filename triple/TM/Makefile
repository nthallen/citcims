# Makefile Generated Wed Mar 18 10:48:27 EDT 2015
MNC=triple
SPECFILE=triple.spec
PCMFILE=triple.pcm
SRC=base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc
SRC+=dstat_conv.tmc triple.tma hrdwr.tma triple.tbl triple2.tbl
SRC+=IWG1.tbl triple.doit fast.cdf medium.cdf tripleeng.cdf
SRC+=triplejson.cdf zaber.cmd herc.cmd modbus.cmd SWStat.cmd
SRC+=IWG1_col.tmc Hercules_col.tmc SWData_col.tmc tdrift_col.tmc
SRC+=modbus_col.tmc
TOOL=triple.spec Makefile
SCRIPT=interact Experiment.config
OBJ=triplealgoa.tmc triplealgo.cc triplealgooui.c triplealgooui.o
OBJ+=triplealgo.o tripletbl.tmc triple2tbl.tmc IWG1tbl.tmc
OBJ+=tripledisp.cc tripledispoui.c tripledispoui.o tripledisp.o
OBJ+=tripletblnc.tmc triple2tblnc.tmc IWG1tblnc.tmc tripledispnc.cc
OBJ+=tripledispncoui.c tripledispncoui.o tripledispnc.o
OBJ+=tripledoit.dep fastextcdf.oui fastext.tmc fastext.cc
OBJ+=fastextoui.c fastextoui.o fastext.o mediumextcdf.oui
OBJ+=mediumext.tmc mediumext.cc mediumextoui.c mediumextoui.o
OBJ+=mediumext.o tripleengextcdf.oui tripleengext.tmc tripleengext.cc
OBJ+=tripleengextoui.c tripleengextoui.o tripleengext.o
OBJ+=triplejsonextcdf.oui triplejsonext.tmc triplejsonext.cc
OBJ+=triplejsonextoui.c triplejsonextoui.o triplejsonext.o
OBJ+=triplecmd.cc triplecmd.dat tripleclt.o triplecltoui.c
OBJ+=triplecltoui.o triplecltnc.o triplecltncoui.c triplecltncoui.o
OBJ+=triplesrvr.o triplesrvroui.c triplesrvroui.o triplecol.cc
OBJ+=triple.pcm tm.dac triplecoloui.c triplecoloui.o triplecol.o
OBJ+=dsdaq.o
TGT=triplealgo tripledisp tripledispnc tripledoit fastext mediumext
TGT+=tripleengext triplejsonext tripleclt triplecltnc triplesrvr
TGT+=triplecol
DISTRIB=../Zaber/zaber ../IWG1/IWG1 ../DSDaq/Hercules
DISTRIB+=../Modbus/modbus triple.pcm tm.dac
IDISTRIB=Experiment.config VERSION tripledoit
SRCDIST=triple.tma hrdwr.tma triple.tbl triple2.tbl IWG1.tbl
SRCDIST+=base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc
SRCDIST+=/usr/local/share/huarp/cpu_usage.tmc
SRCDIST+=/usr/local/share/huarp/tmdf.tmc
SRCDIST+=/usr/local/share/huarp/flttime.tmc
TMCBASE=base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc
TMCBASE+=/usr/local/share/huarp/cpu_usage.tmc
TMCBASE+=/usr/local/share/huarp/tmdf.tmc
TMCBASE+=/usr/local/share/huarp/flttime.tmc
CMDBASE=/usr/local/share/huarp/root.cmd
CMDBASE+=/usr/local/share/huarp/getcon.cmd zaber.cmd herc.cmd
CMDBASE+=modbus.cmd SWStat.cmd
COLBASE=IWG1_col.tmc Hercules_col.tmc
COLBASE+=/usr/local/share/huarp/cpu_usage_col.tmc
COLBASE+=/usr/local/share/huarp/tmdf_col.tmc ../DSDaq/dsdaq.cc
COLBASE+=SWData_col.tmc tdrift_col.tmc modbus_col.tmc
SWSBASE=
QCLIBASE=
PHTGT=tripletbl.tmc triple2tbl.tmc IWG1tbl.tmc
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/triple
include /usr/local/share/huarp/appgen.mk

.PHONY : all extdistribution distribution clean check_photon

all : Makefile check_photon $(TGT) .cvsignore
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
tripleengext : tripleengext.o tripleengextoui.o
	$(LINK.normCXX) tripleengext.o tripleengextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) tripleengextoui.c
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
triplealgoa.tmc : triple.tma hrdwr.tma triplesrvr
	$(SERVER) ./triplesrvr
	$(TMCALGO) -V "`./triplesrvr -R`" triple.tma hrdwr.tma
triplealgo.cc : base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc dstat_conv.tmc triplealgoa.tmc
	$(TMC) base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc dstat_conv.tmc triplealgoa.tmc
triplealgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
triplealgooui.o : triplealgooui.c
triplealgo.o : triplealgo.cc
tripletbl.tmc : triple.tbl
triple2tbl.tmc : triple2.tbl
IWG1tbl.tmc : IWG1.tbl
tripledisp.cc : base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc dstat_conv.tmc tripletbl.tmc triple2tbl.tmc IWG1tbl.tmc
	$(TMC) base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc dstat_conv.tmc tripletbl.tmc triple2tbl.tmc IWG1tbl.tmc
tripledispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
tripledispoui.o : tripledispoui.c
tripledisp.o : tripledisp.cc
tripletblnc.tmc : triple.tbl
triple2tblnc.tmc : triple2.tbl
IWG1tblnc.tmc : IWG1.tbl
tripledispnc.cc : base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc dstat_conv.tmc tripletblnc.tmc triple2tblnc.tmc IWG1tblnc.tmc
	$(TMC) base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc dstat_conv.tmc tripletblnc.tmc triple2tblnc.tmc IWG1tblnc.tmc
tripledispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
tripledispncoui.o : tripledispncoui.c
tripledispnc.o : tripledispnc.cc
tripledoit.dep : triple.doit
	mkdoit3 -M -o tripledoit  triple.doit
-include tripledoit.dep
fastextcdf.oui : fast.cdf
	$(EDF2OUI) fast.cdf
fastext.tmc : fast.cdf
	$(EDF2EXT) fast.cdf
fastext.cc : base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc fastext.tmc
	$(TMC) base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc fastext.tmc
fastextoui.c : fastextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) fastextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
fastextoui.o : fastextoui.c
fastext.o : fastext.cc
mediumextcdf.oui : medium.cdf
	$(EDF2OUI) medium.cdf
mediumext.tmc : medium.cdf
	$(EDF2EXT) medium.cdf
mediumext.cc : base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc mediumext.tmc
	$(TMC) base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc mediumext.tmc
mediumextoui.c : mediumextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) mediumextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
mediumextoui.o : mediumextoui.c
mediumext.o : mediumext.cc
tripleengextcdf.oui : tripleeng.cdf
	$(EDF2OUI) tripleeng.cdf
tripleengext.tmc : tripleeng.cdf
	$(EDF2EXT) tripleeng.cdf
tripleengext.cc : base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc tripleengext.tmc
	$(TMC) base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc tripleengext.tmc
tripleengextoui.c : tripleengextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) tripleengextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
tripleengextoui.o : tripleengextoui.c
tripleengext.o : tripleengext.cc
triplejsonextcdf.oui : triplejson.cdf
	$(EDF2OUI) triplejson.cdf
triplejsonext.tmc : triplejson.cdf
	$(EDF2EXT) triplejson.cdf
triplejsonext.cc : base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc triplejsonext.tmc
	$(TMC) base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc triplejsonext.tmc
triplejsonextoui.c : triplejsonextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) triplejsonextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
triplejsonextoui.o : triplejsonextoui.c
triplejsonext.o : triplejsonext.cc
triplecmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd zaber.cmd herc.cmd modbus.cmd SWStat.cmd
	$(CMDGEN) -d triplecmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd zaber.cmd herc.cmd modbus.cmd SWStat.cmd
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
triplecol.cc : base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc IWG1_col.tmc Hercules_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc SWData_col.tmc tdrift_col.tmc modbus_col.tmc
	$(TMC.col) base.tmc zaber.tmc herc.tmc IWG1.tmc tdrift.tmc modbus.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc IWG1_col.tmc Hercules_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc SWData_col.tmc tdrift_col.tmc modbus_col.tmc
triplecoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
triplecoloui.o : triplecoloui.c
triplecol.o : triplecol.cc
dsdaq.o : ../DSDaq/dsdaq.cc
	$(COMPILE.cc) ../DSDaq/dsdaq.cc

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
.cvsignore : Makefile
	@for i in $(OBJECT) $(TARGET); do echo "$$i"; done >.cvsignore
COLFLAGS='-Haddress.h'
CPPFLAGS+= -I ../Zaber -I ../IWG1 -I ../DSDaq -I ../Modbus
CXXFLAGS=-Wall -g

tripleeng.cdf : genui.txt
	genui -d ../eng -c genui.txt
../Zaber/zaber :
	( cd ../Zaber; make )
../DSDaq/Hercules :
	( cd ../DSDaq; make )
../Modbus/modbus :
	( cd ../Modbus; make )
address.h : triplecol.cc
