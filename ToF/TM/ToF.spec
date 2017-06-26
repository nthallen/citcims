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
Module IonGauge mode=default Hz=1
Module nXDS mode=default
Module OMS mode=Y OMS1=Insl Group=Inlet
Module UPS mode=default
Module gpsd mode=default
Module IWG1 mode=UserPkts2
Module Zaber mode=default
Module Sonic mode=disable Hz=8
Module Zeno mode=disable
Module TwisTorr drives=AB

SCRIPT = interact runfile.AII runfile.AIIa
DISTRIB = ../DSDaq/AthenaII
DISTRIB = ../DSDaq/Hercules
TGTDIR = $(TGTNODE)/home/tof

OBJ = address.h

ToFdisp : AthenaII_conv.tmc Hercules_conv.tmc ../Horiba/TM/Horiba_conv.tmc \
  ToF.tbl
#ToFdisp : AthenaII_conv.tmc Hercules_conv.tmc ../Horiba/TM/Horiba_conv.tmc \
#  ToF.tbl  IWG1.tbl ../Sonic/TM/sonic.tbl
#ToFdisp : AthenaII_conv.tmc Hercules_conv.tmc ../Horiba/TM/Horiba_conv.tmc \
#   ToFz.tbl  ../Sonic/TM/sonic.tbl
IWG1disp : IWG1.tbl UserPkts.tbl
UserPktsext : UserPkts.genui

ToFBdisp : ../Edwards_nXDS/TM/nXDS_conv.tmc ../GPS/TM/gpsd_conv.tmc ToFB.tbl
TwisTorrdisp : TwisTorr_conv.tmc TwisTorr_Pumps.tbl

ToFext : ToF.cdf

#ToFjsonext : ToFjson.cdf
ToFjsonext : ToFajson.cdf
#ToFjsonext : ToFzjson.cdf

ToFalgo : tpfilt.tmc ToF.tma ToF.sws Inlet.tma turbo.tma gasdeck.tma
# Inlet.tma
doit : ToF.doit
#doit : ToFz.doit

IGNORE = Inlet16115.tma
IGNORE = Inlet_160513.tma
IGNORE = Inlet_160802_newambzflows.tma
IGNORE = Inlet_160804_noprescontr.tma
IGNORE = Inlet_170320.tma
IGNORE = Inlet_labnov2016.tma
IGNORE = Inlet_prescontr_160804.tma
IGNORE = gasdeck_160802_forhottertemp.tma
IGNORE = gasdeck_160804_noprescontr.tma
IGNORE = gasdeck_prescontr_160804.tma

%%
# ToFBbase= ../GPS/TM/gpsd.tbl ../UPS/TM/UPS.tbl ToFB.end.tbl
#ToFB.tbl : $(ToFBbase)
#	cat $(ToFBbase) >ToFB.tbl
COLFLAGS=-Haddress.h
CPPFLAGS += -I ../DSDaq
CXXFLAGS = -Wall -g
address.h : ToFcol.cc
../DSDaq/AthenaII ../DSDaq/Hercules :
	cd ../DSDaq && make
.PHONY : clean-ToF
clean-dist : clean-ToF
clean-ToF :
	cd ../DSDaq && make clean
