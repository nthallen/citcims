LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L /usr/local/lib
CPPFLAGS= -I /usr/local/include
CXXFLAGS= -Wall -g
LIBS=-ltmpp -ltm -lnort

SRC = zaber.cc zaberoui.c
OBJ = ${addsuffix .o, ${basename $(SRC) } } 
TGT = zaber

$(TGT) : $(OBJ)
	$(LINK.cc) -o $(TGT) $(OBJ) $(LIBS)
	usemsg $(TGT) zaberoui.c
zaberoui.c : zaber.oui
	oui -o zaberoui.c zaber.oui
.PHONY : clean
clean :
	rm -f *.o zaberoui.c zaber
