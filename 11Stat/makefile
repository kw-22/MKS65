all: main.o
	gcc -o info main.o

main.o: main.c
	gcc -c main.c

run:
	./info

clean:
	rm *.o
	rm info
