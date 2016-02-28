tmcbase = types.tmc
tmcbase = IG.tmc
tmcbase = AthenaII.tmc
tmcbase = Hercules.tmc
tmcbase = oms.tmc
tmcbase = Horiba.tmc
tmcbase = zaber.tmc
tmcbase = tdrift.tmc
tmcbase = /usr/local/share/huarp/cpu_usage.tmc
tmcbase = /usr/local/share/huarp/tmdf.tmc
tmcbase = /usr/local/share/huarp/flttime.tmc

cmdbase = /usr/local/share/huarp/root.cmd
cmdbase = /usr/local/share/huarp/getcon.cmd
cmdbase = /usr/local/share/huarp/OMS.cmd
cmdbase = AthenaII.cmd Hercules.cmd oms.cmd
cmdbase = Horiba.cmd
cmdbase = zaber.cmd
cmdbase = SWlogs.cmd
cmdbase = address.h

colbase = AthenaII_col.tmc
colbase = Hercules_col.tmc
colbase = oms_col.tmc
colbase = Horiba_col.tmc
colbase = tdrift_col.tmc
colbase = /usr/local/share/huarp/cpu_usage_col.tmc
colbase = /usr/local/share/huarp/tmdf_col.tmc
colbase = ../DSDaq/dsdaq.cc

swsbase = ToF.sws
genuibase = ToF.genui

tmcbase = IWG1.tmc
colbase = IWG1_col.tmc
tmcbase = UserPkts.tmc
colbase = UserPkts_col.tmc
genuibase = IWG1.genui
DISTRIB = ../IWG1/IWG1 ../IWG1/UserPkts
CPPFLAGS = -I ../IWG1
UserPktsdisp : UserPkts.tbl
UserPktsext : UserPkts.cdf

#tmcbase = ../Sonic/TM/sonic.tmc
#colbase = ../Sonic/TM/sonic_col.tmc
#genuibase = ../Sonic/TM/sonic.genui
#DISTRIB = ../Sonic/sonic
#CPPFLAGS = -I ../Sonic

#tmcbase = Zeno.tmc
#colbase = Zeno_col.tmc
#cmdbase = Zeno.cmd
#genuibase = ../Zeno/Zeno.genui
#CPPFLAGS = -I ../Zeno
#DISTRIB = ../Zeno/Zeno_Ser

SCRIPT = interact runfile.AII runfile.AIIa
DISTRIB = ../IonGauge/IonGauge ../DSDaq/AthenaII
DISTRIB = ../DSDaq/Hercules ../Horiba/horiba
DISTRIB = ../Zaber/zaber
TGTDIR = $(TGTNODE)/home/tof

OBJ = address.h

ToFdisp : AthenaII_conv.tmc Hercules_conv.tmc Horiba_conv.tmc ToF.tbl \
  IWG1.tbl
#ToFdisp : AthenaII_conv.tmc Hercules_conv.tmc Horiba_conv.tmc ToF.tbl \
#  IWG1.tbl ../Sonic/TM/sonic.tbl
#ToFdisp : AthenaII_conv.tmc Hercules_conv.tmc Horiba_conv.tmc ToFz.tbl \
#    ../Sonic/TM/sonic.tbl

ToFext : ToF.cdf

#ToFengext : ToFeng.cdf
#ToFjsonext : ToFjson.cdf
ToFjsonext : ToFajson.cdf
#ToFjsonext : ToFzjson.cdf

ToFalgo : tpfilt.tmc ToF.tma ToF.sws Inlet.tma turbo.tma gasdeck.tma
# Inlet.tma
doit : ToF.doit
#doit : ToFz.doit
%%
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
