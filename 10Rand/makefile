all: main.o
	gcc -o rand main.o

main.o: main.c
	gcc -c main.c

run:
	./rand

clean:
	rm *.o
	rm ./rand
	rm out.txt
