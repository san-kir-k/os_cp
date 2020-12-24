GCC = gcc
GPP = g++
GCCFLAGS = -std=c99
GPPFLAGS = -std=c++17
ENGDIR = ../src/engine
CLIENTDIR = ../src/client
GUIDIR = ../src/gui
CLIENT_NAME = client

all: game_engine.o engine_wrapper.o connection_handle.o client.o gui.o
	$(GPP) $(GPPFLAGS) game_engine.o engine_wrapper.o connection_handle.o client.o gui.o -o $(CLIENT_NAME) -lzmq -lncurses

gui.o: $(GUIDIR)/gui.c
	$(GCC) $(GCCFLAGS) -c $(GUIDIR)/gui.c -o gui.o

client.o: $(CLIENTDIR)/client.c
	$(GCC) $(GCCFLAGS) -c $(CLIENTDIR)/client.c -o client.o

connection_handle.o: $(CLIENTDIR)/connection_handle.c $(CLIENTDIR)/connection_handle.h
	$(GCC) $(GCCFLAGS) -c $(CLIENTDIR)/connection_handle.c -o connection_handle.o

engine_wrapper.o: $(ENGDIR)/engine_wrapper.cpp $(ENGDIR)/engine_wrapper.hpp
	$(GPP) $(GPPFLAGS) -c $(ENGDIR)/engine_wrapper.cpp -o engine_wrapper.o

game_engine.o: $(ENGDIR)/game_engine.cpp $(ENGDIR)/game_engine.hpp
	$(GPP) $(GPPFLAGS) -c $(ENGDIR)/game_engine.cpp -o game_engine.o

clean:
	rm *.o $(CLIENT_NAME)