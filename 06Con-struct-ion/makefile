all: main.o
	gcc -o struct_playing main.o

main.o: main.c
	gcc -c main.c

run:
	./struct_playing

clean:
	shred -u *.o
	shred -u ./struct_playing
