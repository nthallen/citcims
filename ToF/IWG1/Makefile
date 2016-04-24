LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L /usr/local/lib
CPPFLAGS= -I /usr/local/include
CXXFLAGS= -Wall -g
LIBS=-lsocket -ltmpp -ltm -lnort

IWG1SRC = IWG1.cc IWG1oui.c
IWG1OBJ = ${addsuffix .o, ${basename $(IWG1SRC) } } 
IWG1TGT = IWG1

UserPktsSRC = UserPkts.cc UserPktsoui.c
UserPktsOBJ = ${addsuffix .o, ${basename $(UserPktsSRC) } } 
UserPktsTGT = UserPkts

UserPkts2SRC = UserPkts2.cc UserPkts2oui.c
UserPkts2OBJ = ${addsuffix .o, ${basename $(UserPkts2SRC) } }
UserPkts2TGT = UserPkts2

.PHONY : all clean

all : UserPkts IWG1 UserPkts2

$(IWG1TGT) : $(IWG1OBJ)
	$(LINK.cc) -o $(IWG1TGT) $(IWG1OBJ) $(LIBS)
	usemsg $(IWG1TGT) IWG1oui.c
IWG1oui.c : IWG1.oui
	oui -o IWG1oui.c IWG1.oui

$(UserPktsTGT) : $(UserPktsOBJ)
	$(LINK.cc) -o $(UserPktsTGT) $(UserPktsOBJ) $(LIBS)
	usemsg $(UserPktsTGT) UserPktsoui.c
UserPktsoui.c : UserPkts.oui
	oui -o UserPktsoui.c UserPkts.oui

$(UserPkts2TGT) : $(UserPkts2OBJ)
	$(LINK.cc) -o $(UserPkts2TGT) $(UserPkts2OBJ) $(LIBS)
	usemsg $(UserPkts2TGT) UserPkts2oui.c
UserPkts2oui.c : UserPkts2.oui
	oui -o UserPkts2oui.c UserPkts2.oui

clean :
	rm -f *.o IWG1oui.c IWG1 UserPktsoui.c UserPkts UserPkts2oui.c UserPkts2
