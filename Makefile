CC=g++
OBJS=kilo.o
PROGRAM=kilo
LFLAGS=
CFLAGS=-c -Wall -Wextra -pedantic

all: $(PROGRAM)

kilo: kilo.o
	$(CC) kilo.o -o kilo $(LFLAGS)

kilo.o: kilo.cpp
	$(CC) kilo.cpp -o kilo.o $(CFLAGS)

clean:
	@rm -f $(OBJS)
	@rm -f $(PROGRAM)
