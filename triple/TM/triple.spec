tmcbase = base.tmc
tmcbase = herc.tmc
tmcbase = tdrift.tmc
tmcbase = /usr/local/share/huarp/cpu_usage.tmc
tmcbase = /usr/local/share/huarp/tmdf.tmc
tmcbase = /usr/local/share/huarp/flttime.tmc

cmdbase = /usr/local/share/huarp/root.cmd
cmdbase = /usr/local/share/huarp/getcon.cmd
cmdbase = herc.cmd
cmdbase = SWStat.cmd
# specq.cmd

colbase = Hercules_col.tmc
colbase = /usr/local/share/huarp/cpu_usage_col.tmc
colbase = /usr/local/share/huarp/tmdf_col.tmc
colbase = ../DSDaq/dsdaq.cc
colbase = SWData_col.tmc
colbase = tdrift_col.tmc

genuibase = triple.genui

TGTDIR = $(TGTNODE)/home/triple

DISTRIB = ../DSDaq/Hercules
#DISTRIB = triplelander
#DISTRIB = ../specq/specq
#IDISTRIB = sendcmd
SCRIPT = interact Experiment.config

Module IWG1 mode=default
Module modbus mode=disable
Module Zaber mode=dual
Module Horiba mode=driver src=Horiba.txt
Module ../../ToF/Edwards_nXDS/TM/nXDS mode=remote
Module ../../ToF/UPS/TM/UPS mode=remote

triplealgo : dstat_conv.tmc triple.tma hrdwr.tma
tripledisp : dstat_conv.tmc ../../ToF/Edwards_nXDS/TM/nXDS_conv.tmc \
  Horiba_conv.tmc \
  triple.tbl triple2.tbl IWG1.tbl UPSwin.tbl
tripledoit : triple.doit
fastext : fast.cdf
mediumext : medium.cdf
triplejsonext : triplejson.cdf
# triplelander : triplelander.c triplelander.oui

IGNORE = Makefile
IGNORE = SWStat_backup.cmd
IGNORE = SWStat_new.cmd
IGNORE = files.tar
IGNORE = herc_new.cmd
IGNORE = herc_old.cmd
IGNORE = herc_old.tmc
IGNORE = hrdwr_160402_old.tma
IGNORE = hrdwr_160804.tma
IGNORE = hrdwr_170119.tma
IGNORE = hrdwr_SEAC.tma
IGNORE = triple_160402_old.tma
IGNORE = triple_BEFOREAUTOCALCHANGES_160501.tma
IGNORE = triple_SEAC.tma
IGNORE = triple_new.tma
%%
COLFLAGS='-Haddress.h'
CPPFLAGS+= -I ../DSDaq
CXXFLAGS=-Wall -g

../DSDaq/Hercules :
	( cd ../DSDaq; make )
address.h : triplecol.cc
