LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L /usr/local/lib
CPPFLAGS= -I /usr/local/include
CXXFLAGS= -Wall -g
LIBS=-ltmpp -ltm -lnort

SRC = Agilent.cc TwisTorr.cc TwisTorr_cmd.cc CmdReq.cc TwisTorroui.c
OBJ = ${addsuffix .o, ${basename $(SRC) } } 
TGT = TwisTorr

$(TGT) : $(OBJ)
	$(LINK.cc) -o $(TGT) $(OBJ) $(LIBS)
	usemsg $(TGT) TwisTorroui.c
TwisTorroui.c : TwisTorr.oui
	oui -o TwisTorroui.c TwisTorr.oui
.PHONY : clean
clean :
	rm -f *.o TwisTorroui.c TwisTorr
