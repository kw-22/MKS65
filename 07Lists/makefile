all: main.o node.o
	gcc -o list main.o node.o

main.o: main.c node.h
	gcc -c main.c

node.o: node.c node.h
	gcc -c node.c

run:
	./list

clean:
	rm *.o
	rm ./list
