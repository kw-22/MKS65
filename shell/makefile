all: shell.o core.o launch.o
	gcc -o shell shell.o core.o launch.o

shell.o: shell.c core.h
	gcc -c shell.c

core.o: core.c core.h
	gcc -c core.c

launch.o: launch.c launch.h
	gcc -c launch.c

run:
	./shell

clean:
	rm *.o
	rm ./shell
	rm .sh_history
