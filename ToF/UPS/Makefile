UPSOBJ=UPS_main.o UPS_ser.o UPS_cmd.o UPSCmdReq.o UPS_parsers.o \
  UPSoui.o UPS_TM.o
OBJECT=$(UPSOBJ) UPSoui.c
CXXFLAGS=-Wall -g
CFLAGS=-Wall -g

TARGET=ups

all : $(TARGET)

ups : $(UPSOBJ)
	$(LINK.normCXX) $(UPSOBJ) -ltmpp -ltm -lnort
	usemsg ups UPSoui.c
UPSoui.c : UPS.oui
	oui -o UPSoui.c UPS.oui

clean :
	rm -f $(OBJECT) $(TARGET)

include /usr/local/share/huarp/appgen.mk
