LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L /usr/local/lib
CPPFLAGS= -I /usr/local/include
CXXFLAGS= -Wall -g
LIBS=-ltm -lnort
.PHONY : clean all

all : Hercules

HOBJ=Hercules.o Herculesoui.o dsdaqdrv.o io_ascii_drv.o
Hercules : $(HOBJ)
	$(LINK.cc) -o Hercules $(HOBJ) $(LIBS)
	usemsg Hercules Herculesoui.c
	/usr/local/sbin/promote Hercules
Herculesoui.c : Hercules.oui
	oui -o Herculesoui.c Hercules.oui

clean :
	rm -f *.o Hercules Herculesoui.c
