all: main.o
	gcc -o sig main.o

main.o: main.c
	gcc -c main.c

run:
	./sig

clean:
	shred -u *.o
	shred -u ./sig
	shred -u log.txt
