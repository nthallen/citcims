# Makefile Generated Fri Jul 26 13:06:25 EDT 2013
MNC=ToF
SPECFILE=ToF.spec
SRC=types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc
SRC+=zaber.tmc sonic.tmc tdrift.tmc SWData.tmc SWData.h IWG1.tmc
SRC+=UserPkts.tmc AthenaII_conv.tmc Hercules_conv.tmc Horiba_conv.tmc
SRC+=ToF.tbl IWG1.tbl sonic.tbl ToF.cdf ToFeng.cdf ToFzjson.cdf
SRC+=tpfilt.tmc ToF.tma ToF.sws Inlet.tma turbo.tma gasdeck.tma
SRC+=ToFz.doit AthenaII.cmd Hercules.cmd oms.cmd Horiba.cmd zaber.cmd
SRC+=SWlogs.cmd address.h SWData.cmd AthenaII_col.tmc
SRC+=Hercules_col.tmc oms_col.tmc Horiba_col.tmc tdrift_col.tmc
SRC+=SWData_col.tmc IWG1_col.tmc UserPkts_col.tmc
TOOL=ToF.spec Makefile
SCRIPT=interact runfile.AII runfile.AIIa
OBJ=address.h ToFtbl.tmc IWG1tbl.tmc sonictbl.tmc ToFdisp.cc
OBJ+=ToFdispoui.c ToFdispoui.o ToFdisp.o ToFtblnc.tmc IWG1tblnc.tmc
OBJ+=sonictblnc.tmc ToFdispnc.cc ToFdispncoui.c ToFdispncoui.o
OBJ+=ToFdispnc.o ToFextcdf.oui ToFext.tmc ToFext.cc ToFextoui.c
OBJ+=ToFextoui.o ToFext.o ToFengextcdf.oui ToFengext.tmc ToFengext.cc
OBJ+=ToFengextoui.c ToFengextoui.o ToFengext.o ToFjsonextcdf.oui
OBJ+=ToFzjsonext.tmc ToFjsonext.cc ToFjsonextoui.c ToFjsonextoui.o
OBJ+=ToFjsonext.o ToFsws.tma ToFalgoa.tmc ToFalgo.cc ToFalgooui.c
OBJ+=ToFalgooui.o ToFalgo.o doit.dep ToFcmd.cc ToFcmd.dat ToFclt.o
OBJ+=ToFcltoui.c ToFcltoui.o ToFcltnc.o ToFcltncoui.c ToFcltncoui.o
OBJ+=ToFsrvr.o ToFsrvroui.c ToFsrvroui.o ToFcol.cc ToF.pcm tm.dac
OBJ+=ToFcoloui.c ToFcoloui.o ToFcol.o dsdaq.o
TGT=ToFdisp ToFdispnc ToFext ToFengext ToFjsonext ToFalgo doit
TGT+=ToFclt ToFcltnc ToFsrvr ToFcol
DISTRIB=../IonGauge/IonGauge ../DSDaq/AthenaII ../DSDaq/Hercules
DISTRIB+=../Horiba/horiba ../Zaber/zaber ../IWG1/IWG1
DISTRIB+=../IWG1/UserPkts ../Sonic/sonic ../Zeno/Zeno_Ser ToF.pcm
DISTRIB+=tm.dac
IDISTRIB=Experiment.config VERSION doit
SRCDIST=ToF.tbl IWG1.tbl sonic.tbl ToF.tma Inlet.tma turbo.tma
SRCDIST+=gasdeck.tma types.tmc IG.tmc AthenaII.tmc Hercules.tmc
SRCDIST+=oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc
SRCDIST+=/usr/local/share/huarp/cpu_usage.tmc
SRCDIST+=/usr/local/share/huarp/tmdf.tmc
SRCDIST+=/usr/local/share/huarp/flttime.tmc SWData.tmc SWData.h
SRCDIST+=IWG1.tmc UserPkts.tmc
TMCBASE=types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc
TMCBASE+=Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc
TMCBASE+=/usr/local/share/huarp/cpu_usage.tmc
TMCBASE+=/usr/local/share/huarp/tmdf.tmc
TMCBASE+=/usr/local/share/huarp/flttime.tmc SWData.tmc SWData.h
TMCBASE+=IWG1.tmc UserPkts.tmc
CMDBASE=/usr/local/share/huarp/root.cmd
CMDBASE+=/usr/local/share/huarp/getcon.cmd
CMDBASE+=/usr/local/share/huarp/OMS.cmd AthenaII.cmd Hercules.cmd
CMDBASE+=oms.cmd Horiba.cmd zaber.cmd SWlogs.cmd address.h SWData.cmd
COLBASE=AthenaII_col.tmc Hercules_col.tmc oms_col.tmc Horiba_col.tmc
COLBASE+=tdrift_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc
COLBASE+=/usr/local/share/huarp/tmdf_col.tmc ../DSDaq/dsdaq.cc
COLBASE+=SWData_col.tmc IWG1_col.tmc UserPkts_col.tmc
SWSBASE=ToF.sws
QCLIBASE=
PHTGT=ToFtbl.tmc IWG1tbl.tmc sonictbl.tmc
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/tof
include /usr/local/share/huarp/appgen.mk

.PHONY : all extdistribution distribution clean check_photon

all : Makefile check_photon $(TGT) .cvsignore
Makefile : ToF.spec
	appgen ToF.spec
VERSION=`cat VERSION`
extdistribution : $(DSTRB) $(SRCDIST) VERSION
	@[ -d $(TGTDIR)/bin ] || mkdir $(TGTDIR)/bin
	@[ -d $(TGTDIR)/bin/$(VERSION) ] || mkdir $(TGTDIR)/bin/$(VERSION)
	@[ -d  $(TGTDIR)/bin/$(VERSION)/Base ] || mkdir $(TGTDIR)/bin/$(VERSION)/Base
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
ToFdisp : ToFdisp.o ToFdispoui.o
	$(LINK.normCXX) ToFdisp.o ToFdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) ToFdispoui.c
ToFdispnc : ToFdispnc.o ToFdispncoui.o
	$(LINK.normCXX) ToFdispnc.o ToFdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) ToFdispncoui.c
ToFext : ToFext.o ToFextoui.o
	$(LINK.normCXX) ToFext.o ToFextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) ToFextoui.c
ToFengext : ToFengext.o ToFengextoui.o
	$(LINK.normCXX) ToFengext.o ToFengextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) ToFengextoui.c
ToFjsonext : ToFjsonext.o ToFjsonextoui.o
	$(LINK.normCXX) ToFjsonext.o ToFjsonextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) ToFjsonextoui.c
ToFalgo : ToFalgo.o ToFalgooui.o
	$(LINK.normCXX) ToFalgo.o ToFalgooui.o -ltmpp -ltm -lnort
	$(OUIUSE) ToFalgooui.c
doit : ToFz.doit
	mkdoit3 -o doit  ToFz.doit
ToFclt : ToFclt.o ToFcltoui.o
	$(LINK.normCXX) ToFclt.o ToFcltoui.o -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) ToFcltoui.c
ToFcltnc : ToFcltnc.o ToFcltncoui.o
	$(LINK.normCXX) ToFcltnc.o ToFcltncoui.o -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) ToFcltncoui.c
ToFsrvr : ToFsrvr.o ToFsrvroui.o
	$(LINK.privCXX) ToFsrvr.o ToFsrvroui.o -ltmpp -ltm -lnort
	$(OUIUSE) ToFsrvroui.c
	$(PROMOTE) ToFsrvr
ToFcol : ToFcol.o dsdaq.o ToFcoloui.o
	$(LINK.privCXX) ToFcol.o dsdaq.o ToFcoloui.o -ltmpp -ltm -lnort
	$(OUIUSE) ToFcoloui.c
	$(PROMOTE) ToFcol
ToFtbl.tmc : ToF.tbl
IWG1tbl.tmc : IWG1.tbl
sonictbl.tmc : sonic.tbl
ToFdisp.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc AthenaII_conv.tmc Hercules_conv.tmc Horiba_conv.tmc ToFtbl.tmc IWG1tbl.tmc sonictbl.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc AthenaII_conv.tmc Hercules_conv.tmc Horiba_conv.tmc ToFtbl.tmc IWG1tbl.tmc sonictbl.tmc
ToFdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFdispoui.o : ToFdispoui.c SWData.h
ToFdisp.o : ToFdisp.cc SWData.h
ToFtblnc.tmc : ToF.tbl
IWG1tblnc.tmc : IWG1.tbl
sonictblnc.tmc : sonic.tbl
ToFdispnc.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc AthenaII_conv.tmc Hercules_conv.tmc Horiba_conv.tmc ToFtblnc.tmc IWG1tblnc.tmc sonictblnc.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc AthenaII_conv.tmc Hercules_conv.tmc Horiba_conv.tmc ToFtblnc.tmc IWG1tblnc.tmc sonictblnc.tmc
ToFdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFdispncoui.o : ToFdispncoui.c SWData.h
ToFdispnc.o : ToFdispnc.cc SWData.h
ToFextcdf.oui : ToF.cdf
	$(EDF2OUI) ToF.cdf
ToFext.tmc : ToF.cdf
	$(EDF2EXT) ToF.cdf
ToFext.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc ToFext.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc ToFext.tmc
ToFextoui.c : ToFextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) ToFextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFextoui.o : ToFextoui.c SWData.h
ToFext.o : ToFext.cc SWData.h
ToFengextcdf.oui : ToFeng.cdf
	$(EDF2OUI) ToFeng.cdf
ToFengext.tmc : ToFeng.cdf
	$(EDF2EXT) ToFeng.cdf
ToFengext.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc ToFengext.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc ToFengext.tmc
ToFengextoui.c : ToFengextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) ToFengextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFengextoui.o : ToFengextoui.c SWData.h
ToFengext.o : ToFengext.cc SWData.h
ToFjsonextcdf.oui : ToFzjson.cdf
	$(EDF2OUI) ToFzjson.cdf
ToFzjsonext.tmc : ToFzjson.cdf
	$(EDF2EXT) ToFzjson.cdf
ToFjsonext.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc ToFzjsonext.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc ToFzjsonext.tmc
ToFjsonextoui.c : ToFjsonextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) ToFjsonextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFjsonextoui.o : ToFjsonextoui.c SWData.h
ToFjsonext.o : ToFjsonext.cc SWData.h
ToFsws.tma : ToF.sws
	$(COMPILE.sws) ToF.sws
ToFalgoa.tmc : ToF.tma ToFsws.tma Inlet.tma turbo.tma gasdeck.tma ToFsrvr
	$(SERVER) ./ToFsrvr
	$(TMCALGO) -V "`./ToFsrvr -R`" ToF.tma ToFsws.tma Inlet.tma turbo.tma gasdeck.tma
ToFalgo.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc tpfilt.tmc ToFalgoa.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc tpfilt.tmc ToFalgoa.tmc
ToFalgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFalgooui.o : ToFalgooui.c SWData.h
ToFalgo.o : ToFalgo.cc SWData.h
doit.dep : ToFz.doit
	mkdoit3 -M -o doit  ToFz.doit
-include doit.dep
ToFcmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd /usr/local/share/huarp/OMS.cmd AthenaII.cmd Hercules.cmd oms.cmd Horiba.cmd zaber.cmd SWlogs.cmd SWData.cmd
	$(CMDGEN) -d ToFcmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd /usr/local/share/huarp/OMS.cmd AthenaII.cmd Hercules.cmd oms.cmd Horiba.cmd zaber.cmd SWlogs.cmd SWData.cmd
ToFclt.o : ToFcmd.cc
	$(COMPILE.clt) ToFcmd.cc
ToFcltoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
ToFcltoui.o : ToFcltoui.c address.h
ToFcltnc.o : ToFcmd.cc
	$(COMPILE.cltnc) ToFcmd.cc
ToFcltncoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
ToFcltncoui.o : ToFcltncoui.c address.h
ToFsrvr.o : ToFcmd.cc
	$(COMPILE.srvr) ToFcmd.cc
ToFsrvroui.c : $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
ToFsrvroui.o : ToFsrvroui.c address.h
ToFcol.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc AthenaII_col.tmc Hercules_col.tmc oms_col.tmc Horiba_col.tmc tdrift_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc SWData_col.tmc IWG1_col.tmc UserPkts_col.tmc
	$(TMC.col) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc sonic.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc AthenaII_col.tmc Hercules_col.tmc oms_col.tmc Horiba_col.tmc tdrift_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc SWData_col.tmc IWG1_col.tmc UserPkts_col.tmc
ToFcoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
ToFcoloui.o : ToFcoloui.c SWData.h
ToFcol.o : ToFcol.cc SWData.h
dsdaq.o : ../DSDaq/dsdaq.cc SWData.h
	$(COMPILE.cc) ../DSDaq/dsdaq.cc
SWData.h SWData.tmc SWData_col.tmc SWData.cmd :  ToF.sws
	swscomp -o SWData  ToF.sws

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
.cvsignore : Makefile
	@for i in $(OBJECT) $(TARGET); do echo "$$i"; done >.cvsignore
COLFLAGS=-Haddress.h
CPPFLAGS += -I ../IonGauge -I ../DSDaq -I ../Horiba -I ../Zaber -I ../Sonic
CPPFLAGS += -I ../IWG1
CPPFLAGS += -I ../Zeno
CXXFLAGS = -Wall -g
ToFeng.cdf : genui.txt
	genui -d ../eng -c genui.txt
address.h : ToFcol.cc
../Zaber/zaber :
	cd ../Zaber && make
../IonGauge/IonGauge :
	cd ../IonGauge && make
../DSDaq/AthenaII ../DSDaq/Hercules :
	cd ../DSDaq && make
../Horiba/horiba :
	cd ../Horiba && make
../IWG1/IWG1 :
	cd ../IWG1 && make IWG1
../IWG1/UserPkts :
	cd ../IWG1 && make UserPkts
../Zeno/Zeno_Ser :
	cd ../Zeno && make Zeno_Ser
.PHONY : all-clean
all-clean : clean
	cd ../Zaber && make clean
	cd ../IonGauge && make clean
	cd ../DSDaq && make clean
	cd ../Horiba && make clean
