all: main.o strh.o
	gcc -o my_string_lib main.o strh.o

strh.o: strh.c strh.h
	gcc -c strh.c

main.o: main.c strh.h
	gcc -c main.c

run:
	./my_string_lib

clean:
	rm *.o
	rm ./my_string_lib
