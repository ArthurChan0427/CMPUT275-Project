# ------------------------------------------------------------------------------------
#    Name:  Ryan Jacques         / Arthur Chan
#    ID:    1523211              / 1425382
#    Email: rjacques@ualberta.ca / yungjen@ualberta.ca
#    CMPUT 275, Winter 2019
#
#    Final Project: Terminal Text Editor with Auto-Completion and Undo/Redo Features
# ------------------------------------------------------------------------------------

CC=g++
OBJS=kilo.o iCommand.o commandManager.o autoComplete.o
PROGRAM=kilo
LFLAGS=
CFLAGS=-c -Wall -Wextra -pedantic -std=c++11

all: $(PROGRAM)

kilo: $(OBJS)
	$(CC) $(OBJS) -o kilo $(LFLAGS)

kilo.o: kilo.cpp commandManager.h autoComplete.h iCommand.h
	$(CC) kilo.cpp -o kilo.o $(CFLAGS)

commandManager.o: commandManager.cpp commandManager.h iCommand.h
	$(CC) commandManager.cpp -o commandManager.o $(CFLAGS)

autoComplete.o: autoComplete.cpp autoComplete.h iCommand.h
	$(CC) autoComplete.cpp -o autoComplete.o $(CFLAGS)

iCommand.o: iCommand.cpp iCommand.h
	$(CC) iCommand.cpp -o iCommand.o $(CFLAGS)

clean:
	@rm -f $(OBJS)
	@rm -f $(PROGRAM)
