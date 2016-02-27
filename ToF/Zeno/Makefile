LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L /usr/local/lib
CPPFLAGS= -I /usr/local/include
CFLAGS=-Wall -g
CXXFLAGS= -Wall -g

TGT = Zeno_Ser

SERSRC = Zeno_Ser.cc Zeno_Seroui.c
SEROBJ = ${addsuffix .o, ${basename $(SERSRC) } } 
SERLIBS=-ltmpp -ltm -lnort

all : $(TGT)
Zeno_Ser : $(SEROBJ)
	$(LINK.cc) -o Zeno_Ser $(SEROBJ) $(SERLIBS)
	usemsg Zeno_Ser Zeno_Seroui.c
Zeno_Seroui.c : Zeno_Ser.oui
	oui -o Zeno_Seroui.c Zeno_Ser.oui
.PHONY : clean all
clean :
	rm -f *.o Zeno_Seroui.c Zeno_Ser
