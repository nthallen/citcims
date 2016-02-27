LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L /usr/local/lib
CPPFLAGS= -I /usr/local/include
CXXFLAGS= -Wall -g
LIBS=-lsocket -ltmpp -ltm -lnort

SRC = IWG1.cc IWG1oui.c
OBJ = ${addsuffix .o, ${basename $(SRC) } } 
TGT = IWG1

$(TGT) : $(OBJ)
	$(LINK.cc) -o $(TGT) $(OBJ) $(LIBS)
	usemsg $(TGT) IWG1oui.c
IWG1oui.c : IWG1.oui
	oui -o IWG1oui.c IWG1.oui
.PHONY : clean
clean :
	rm -f *.o IWG1oui.c IWG1
