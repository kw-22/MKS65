all: main.o
	gcc -o sig main.o

main.o: main.c
	gcc -c main.c

run:
	./sig

clean:
	rm *.o
	rm ./sig
	rm log.txt
