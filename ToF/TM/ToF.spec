tmcbase = types.tmc
tmcbase = AthenaII.tmc
tmcbase = Hercules.tmc
tmcbase = tdrift.tmc
tmcbase = /usr/local/share/huarp/cpu_usage.tmc
tmcbase = /usr/local/share/huarp/tmdf.tmc
tmcbase = /usr/local/share/huarp/flttime.tmc

cmdbase = /usr/local/share/huarp/root.cmd
cmdbase = /usr/local/share/huarp/getcon.cmd
cmdbase = AthenaII.cmd Hercules.cmd
cmdbase = SWlogs.cmd
cmdbase = address.h

colbase = AthenaII_col.tmc
colbase = Hercules_col.tmc
colbase = tdrift_col.tmc
colbase = /usr/local/share/huarp/cpu_usage_col.tmc
colbase = /usr/local/share/huarp/tmdf_col.tmc
colbase = ../DSDaq/dsdaq.cc

swsbase = ToF.sws
genuibase = ToF.genui

Module Horiba mode=default
Module IonGauge mode=default
Module nXDS mode=default
Module OMS mode=Y OMS1=Insl Group=Inlet
Module UPS mode=default
Module gpsd mode=default
Module IWG1 mode=UserPkts
Module Zaber mode=default
Module Sonic mode=disable Hz=8
Module Zeno mode=disable

SCRIPT = interact runfile.AII runfile.AIIa
DISTRIB = ../DSDaq/AthenaII
DISTRIB = ../DSDaq/Hercules
TGTDIR = $(TGTNODE)/home/tof

OBJ = address.h

ToFdisp : AthenaII_conv.tmc Hercules_conv.tmc ../Horiba/TM/Horiba_conv.tmc \
  ToF.tbl IWG1.tbl
#ToFdisp : AthenaII_conv.tmc Hercules_conv.tmc ../Horiba/TM/Horiba_conv.tmc \
#  ToF.tbl  IWG1.tbl ../Sonic/TM/sonic.tbl
#ToFdisp : AthenaII_conv.tmc Hercules_conv.tmc ../Horiba/TM/Horiba_conv.tmc \
#   ToFz.tbl  ../Sonic/TM/sonic.tbl
UserPktsdisp : UserPkts.tbl
UserPktsext : ../IWG1/TM/UserPkts.cdf

ToFBdisp : ../Edwards_nXDS/TM/nXDS_conv.tmc ../GPS/TM/gpsd_conv.tmc ToFB.tbl

ToFext : ToF.cdf

#ToFjsonext : ToFjson.cdf
ToFjsonext : ToFajson.cdf
#ToFjsonext : ToFzjson.cdf

ToFalgo : tpfilt.tmc ToF.tma ToF.sws Inlet.tma turbo.tma gasdeck.tma
# Inlet.tma
doit : ToF.doit
#doit : ToFz.doit
%%
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
