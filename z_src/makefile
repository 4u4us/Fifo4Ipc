
#all:
#	g++ -fPIC -shared -o libmyIOFunctions.so myIOFunctions.c util.c -ldl -lpthread
#	g++ -L. -Wl,-rpath=. -Wall -g -o testIOEGX testIOMain.cpp
#	g++ -L. -Wl,-rpath=. -Wall -g -o testclient testclient.cpp

IDIR =../z_include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=z_obj
LDIR =../lib

LIBS_PSA=-lm
LIBS_ASA=-lm

_DEPS = platform_side_adapter.h app_side_adapter.h fifo_ipc_msg.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ_PSA = platform_side_adapter.o fifo_ipc_msg.o
OBJ_PSA = $(patsubst %,$(ODIR)/%,$(_OBJ_PSA))

_OBJ_ASA = app_side_adapter.o fifo_ipc_msg.o
OBJ_ASA = $(patsubst %,$(ODIR)/%,$(_OBJ_ASA))

all: app-side-adapter platform-side-adapter

app-side-adapter: $(OBJ_ASA)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS_ASA)

platform-side-adapter: $(OBJ_PSA)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS_PSA)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
