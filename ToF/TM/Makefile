# Makefile Generated Sun Feb 28 14:46:26 EST 2016
MNC=ToF
SPECFILE=ToF.spec
PCMFILE=ToF.pcm
SRC=types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc
SRC+=zaber.tmc tdrift.tmc SWData.tmc SWData.h IWG1.tmc UserPkts.tmc
SRC+=UserPkts.tbl UserPkts.cdf AthenaII_conv.tmc Hercules_conv.tmc
SRC+=Horiba_conv.tmc ToF.tbl IWG1.tbl ToF.cdf ToFajson.cdf tpfilt.tmc
SRC+=ToF.tma ToF.sws Inlet.tma turbo.tma gasdeck.tma ToF.doit
SRC+=AthenaII.cmd Hercules.cmd oms.cmd Horiba.cmd zaber.cmd
SRC+=SWlogs.cmd address.h SWData.cmd AthenaII_col.tmc
SRC+=Hercules_col.tmc oms_col.tmc Horiba_col.tmc tdrift_col.tmc
SRC+=SWData_col.tmc IWG1_col.tmc UserPkts_col.tmc ToF.genui
SRC+=IWG1.genui
TOOL=ToF.spec Makefile
SCRIPT=interact runfile.AII runfile.AIIa
OBJ=address.h UserPktstbl.tmc UserPktsdisp.cc UserPktsdispoui.c
OBJ+=UserPktsdispoui.o UserPktsdisp.o UserPktstblnc.tmc
OBJ+=UserPktsdispnc.cc UserPktsdispncoui.c UserPktsdispncoui.o
OBJ+=UserPktsdispnc.o UserPktsextcdf.oui UserPktscdf.tmc
OBJ+=UserPktsext.cc UserPktsextoui.c UserPktsextoui.o UserPktsext.o
OBJ+=ToFtbl.tmc IWG1tbl.tmc ToFdisp.cc ToFdispoui.c ToFdispoui.o
OBJ+=ToFdisp.o ToFtblnc.tmc IWG1tblnc.tmc ToFdispnc.cc ToFdispncoui.c
OBJ+=ToFdispncoui.o ToFdispnc.o ToFextcdf.oui ToFcdf.tmc ToFext.cc
OBJ+=ToFextoui.c ToFextoui.o ToFext.o ToFjsonextcdf.oui
OBJ+=ToFajsoncdf.tmc ToFjsonext.cc ToFjsonextoui.c ToFjsonextoui.o
OBJ+=ToFjsonext.o ToFsws.tma ToFalgoa.tmc ToFalgo.cc ToFalgooui.c
OBJ+=ToFalgooui.o ToFalgo.o doit.dep ToFcmd.cc ToFcmd.dat ToFclt.o
OBJ+=ToFcltoui.c ToFcltoui.o ToFcltnc.o ToFcltncoui.c ToFcltncoui.o
OBJ+=ToFsrvr.o ToFsrvroui.c ToFsrvroui.o ToFcol.cc ToF.pcm tm.dac
OBJ+=ToFcoloui.c ToFcoloui.o ToFcol.o dsdaq.o ToFengext.cdf
OBJ+=ToFengextcdf.oui ToFengextcdf.tmc ToFengext.cc ToFengextoui.c
OBJ+=ToFengextoui.o ToFengext.o
TGT=UserPktsdisp UserPktsdispnc UserPktsext ToFdisp ToFdispnc ToFext
TGT+=ToFjsonext ToFalgo doit ToFclt ToFcltnc ToFsrvr ToFcol ToFengext
DISTRIB=../IWG1/IWG1 ../IWG1/UserPkts ../IonGauge/IonGauge
DISTRIB+=../DSDaq/AthenaII ../DSDaq/Hercules ../Horiba/horiba
DISTRIB+=../Zaber/zaber ToF.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit
SRCDIST=UserPkts.tbl ToF.tbl IWG1.tbl ToF.tma Inlet.tma turbo.tma
SRCDIST+=gasdeck.tma types.tmc IG.tmc AthenaII.tmc Hercules.tmc
SRCDIST+=oms.tmc Horiba.tmc zaber.tmc tdrift.tmc
SRCDIST+=/usr/local/share/huarp/cpu_usage.tmc
SRCDIST+=/usr/local/share/huarp/tmdf.tmc
SRCDIST+=/usr/local/share/huarp/flttime.tmc SWData.tmc SWData.h
SRCDIST+=IWG1.tmc UserPkts.tmc
TMCBASE=types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc
TMCBASE+=Horiba.tmc zaber.tmc tdrift.tmc
TMCBASE+=/usr/local/share/huarp/cpu_usage.tmc
TMCBASE+=/usr/local/share/huarp/tmdf.tmc
TMCBASE+=/usr/local/share/huarp/flttime.tmc SWData.tmc SWData.h
TMCBASE+=IWG1.tmc UserPkts.tmc
CMDBASE=/usr/local/share/huarp/root.cmd
CMDBASE+=/usr/local/share/huarp/getcon.cmd
CMDBASE+=/usr/local/share/huarp/OMS.cmd AthenaII.cmd Hercules.cmd
CMDBASE+=oms.cmd Horiba.cmd zaber.cmd SWlogs.cmd address.h SWData.cmd
CMDBASE+=SWData.h
COLBASE=AthenaII_col.tmc Hercules_col.tmc oms_col.tmc Horiba_col.tmc
COLBASE+=tdrift_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc
COLBASE+=/usr/local/share/huarp/tmdf_col.tmc ../DSDaq/dsdaq.cc
COLBASE+=SWData_col.tmc IWG1_col.tmc UserPkts_col.tmc
SWSBASE=ToF.sws
QCLIBASE=
AG_CPPFLAGS=-I ../IWG1
PHTGT=UserPktstbl.tmc ToFtbl.tmc IWG1tbl.tmc
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/tof
include /usr/local/share/huarp/appgen.mk

.PHONY : all all-dist extdistribution distribution clean check_photon

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
UserPktsdisp : UserPktsdisp.o UserPktsdispoui.o
	$(LINK.normCXX) UserPktsdisp.o UserPktsdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) UserPktsdispoui.c
UserPktsdispnc : UserPktsdispnc.o UserPktsdispncoui.o
	$(LINK.normCXX) UserPktsdispnc.o UserPktsdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) UserPktsdispncoui.c
UserPktsext : UserPktsext.o UserPktsextoui.o
	$(LINK.normCXX) UserPktsext.o UserPktsextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) UserPktsextoui.c
ToFdisp : ToFdisp.o ToFdispoui.o
	$(LINK.normCXX) ToFdisp.o ToFdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) ToFdispoui.c
ToFdispnc : ToFdispnc.o ToFdispncoui.o
	$(LINK.normCXX) ToFdispnc.o ToFdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) ToFdispncoui.c
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
UserPktstbl.tmc : UserPkts.tbl
UserPktsdisp.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc UserPktstbl.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc UserPktstbl.tmc
UserPktsdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
UserPktsdispoui.o : UserPktsdispoui.c SWData.h
UserPktsdisp.o : UserPktsdisp.cc SWData.h
UserPktstblnc.tmc : UserPkts.tbl
UserPktsdispnc.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc UserPktstblnc.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc UserPktstblnc.tmc
UserPktsdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
UserPktsdispncoui.o : UserPktsdispncoui.c SWData.h
UserPktsdispnc.o : UserPktsdispnc.cc SWData.h
UserPktsextcdf.oui : UserPkts.cdf
	$(EDF2OUI) UserPkts.cdf
UserPktscdf.tmc : UserPkts.cdf
	$(EDF2EXT) UserPkts.cdf
UserPktsext.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc UserPktscdf.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc UserPktscdf.tmc
UserPktsextoui.c : UserPktsextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) UserPktsextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
UserPktsextoui.o : UserPktsextoui.c SWData.h
UserPktsext.o : UserPktsext.cc SWData.h
ToFtbl.tmc : ToF.tbl
IWG1tbl.tmc : IWG1.tbl
ToFdisp.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc AthenaII_conv.tmc Hercules_conv.tmc Horiba_conv.tmc ToFtbl.tmc IWG1tbl.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc AthenaII_conv.tmc Hercules_conv.tmc Horiba_conv.tmc ToFtbl.tmc IWG1tbl.tmc
ToFdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFdispoui.o : ToFdispoui.c SWData.h
ToFdisp.o : ToFdisp.cc SWData.h
ToFtblnc.tmc : ToF.tbl
IWG1tblnc.tmc : IWG1.tbl
ToFdispnc.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc AthenaII_conv.tmc Hercules_conv.tmc Horiba_conv.tmc ToFtblnc.tmc IWG1tblnc.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc AthenaII_conv.tmc Hercules_conv.tmc Horiba_conv.tmc ToFtblnc.tmc IWG1tblnc.tmc
ToFdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFdispncoui.o : ToFdispncoui.c SWData.h
ToFdispnc.o : ToFdispnc.cc SWData.h
ToFextcdf.oui : ToF.cdf
	$(EDF2OUI) ToF.cdf
ToFcdf.tmc : ToF.cdf
	$(EDF2EXT) ToF.cdf
ToFext.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc ToFcdf.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc ToFcdf.tmc
ToFextoui.c : ToFextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) ToFextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFextoui.o : ToFextoui.c SWData.h
ToFext.o : ToFext.cc SWData.h
ToFjsonextcdf.oui : ToFajson.cdf
	$(EDF2OUI) ToFajson.cdf
ToFajsoncdf.tmc : ToFajson.cdf
	$(EDF2EXT) ToFajson.cdf
ToFjsonext.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc ToFajsoncdf.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc ToFajsoncdf.tmc
ToFjsonextoui.c : ToFjsonextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) ToFjsonextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFjsonextoui.o : ToFjsonextoui.c SWData.h
ToFjsonext.o : ToFjsonext.cc SWData.h
ToFsws.tma : ToF.sws
	$(COMPILE.sws) ToF.sws
ToFalgoa.tmc : ToF.tma ToFsws.tma Inlet.tma turbo.tma gasdeck.tma ToFsrvr
	$(SERVER) ./ToFsrvr
	$(TMCALGO) -V "`./ToFsrvr -R`" ToF.tma ToFsws.tma Inlet.tma turbo.tma gasdeck.tma
ToFalgo.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc tpfilt.tmc ToFalgoa.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc tpfilt.tmc ToFalgoa.tmc
ToFalgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ToFalgooui.o : ToFalgooui.c SWData.h
ToFalgo.o : ToFalgo.cc SWData.h
doit.dep : ToF.doit
	mkdoit3 -M -o doit  ToF.doit
-include doit.dep
ToFcmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd /usr/local/share/huarp/OMS.cmd AthenaII.cmd Hercules.cmd oms.cmd Horiba.cmd zaber.cmd SWlogs.cmd SWData.cmd
	$(CMDGEN) -d ToFcmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd /usr/local/share/huarp/OMS.cmd AthenaII.cmd Hercules.cmd oms.cmd Horiba.cmd zaber.cmd SWlogs.cmd SWData.cmd
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
ToFcol.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc AthenaII_col.tmc Hercules_col.tmc oms_col.tmc Horiba_col.tmc tdrift_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc SWData_col.tmc IWG1_col.tmc UserPkts_col.tmc
	$(TMC.col) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc AthenaII_col.tmc Hercules_col.tmc oms_col.tmc Horiba_col.tmc tdrift_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc SWData_col.tmc IWG1_col.tmc UserPkts_col.tmc
ToFcoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
ToFcoloui.o : ToFcoloui.c SWData.h
ToFcol.o : ToFcol.cc SWData.h
dsdaq.o : ../DSDaq/dsdaq.cc SWData.h
	$(COMPILE.cc) ../DSDaq/dsdaq.cc
ToFengext.cdf : ToF.genui IWG1.genui
	$(GENUI2CDF) ToF.genui IWG1.genui
ToFengextcdf.oui : ToFengext.cdf
	$(EDF2OUI) ToFengext.cdf
ToFengextcdf.tmc : ToFengext.cdf
	$(EDF2EXT) ToFengext.cdf
ToFengext.cc : types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc ToFengextcdf.tmc
	$(TMC) types.tmc IG.tmc AthenaII.tmc Hercules.tmc oms.tmc Horiba.tmc zaber.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc SWData.tmc IWG1.tmc UserPkts.tmc ToFengextcdf.tmc
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
$(IGNOREFILE) : Makefile
	@for i in $(OBJECT) $(TARGET); do echo "$$i"; done >$(IGNOREFILE)
COLFLAGS=-Haddress.h
CPPFLAGS += -I ../IonGauge -I ../DSDaq -I ../Horiba -I ../Zaber
CXXFLAGS = -Wall -g
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
../Sonic/sonic :
	cd ../Sonic && make
../Zeno/Zeno_Ser :
	cd ../Zeno && make Zeno_Ser
.PHONY : all-clean
all-clean : clean
	cd ../Zaber && make clean
	cd ../IonGauge && make clean
	cd ../DSDaq && make clean
	cd ../Horiba && make clean
	cd ../IWG1 && make clean
	cd ../Sonic && make clean
	cd ../Zeno && make clean
