all: main.o
	gcc -o fork main.o

main.o: main.c
	gcc -c main.c

run:
	./fork

clean:
	shred -u *.o
	shred -u ./fork
