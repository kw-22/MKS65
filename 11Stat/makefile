all: main.o
	gcc -o info main.o

main.o: main.c
	gcc -c main.c

run:
	./info

clean:
	shred -u *.o
	shred -u info
