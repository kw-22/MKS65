all: main.o
	gcc -o share main.o

main.o: main.c
	gcc -c main.c

run:
	./share

clean:
	shred -u *.o
	shred -u ./share
