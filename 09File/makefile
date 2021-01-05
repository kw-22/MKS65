all: main.o
	gcc -o go main.o

main.o: main.c
	gcc -c main.c

run:
	@echo "The input file is:"
	@cat hi.txt
	@echo
	./go
	@echo
	@echo "The output file is:"
	@cat bye.txt

clean:
	rm *.o
	rm ./go
