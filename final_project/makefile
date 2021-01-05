all: client server display basic_server

client: client.o networking.o engine.o
	gcc -o client client.o networking.o engine.o -lm

server: server.o networking.o
	gcc -o server server.o networking.o

basic_server: basic_server.o pipe_networking.o
	gcc -o basic_server basic_server.o pipe_networking.o

display: display.o pipe_networking.o engine.o
	gcc -o display display.o pipe_networking.o engine.o -lm

client.o: client.c networking.h engine.h headers.h
	gcc -c client.c

server.o: server.c server.h networking.h display.h
	gcc -c server.c

basic_server.o: basic_server.c headers.h pipe_networking.h
	gcc -c basic_server.c

display.o: display.c display.h headers.h pipe_networking.h engine.h
	gcc -c display.c

networking.o: networking.c networking.h headers.h
	gcc -c networking.c

pipe_networking.o: pipe_networking.c pipe_networking.h headers.h
	gcc -c pipe_networking.c

engine.o: engine.c engine.h headers.h
	gcc -c engine.c

clean:
	rm *.o
	rm ./server
	rm ./client
	rm ./display
	rm ./basic_server
	rm results
