CC=g++
OBJS=kilo.o iCommand.o commandManager.o
PROGRAM=kilo
LFLAGS=
CFLAGS=-c -Wall -Wextra -pedantic -std=c++11

all: $(PROGRAM)

kilo: $(OBJS)
	$(CC) $(OBJS) -o kilo $(LFLAGS)

kilo.o: kilo.cpp commandManager.h iCommand.h
	$(CC) kilo.cpp -o kilo.o $(CFLAGS)

commandManager.o: commandManager.cpp commandManager.h iCommand.h
	$(CC) commandManager.cpp -o commandManager.o $(CFLAGS)

iCommand.o: iCommand.cpp iCommand.h
	$(CC) iCommand.cpp -o iCommand.o $(CFLAGS)

clean:
	@rm -f $(OBJS)
	@rm -f $(PROGRAM)
