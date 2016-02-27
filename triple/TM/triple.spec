tmcbase = base.tmc
tmcbase = zaber.tmc
tmcbase = herc.tmc
tmcbase = IWG1.tmc
tmcbase = tdrift.tmc
tmcbase = modbus.tmc
tmcbase = /usr/local/share/huarp/cpu_usage.tmc
tmcbase = /usr/local/share/huarp/tmdf.tmc
tmcbase = /usr/local/share/huarp/flttime.tmc

cmdbase = /usr/local/share/huarp/root.cmd
cmdbase = /usr/local/share/huarp/getcon.cmd
cmdbase = zaber.cmd
cmdbase = herc.cmd
cmdbase = modbus.cmd
cmdbase = SWStat.cmd
# specq.cmd

colbase = IWG1_col.tmc
colbase = Hercules_col.tmc
colbase = /usr/local/share/huarp/cpu_usage_col.tmc
colbase = /usr/local/share/huarp/tmdf_col.tmc
colbase = ../DSDaq/dsdaq.cc
colbase = SWData_col.tmc
colbase = tdrift_col.tmc
colbase = modbus_col.tmc

TGTDIR = $(TGTNODE)/home/triple

DISTRIB = ../Zaber/zaber ../IWG1/IWG1
DISTRIB = ../DSDaq/Hercules
DISTRIB = ../Modbus/modbus
#DISTRIB = triplelander
#DISTRIB = ../specq/specq
#IDISTRIB = sendcmd
SCRIPT = interact Experiment.config

triplealgo : dstat_conv.tmc triple.tma hrdwr.tma
tripledisp : dstat_conv.tmc triple.tbl triple2.tbl IWG1.tbl
tripledoit : triple.doit
fastext : fast.cdf
mediumext : medium.cdf
tripleengext : tripleeng.cdf
triplejsonext : triplejson.cdf
# triplelander : triplelander.c triplelander.oui
%%
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
