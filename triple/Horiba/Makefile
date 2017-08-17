LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L /usr/local/lib
CPPFLAGS= -I /usr/local/include
CXXFLAGS= -Wall -g
LIBS=-ltmpp -ltm -lnort

SRC = horiba.cc horibaoui.c
OBJ = ${addsuffix .o, ${basename $(SRC) } } 
TGT = horiba

$(TGT) : $(OBJ)
	$(LINK.cc) -o $(TGT) $(OBJ) $(LIBS)
	usemsg $(TGT) horibaoui.c
horibaoui.c : horiba.oui
	oui -o horibaoui.c horiba.oui
.PHONY : clean
clean :
	rm -f *.o horibaoui.c horiba
