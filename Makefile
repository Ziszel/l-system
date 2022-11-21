# Define vars
IDIR=include/
CC=g++
PROG=l-system-viewer
CFLAGS=-g -W -Wall -Wextra -pedantic -std=c++17 -lpthread -Llib -lSDL2 -lSDL2main

data-manager.o: rule.o
	$(CC) $(CFLAGS) -c src/data-manager.cpp

turtle.o:
	$(CC) $(CFLAGS) -c src/turtle.cpp

rule.o:
	$(CC) $(CFLAGS) -c src/rule.cpp

l-system.o: turtle.o rule.o data-manager.o
	$(CC) $(CFLAGS) -c src/l-system.cpp

sdl-app.o:
	$(CC) $(CFLAGS) -c src/sdl-app.cpp

main.o: sdl-app.o turtle.o l-system.o data-manager.o
	$(CC) $(CFLAGS) -c src/main.cpp

.PHONY: all
all: main.o
	$(CC) -o $(PROG) main.o sdl-app.o turtle.o l-system.o rule.o data-manager.o $(CFLAGS) -I$(IDIR)

.PHONY: clean
clean:
	rm $(PROG) *.o
