#include "headers.h"
#include "pipe_networking.h"

/*=========================
  server_handshake
args: int * to_client

Performs the client side pipe 3 way handshake.
Sets *to_client to the file descriptor to the downstream pipe.

returns the file descriptor for the upstream pipe.
=========================*/
int server_handshake(int *to_client)
{
	int f;
	while(1) {
		printf("server create fifo, wait for connection\n");
		mkfifo("serverR", 0644);
		int fd1 = open("serverR", O_RDONLY);
		printf("server receives the clients message\n");
		char smessage[200];
		if(read(fd1, smessage, 200)) {
			printf("message: %s\n", smessage);
			printf("fork\n");
			f = fork();
		}
		if (f) {
			printf("server removes well known pipe\n");
			remove("serverR");
		} else {
			printf("server connects to client fifo, sending and initial acknowledgement message \n");
			*to_client = open("clientR", O_WRONLY);
			write(*to_client, "hello", 6);

			char smessagedos[200];
			read(fd1, smessagedos, 200);
			printf("client response: %s\n", smessagedos);

			return fd1;
		}
	}
}

/*=========================
  client_handshake
args: int * to_server

Performs the client side pipe 3 way handshake.
Sets *to_server to the file descriptor for the upstream pipe.

returns the file descriptor for the downstream pipe.
=========================*/
int client_handshake(int *to_server)
{
	printf("client create fifo\n");
	mkfifo("clientR", 0644);
	printf("client connect to serve and send fifo name, \n client waits for a response from the server\n");
	*to_server = open("serverR", O_WRONLY);
	write(*to_server, "clientR", 7);

	int fd2 = open("clientR", O_RDONLY);
	printf("client receives servers message\n");
	char cmessage[200];
	read(fd2, cmessage, 200);
	printf("message: %s\n", cmessage);
	printf("client removes its fifi\n");
	remove("clientR");

	printf("client sends response to server\n");
	write(*to_server, "response", 7);

	return fd2;
}
