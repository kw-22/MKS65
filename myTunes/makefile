all: main.o linked_list.o library.o
	gcc -o tunes main.o linked_list.o library.o

main.o: main.c linked_list.h library.h
	gcc -c main.c

list.o: linked_list.c linked_list.h
	gcc -c linked_list.c

library.o: library.c library.h
	gcc -c library.c

run:
	./tunes

clean:
	rm ./tunes
	rm *.o
