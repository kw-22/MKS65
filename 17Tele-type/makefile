all: tele.o phoneline.o
	gcc -o tele tele.o
	gcc -o phoneline phoneline.o

tele.o: tele.c
	gcc -c tele.c

phoneline.o: phoneline.c
	gcc -c phoneline.c

clean:
	rm *.o
	rm ./tele ./phoneline
