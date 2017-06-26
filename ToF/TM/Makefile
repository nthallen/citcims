# Invoking: appgen_module Horiba X mode=default
# Invoking: appgen_module IonGauge X mode=default Hz=1
# Invoking: appgen_module nXDS X mode=default
# Invoking: appgen_module OMS X mode=Y OMS1=Insl Group=Inlet
# Invoking: appgen_module UPS X mode=default
# Invoking: appgen_module gpsd X mode=default
# Invoking: appgen_module IWG1 X mode=UserPkts2
# Invoking: appgen_module Zaber X mode=default
# Invoking: appgen_module Sonic X mode=disable Hz=8
# Invoking: appgen_module Zeno X mode=disable
# Makefile Generated Mon Jun 26 16:20:23 PDT 2017
MNC=ToF
SPECFILE=ToF.spec
PCMFILE=ToF.pcm
SRC=types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc SWData.tmc
SRC+=SWData.h IonGauge.tmc OMS.tmc UPS.tmc IWG1.tbl UserPkts.tbl
SRC+=AthenaII_conv.tmc Hercules_conv.tmc ToF.tbl ToFB.tbl ToF.cdf
SRC+=ToFajson.cdf tpfilt.tmc ToF.tma ToF.sws Inlet.tma turbo.tma
SRC+=gasdeck.tma ToF.doit AthenaII.cmd Hercules.cmd SWlogs.cmd
SRC+=address.h SWData.cmd omsaxis.cmd AthenaII_col.tmc
SRC+=Hercules_col.tmc tdrift_col.tmc SWData_col.tmc ToF.genui
SRC+=IonGauge.genui OMS.genui
TOOL=ToF.spec Makefile
SCRIPT=interact runfile.AII runfile.AIIa
OBJ=address.h IWG1tbl.tmc IWG1disp.cc IWG1dispoui.c IWG1dispoui.o
OBJ+=IWG1disp.o IWG1tblnc.tmc IWG1dispnc.cc IWG1dispncoui.c
OBJ+=IWG1dispncoui.o IWG1dispnc.o UserPktstbl.tmc UPdisp.cc
OBJ+=UPdispoui.c UPdispoui.o UPdisp.o UserPktstblnc.tmc UPdispnc.cc
OBJ+=UPdispncoui.c UPdispncoui.o UPdispnc.o ToFtbl.tmc ToFdisp.cc
OBJ+=ToFdispoui.c ToFdispoui.o ToFdisp.o ToFtblnc.tmc ToFdispnc.cc
OBJ+=ToFdispncoui.c ToFdispncoui.o ToFdispnc.o UserPktsdisp.cc
OBJ+=UserPktsdispoui.c UserPktsdispoui.o UserPktsdisp.o
OBJ+=UserPktsdispnc.cc UserPktsdispncoui.c UserPktsdispncoui.o
OBJ+=UserPktsdispnc.o UserPktsextcdf.oui UserPkts2cdf.tmc
OBJ+=UserPktsext.cc UserPktsextoui.c UserPktsextoui.o UserPktsext.o
OBJ+=ToFBtbl.tmc ToFBdisp.cc ToFBdispoui.c ToFBdispoui.o ToFBdisp.o
OBJ+=ToFBtblnc.tmc ToFBdispnc.cc ToFBdispncoui.c ToFBdispncoui.o
OBJ+=ToFBdispnc.o ToFextcdf.oui ToFcdf.tmc ToFext.cc ToFextoui.c
OBJ+=ToFextoui.o ToFext.o ToFjsonextcdf.oui ToFajsoncdf.tmc
OBJ+=ToFjsonext.cc ToFjsonextoui.c ToFjsonextoui.o ToFjsonext.o
OBJ+=ToFsws.tma ToFalgoa.tmc ToFalgo.cc ToFalgooui.c ToFalgooui.o
OBJ+=ToFalgo.o doit.dep ToFcmd.cc ToFcmd.dat ToFclt.o ToFcltoui.c
OBJ+=ToFcltoui.o ToFcltnc.o ToFcltncoui.c ToFcltncoui.o ToFsrvr.o
OBJ+=ToFsrvroui.c ToFsrvroui.o ToFcol.cc ToF.pcm tm.dac ToFcoloui.c
OBJ+=ToFcoloui.o ToFcol.o dsdaq.o ToFengext.cdf ToFengextcdf.oui
OBJ+=ToFengextcdf.tmc ToFengext.cc ToFengextoui.c ToFengextoui.o
OBJ+=ToFengext.o
TGT=IWG1disp IWG1dispnc UPdisp UPdispnc ToFdisp ToFdispnc
TGT+=UserPktsdisp UserPktsdispnc UserPktsext ToFBdisp ToFBdispnc
TGT+=ToFext ToFjsonext ToFalgo doit ToFclt ToFcltnc ToFsrvr ToFcol
TGT+=ToFengext
DISTRIB=../Horiba/TM/../horiba ../IonGauge/TM/../IonGauge
DISTRIB+=../Edwards_nXDS/TM/../nXDS ../UPS/TM/../ups
DISTRIB+=../GPS/TM/../gpsd_client ../IWG1/TM/../IWG1
DISTRIB+=../IWG1/TM/../UserPkts2 UserPktsdisp UserPktsext
DISTRIB+=../Zaber/TM/../zaber ../DSDaq/AthenaII ../DSDaq/Hercules
DISTRIB+=ToF.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit
SRCDIST=IWG1.tbl UserPkts.tbl ToF.tbl ToFB.tbl ToF.tma Inlet.tma
SRCDIST+=turbo.tma gasdeck.tma types.tmc AthenaII.tmc Hercules.tmc
SRCDIST+=tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc
SRCDIST+=/usr/local/share/huarp/tmdf.tmc
SRCDIST+=/usr/local/share/huarp/flttime.tmc SWData.tmc SWData.h
SRCDIST+=../Horiba/TM/Horiba.tmc IonGauge.tmc
SRCDIST+=../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc
SRCDIST+=../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc
SRCDIST+=../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc
TMCBASE=types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc
TMCBASE+=/usr/local/share/huarp/cpu_usage.tmc
TMCBASE+=/usr/local/share/huarp/tmdf.tmc
TMCBASE+=/usr/local/share/huarp/flttime.tmc SWData.tmc SWData.h
TMCBASE+=../Horiba/TM/Horiba.tmc IonGauge.tmc
TMCBASE+=../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc
TMCBASE+=../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc
TMCBASE+=../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc
CMDBASE=/usr/local/share/huarp/root.cmd
CMDBASE+=/usr/local/share/huarp/getcon.cmd AthenaII.cmd Hercules.cmd
CMDBASE+=SWlogs.cmd address.h SWData.cmd SWData.h
CMDBASE+=../Horiba/TM/Horiba.cmd ../Edwards_nXDS/TM/nXDS.cmd
CMDBASE+=/usr/local/share/huarp/OMS.cmd omsaxis.cmd ../UPS/TM/UPS.cmd
CMDBASE+=../Zaber/TM/zaber.cmd
COLBASE=AthenaII_col.tmc Hercules_col.tmc tdrift_col.tmc
COLBASE+=/usr/local/share/huarp/cpu_usage_col.tmc
COLBASE+=/usr/local/share/huarp/tmdf_col.tmc ../DSDaq/dsdaq.cc
COLBASE+=SWData_col.tmc ../Horiba/TM/Horiba_col.tmc
COLBASE+=../IonGauge/TM/IonGauge_col.tmc
COLBASE+=../Edwards_nXDS/TM/nXDS_col.tmc
COLBASE+=/usr/local/share/huarp/OMS_col.tmc ../UPS/TM/UPS_col.tmc
COLBASE+=../GPS/TM/gpsd_col.tmc ../IWG1/TM/IWG1_col.tmc
COLBASE+=../IWG1/TM/UserPkts2_col.tmc
SWSBASE=ToF.sws
QCLIBASE=
AG_CPPFLAGS=-I ../Horiba/TM/.. -I ../IonGauge/TM/.. -I
AG_CPPFLAGS+=../Edwards_nXDS/TM/.. -I ../UPS/TM/.. -I ../GPS/TM/.. -I
AG_CPPFLAGS+=../IWG1/TM/.. -I ../Zaber/TM/..
PHTGT=IWG1tbl.tmc UserPktstbl.tmc ToFtbl.tmc ToFBtbl.tmc
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/tof
include /usr/local/share/huarp/appgen.mk

.PHONY : all all-dist extdistribution distribution clean clean-dist check_photon

IGNOREFILE=.gitignore
all : Makefile check_photon $(TGT) $(IGNOREFILE)
all-dist : $(DSTRB) $(SRCDIST) VERSION
Makefile : ToF.spec
	appgen ToF.spec
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
UPdisp : UPdisp.o UPdispoui.o
	$(LINK.normCXX) UPdisp.o UPdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) UPdispoui.c
UPdispnc : UPdispnc.o UPdispncoui.o
	$(LINK.normCXX) UPdispnc.o UPdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) UPdispncoui.c
ToFdisp : ToFdisp.o ToFdispoui.o
	$(LINK.normCXX) ToFdisp.o ToFdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) ToFdispoui.c
ToFdispnc : ToFdispnc.o ToFdispncoui.o
	$(LINK.normCXX) ToFdispnc.o ToFdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) ToFdispncoui.c
UserPktsdisp : UserPktsdisp.o UserPktsdispoui.o
	$(LINK.normCXX) UserPktsdisp.o UserPktsdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) UserPktsdispoui.c
UserPktsdispnc : UserPktsdispnc.o UserPktsdispncoui.o
	$(LINK.normCXX) UserPktsdispnc.o UserPktsdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) UserPktsdispncoui.c
UserPktsext : UserPktsext.o UserPktsextoui.o
	$(LINK.normCXX) UserPktsext.o UserPktsextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) UserPktsextoui.c
ToFBdisp : ToFBdisp.o ToFBdispoui.o
	$(LINK.normCXX) ToFBdisp.o ToFBdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) ToFBdispoui.c
ToFBdispnc : ToFBdispnc.o ToFBdispncoui.o
	$(LINK.normCXX) ToFBdispnc.o ToFBdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) ToFBdispncoui.c
ToFext : ToFext.o ToFextoui.o
	$(LINK.normCXX) ToFext.o ToFextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) ToFextoui.c
ToFjsonext : ToFjsonext.o ToFjsonextoui.o
	$(LINK.normCXX) ToFjsonext.o ToFjsonextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) ToFjsonextoui.c
ToFalgo : ToFalgo.o ToFalgooui.o
	$(LINK.normCXX) ToFalgo.o ToFalgooui.o -ltmpp -ltm -lnort
	$(OUIUSE) ToFalgooui.c
doit : ToF.doit
	mkdoit3 -o doit  ToF.doit
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
ToFengext : ToFengext.o ToFengextoui.o
	$(LINK.normCXX) ToFengext.o ToFengextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) ToFengextoui.c
IWG1tbl.tmc : IWG1.tbl
IWG1disp.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc IWG1tbl.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc IWG1tbl.tmc
IWG1dispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
IWG1dispoui.o : IWG1dispoui.c SWData.h
IWG1disp.o : IWG1disp.cc SWData.h
IWG1tblnc.tmc : IWG1.tbl
IWG1dispnc.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc IWG1tblnc.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc IWG1tblnc.tmc
IWG1dispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
IWG1dispncoui.o : IWG1dispncoui.c SWData.h
IWG1dispnc.o : IWG1dispnc.cc SWData.h
UserPktstbl.tmc : UserPkts.tbl
UPdisp.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc UserPktstbl.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc UserPktstbl.tmc
UPdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
UPdispoui.o : UPdispoui.c SWData.h
UPdisp.o : UPdisp.cc SWData.h
UserPktstblnc.tmc : UserPkts.tbl
UPdispnc.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc UserPktstblnc.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc UserPktstblnc.tmc
UPdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
UPdispncoui.o : UPdispncoui.c SWData.h
UPdispnc.o : UPdispnc.cc SWData.h
ToFtbl.tmc : ToF.tbl
ToFdisp.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc AthenaII_conv.tmc Hercules_conv.tmc ../Horiba/TM/Horiba_conv.tmc ToFtbl.tmc IWG1tbl.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc AthenaII_conv.tmc Hercules_conv.tmc ../Horiba/TM/Horiba_conv.tmc ToFtbl.tmc IWG1tbl.tmc
ToFdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFdispoui.o : ToFdispoui.c SWData.h
ToFdisp.o : ToFdisp.cc SWData.h
ToFtblnc.tmc : ToF.tbl
ToFdispnc.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc AthenaII_conv.tmc Hercules_conv.tmc ../Horiba/TM/Horiba_conv.tmc ToFtblnc.tmc IWG1tblnc.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc AthenaII_conv.tmc Hercules_conv.tmc ../Horiba/TM/Horiba_conv.tmc ToFtblnc.tmc IWG1tblnc.tmc
ToFdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFdispncoui.o : ToFdispncoui.c SWData.h
ToFdispnc.o : ToFdispnc.cc SWData.h
UserPktsdisp.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc UserPktstbl.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc UserPktstbl.tmc
UserPktsdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
UserPktsdispoui.o : UserPktsdispoui.c SWData.h
UserPktsdisp.o : UserPktsdisp.cc SWData.h
UserPktsdispnc.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc UserPktstblnc.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc UserPktstblnc.tmc
UserPktsdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
UserPktsdispncoui.o : UserPktsdispncoui.c SWData.h
UserPktsdispnc.o : UserPktsdispnc.cc SWData.h
UserPktsextcdf.oui : ../IWG1/TM/UserPkts2.cdf
	$(EDF2OUI) ../IWG1/TM/UserPkts2.cdf
UserPkts2cdf.tmc : ../IWG1/TM/UserPkts2.cdf
	$(EDF2EXT) ../IWG1/TM/UserPkts2.cdf
UserPktsext.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc UserPkts2cdf.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc UserPkts2cdf.tmc
UserPktsextoui.c : UserPktsextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) UserPktsextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
UserPktsextoui.o : UserPktsextoui.c SWData.h
UserPktsext.o : UserPktsext.cc SWData.h
ToFBtbl.tmc : ToFB.tbl
ToFBdisp.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc ../Edwards_nXDS/TM/nXDS_conv.tmc ../GPS/TM/gpsd_conv.tmc ToFBtbl.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc ../Edwards_nXDS/TM/nXDS_conv.tmc ../GPS/TM/gpsd_conv.tmc ToFBtbl.tmc
ToFBdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFBdispoui.o : ToFBdispoui.c SWData.h
ToFBdisp.o : ToFBdisp.cc SWData.h
ToFBtblnc.tmc : ToFB.tbl
ToFBdispnc.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc ../Edwards_nXDS/TM/nXDS_conv.tmc ../GPS/TM/gpsd_conv.tmc ToFBtblnc.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc ../Edwards_nXDS/TM/nXDS_conv.tmc ../GPS/TM/gpsd_conv.tmc ToFBtblnc.tmc
ToFBdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFBdispncoui.o : ToFBdispncoui.c SWData.h
ToFBdispnc.o : ToFBdispnc.cc SWData.h
ToFextcdf.oui : ToF.cdf
	$(EDF2OUI) ToF.cdf
ToFcdf.tmc : ToF.cdf
	$(EDF2EXT) ToF.cdf
ToFext.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc ToFcdf.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc ToFcdf.tmc
ToFextoui.c : ToFextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) ToFextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFextoui.o : ToFextoui.c SWData.h
ToFext.o : ToFext.cc SWData.h
ToFjsonextcdf.oui : ToFajson.cdf
	$(EDF2OUI) ToFajson.cdf
ToFajsoncdf.tmc : ToFajson.cdf
	$(EDF2EXT) ToFajson.cdf
ToFjsonext.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc ToFajsoncdf.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc ToFajsoncdf.tmc
ToFjsonextoui.c : ToFjsonextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) ToFjsonextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFjsonextoui.o : ToFjsonextoui.c SWData.h
ToFjsonext.o : ToFjsonext.cc SWData.h
ToFsws.tma : ToF.sws
	$(COMPILE.sws) ToF.sws
ToFalgoa.tmc : ToF.tma ToFsws.tma Inlet.tma turbo.tma gasdeck.tma ToFsrvr
	$(SERVER) ./ToFsrvr
	$(TMCALGO) -V "`./ToFsrvr -R`" ToF.tma ToFsws.tma Inlet.tma turbo.tma gasdeck.tma
ToFalgo.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc tpfilt.tmc ToFalgoa.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc tpfilt.tmc ToFalgoa.tmc
ToFalgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFalgooui.o : ToFalgooui.c SWData.h
ToFalgo.o : ToFalgo.cc SWData.h
doit.dep : ToF.doit
	mkdoit3 -M -o doit  ToF.doit
-include doit.dep
ToFcmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd AthenaII.cmd Hercules.cmd SWlogs.cmd SWData.cmd ../Horiba/TM/Horiba.cmd ../Edwards_nXDS/TM/nXDS.cmd /usr/local/share/huarp/OMS.cmd omsaxis.cmd ../UPS/TM/UPS.cmd ../Zaber/TM/zaber.cmd
	$(CMDGEN) -d ToFcmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd AthenaII.cmd Hercules.cmd SWlogs.cmd SWData.cmd ../Horiba/TM/Horiba.cmd ../Edwards_nXDS/TM/nXDS.cmd /usr/local/share/huarp/OMS.cmd omsaxis.cmd ../UPS/TM/UPS.cmd ../Zaber/TM/zaber.cmd
ToFclt.o : ToFcmd.cc address.h SWData.h
	$(COMPILE.clt) ToFcmd.cc
ToFcltoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
ToFcltoui.o : ToFcltoui.c address.h SWData.h
ToFcltnc.o : ToFcmd.cc address.h SWData.h
	$(COMPILE.cltnc) ToFcmd.cc
ToFcltncoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
ToFcltncoui.o : ToFcltncoui.c address.h SWData.h
ToFsrvr.o : ToFcmd.cc address.h SWData.h
	$(COMPILE.srvr) ToFcmd.cc
ToFsrvroui.c : $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
ToFsrvroui.o : ToFsrvroui.c address.h SWData.h
ToFcol.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc AthenaII_col.tmc Hercules_col.tmc tdrift_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc SWData_col.tmc ../Horiba/TM/Horiba_col.tmc ../IonGauge/TM/IonGauge_col.tmc ../Edwards_nXDS/TM/nXDS_col.tmc /usr/local/share/huarp/OMS_col.tmc ../UPS/TM/UPS_col.tmc ../GPS/TM/gpsd_col.tmc ../IWG1/TM/IWG1_col.tmc ../IWG1/TM/UserPkts2_col.tmc
	$(TMC.col) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc AthenaII_col.tmc Hercules_col.tmc tdrift_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc SWData_col.tmc ../Horiba/TM/Horiba_col.tmc ../IonGauge/TM/IonGauge_col.tmc ../Edwards_nXDS/TM/nXDS_col.tmc /usr/local/share/huarp/OMS_col.tmc ../UPS/TM/UPS_col.tmc ../GPS/TM/gpsd_col.tmc ../IWG1/TM/IWG1_col.tmc ../IWG1/TM/UserPkts2_col.tmc
ToFcoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
ToFcoloui.o : ToFcoloui.c SWData.h
ToFcol.o : ToFcol.cc SWData.h
dsdaq.o : ../DSDaq/dsdaq.cc SWData.h
	$(COMPILE.cc) ../DSDaq/dsdaq.cc
ToFengext.cdf : ToF.genui ../Horiba/TM/Horiba.genui IonGauge.genui ../Edwards_nXDS/TM/nXDS.genui OMS.genui ../UPS/TM/UPS.genui ../GPS/TM/gpsd.genui ../IWG1/TM/IWG1.genui ../Zaber/TM/zaber.genui
	$(GENUI2ENG) ToF.genui ../Horiba/TM/Horiba.genui IonGauge.genui ../Edwards_nXDS/TM/nXDS.genui OMS.genui ../UPS/TM/UPS.genui ../GPS/TM/gpsd.genui ../IWG1/TM/IWG1.genui ../Zaber/TM/zaber.genui
ToFengextcdf.oui : ToFengext.cdf
	$(EDF2OUI) ToFengext.cdf
ToFengextcdf.tmc : ToFengext.cdf
	$(EDF2EXT) ToFengext.cdf
ToFengext.cc : types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc ../Horiba/TM/Horiba_conv.tmc ../Edwards_nXDS/TM/nXDS_conv.tmc ToFengextcdf.tmc
	$(TMC) types.tmc AthenaII.tmc Hercules.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc ../Horiba/TM/Horiba.tmc IonGauge.tmc ../Edwards_nXDS/TM/nXDS.tmc OMS.tmc UPS.tmc ../GPS/TM/gpsd.tmc ../IWG1/TM/IWG1.tmc ../IWG1/TM/UserPkts2.tmc ../Zaber/TM/zaber.tmc ../Horiba/TM/Horiba_conv.tmc ../Edwards_nXDS/TM/nXDS_conv.tmc ToFengextcdf.tmc
ToFengextoui.c : ToFengextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) ToFengextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFengextoui.o : ToFengextoui.c SWData.h
ToFengext.o : ToFengext.cc SWData.h
SWData.h SWData.tmc SWData_col.tmc SWData.cmd :  ToF.sws
	swscomp -o SWData  ToF.sws

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
clean-dist : clean
$(IGNOREFILE) : Makefile
	@for i in $(OBJECT) $(TARGET); do echo "$$i"; done >$(IGNOREFILE)
../Horiba/TM/../horiba :
	cd ../Horiba/TM/.. && make
.PHONY : clean-Horiba
clean-dist : clean-Horiba
clean-Horiba :
	cd ../Horiba/TM/.. && make clean
../IonGauge/TM/../IonGauge :
	cd ../IonGauge/TM/.. && make
.PHONY : clean-IonGauge
clean-dist : clean-IonGauge
clean-IonGauge :
	cd ../IonGauge/TM/.. && make clean
../Edwards_nXDS/TM/../nXDS :
	cd ../Edwards_nXDS/TM/.. && make
.PHONY : clean-nXDS
clean-dist : clean-nXDS
clean-nXDS :
	cd ../Edwards_nXDS/TM/.. && make clean
../UPS/TM/../ups :
	cd ../UPS/TM/.. && make
.PHONY : clean-UPS
clean-dist : clean-UPS
clean-UPS :
	cd ../UPS/TM/.. && make clean
../GPS/TM/../gpsd_client :
	cd ../GPS/TM/.. && make
.PHONY : clean-gpsd
clean-dist : clean-gpsd
clean-gpsd :
	cd ../GPS/TM/.. && make clean
../IWG1/TM/../UserPkts2 :
	cd ../IWG1/TM/.. && make UserPkts2
../IWG1/TM/../IWG1 :
	cd ../IWG1/TM/.. && make IWG1
.PHONY : clean-IWG1
clean-dist : clean-IWG1
clean-IWG1 :
	cd ../IWG1/TM/.. && make clean
../Zaber/TM/../zaber :
	cd ../Zaber/TM/.. && make
.PHONY : clean-zaber
clean-dist : clean-zaber
clean-zaber :
	cd ../Zaber/TM/.. && make clean
.PHONY : clean-sonic
clean-dist : clean-sonic
clean-sonic :
	cd ../Sonic/TM/.. && make clean
.PHONY : clean-Zeno
clean-dist : clean-Zeno
clean-Zeno :
	cd ../Zeno/TM/.. && make clean
ToFBbase=../Edwards_nXDS/TM/nXDS.tbl ../GPS/TM/gpsd.tbl ../UPS/TM/UPS.tbl ToFB.end.tbl
ToFB.tbl : $(ToFBbase)
	cat $(ToFBbase) >ToFB.tbl
COLFLAGS=-Haddress.h
CPPFLAGS += -I ../DSDaq
CXXFLAGS = -Wall -g
address.h : ToFcol.cc
../DSDaq/AthenaII ../DSDaq/Hercules :
	cd ../DSDaq && make
.PHONY : clean-ToF
clean-dist : clean-ToF
clean-ToF :
	cd ../IonGauge && make clean
	cd ../DSDaq && make clean
