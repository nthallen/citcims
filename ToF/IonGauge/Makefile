LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L /usr/local/lib
CPPFLAGS= -I /usr/local/include
CXXFLAGS= -Wall -g
LIBS=-ltmpp -ltm -lnort

SRC = IonGauge.cc IonGaugeoui.c
OBJ = ${addsuffix .o, ${basename $(SRC) } } 
TGT = IonGauge

$(TGT) : $(OBJ)
	$(LINK.cc) -o $(TGT) $(OBJ) $(LIBS)
	usemsg $(TGT) IonGaugeoui.c
IonGaugeoui.c : IonGauge.oui
	oui -o IonGaugeoui.c IonGauge.oui
.PHONY : clean
clean :
	rm -f *.o IonGaugeoui.c IonGauge
