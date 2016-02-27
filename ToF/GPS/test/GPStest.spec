tmcbase = GPStest.tmc
tmcbase = ../TM/gpsd.tmc
tmcbase = /usr/local/share/huarp/cpu_usage.tmc
tmcbase = /usr/local/share/huarp/flttime.tmc

cmdbase = /usr/local/share/huarp/root.cmd
cmdbase = /usr/local/share/huarp/getcon.cmd

colbase = /usr/local/share/huarp/cpu_usage_col.tmc
colbase = ../TM/gpsd_col.tmc

SCRIPT = interact
TGTDIR = $(TGTNODE)/home/GPStest
DISTRIB = ../gpsd_client
OBJ = GPStest.tbl

GPStestdisp : ../TM/gpsd_conv.tmc GPStest.tbl
GPStestext : GPStesteng.cdf
doit : GPStest.doit

%%
CPPFLAGS += -I ../
GENUISRCS = genui.txt
GENUISRCS += ../TM/gpsd.genui

GPStest.tbl : ../TM/gpsd.tbl GPStest_foot.tbl
	cat ../TM/gpsd.tbl GPStest_foot.tbl >GPStest.tbl

GPStesteng.cdf : $(GENUISRCS)
	genui -d eng -c $(GENUISRCS)

../gpsd_client :
	cd .. && make
