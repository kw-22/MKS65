all: main.o
	gcc -o rand main.o

main.o: main.c
	gcc -c main.c

run:
	./rand

clean:
	shred -u *.o
	shred -u ./rand
	shred -u out.txt
