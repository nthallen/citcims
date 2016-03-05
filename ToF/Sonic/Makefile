SONICOBJ=sonic.o sonicoui.o
OBJECT=$(SONICOBJ) sonicoui.c
CXXFLAGS=-Wall -g
CFLAGS=-Wall -g

TARGET=sonic

all : $(TARGET)

sonic : $(SONICOBJ)
	$(LINK.normCXX) $(SONICOBJ) -ltmpp -ltm -lnort
	usemsg sonic sonicoui.c
sonicoui.c : sonic.oui
	oui -o sonicoui.c sonic.oui

clean :
	rm -f $(OBJECT) $(TARGET)

include /usr/local/share/huarp/appgen.mk
