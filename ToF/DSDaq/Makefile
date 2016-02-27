LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L /usr/local/lib
CPPFLAGS= -I /usr/local/include
CXXFLAGS= -Wall -g
LIBS=-ltm -lnort
.PHONY : clean all

all : AthenaII Hercules


AOBJ=AthenaII.o AthenaIIoui.o dsdaqdrv.o io_ascii_drv.o
AthenaII : $(AOBJ)
	$(LINK.cc) -o AthenaII $(AOBJ) $(LIBS)
	usemsg AthenaII AthenaIIoui.c
	/usr/local/sbin/promote AthenaII
AthenaIIoui.c : AthenaII.oui
	oui -o AthenaIIoui.c AthenaII.oui

HOBJ=Hercules.o Herculesoui.o dsdaqdrv.o io_ascii_drv.o
Hercules : $(HOBJ)
	$(LINK.cc) -o Hercules $(HOBJ) $(LIBS)
	usemsg Hercules Herculesoui.c
	/usr/local/sbin/promote Hercules
Herculesoui.c : Hercules.oui
	oui -o Herculesoui.c Hercules.oui

clean :
	rm -f *.o dscoui.c dsdoui.c dsd dsc AthenaII AthenaIIoui.c Hercules Herculesoui.c

# dsd and dsc are test instances for validating the IPC mechanisms

OBJ=dsd.o dsdoui.o io_ascii_drv.o dsdaqdrv.o
dsd : $(OBJ)
	$(LINK.cc) -o dsd $(OBJ) $(LIBS)
dsdoui.c : dsd.oui
	oui -o dsdoui.c dsd.oui

DSCOBJ=dsc.o dsdaq.o dscoui.o
dsc : $(DSCOBJ)
	$(LINK.cc) -o dsc $(DSCOBJ) $(LIBS)
dscoui.c : dsc.oui
	oui -o dscoui.c dsc.oui
