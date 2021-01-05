all: ls2.o
	gcc -o ls ls2.o -lm

ls2.o: ls2.c
	gcc -c ls2.c

run:
	./ls

clean:
	rm *.o
	rm ls
