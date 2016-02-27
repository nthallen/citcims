LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L /usr/local/lib
CPPFLAGS= -I /usr/local/include
CXXFLAGS= -Wall -g
LIBS=-ltmpp -ltm -lnort

SRC = modbus.cc crc.cc modbusoui.c
OBJ = ${addsuffix .o, ${basename $(SRC) } } 
TGT = modbus

$(TGT) : $(OBJ)
	$(LINK.cc) -o $(TGT) $(OBJ) $(LIBS)
	usemsg $(TGT) modbusoui.c
modbusoui.c : modbus.oui
	oui -o modbusoui.c modbus.oui
.PHONY : clean
clean :
	rm -f *.o modbusoui.c modbus

test_crc : test_crc.o crc.o
	$(LINK.cc) -o test_crc test_crc.o crc.o
