LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L /usr/local/lib
CPPFLAGS= -I /usr/local/include
CXXFLAGS= -Wall -g
LIBS=-ltmpp -ltm -lnort

SRC = nXDS_main.cc nXDS.cc nXDS_cmd.cc CmdReq.cc nXDSoui.c nXDS_TM.cc
OBJ = ${addsuffix .o, ${basename $(SRC) } } 
TGT = nXDS

$(TGT) : $(OBJ)
	$(LINK.cc) -o $(TGT) $(OBJ) $(LIBS)
	usemsg $(TGT) nXDSoui.c
nXDSoui.c : nXDS.oui
	oui -o nXDSoui.c nXDS.oui
.PHONY : clean
clean :
	rm -f *.o nXDSoui.c nXDS
