all: main.o sieve.o
	gcc -o sieve main.o sieve.o -lm
	# gcc -Wall -pg -o sieve main.o sieve.o -lm

main.o: main.c sieve.h
	gcc -c main.c

sieve.o: sieve.c sieve.h
	gcc -c sieve.c

run:
	./sieve $(args)

clean:
	rm *.o
	rm ./sieve

asm: main.c sieve.c sieve.h
	gcc -S -fverbose-asm -g -O2 main.c -o main.s
	gcc -S -fverbose-asm -g -O2 sieve.c -o sieve.s
