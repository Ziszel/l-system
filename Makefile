# Define vars
IDIR=include/
CC=g++
PROG=fractals
CFLAGS=-g -W -Wall -Wextra -pedantic -std=c++17 -lpthread -Llib -lSDL2 -lSDL2main

turtle.o:
	$(CC) $(CFLAGS) -c src/turtle.cpp

rule.o:
	$(CC) $(CFLAGS) -c src/rule.cpp

l-system.o: turtle.o rule.o
	$(CC) $(CFLAGS) -c src/l-system.cpp

sdl-app.o:
	$(CC) $(CFLAGS) -c src/sdl-app.cpp

main.o: sdl-app.o turtle.o l-system.o
	$(CC) $(CFLAGS) -c src/main.cpp

.PHONY: all
all: main.o
	$(CC) -o $(PROG) main.o sdl-app.o turtle.o l-system.o rule.o $(CFLAGS) -I$(IDIR)

.PHONY: clean
clean:
	rm $(PROG) *.o
