LIBS = -L/usr/lib -lSDL
IDIR = -I. -I./src/
CC = g++ -O0

all:
	$(CC) -g -c src/map.cpp -o obj/map.o $(IDIR) $(LIBS)
	$(CC) -g -c src/player.cpp -o obj/player.o $(IDIR) $(LIBS)
	$(CC) -g -c src/image.cpp -o obj/image.o $(IDIR) $(LIBS)
	$(CC) -g -c src/mysdl.cpp -o obj/mysdl.o $(IDIR) $(LIBS)
	$(CC) -g src/main.cpp obj/mysdl.o obj/image.o obj/mob.o obj/map.o obj/player.o -o Game $(IDIR) $(LIBS)