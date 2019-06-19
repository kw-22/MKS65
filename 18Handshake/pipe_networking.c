#include "pipe_networking.h"


/*=========================
  server_handshake
args: int * to_client

Performs the client side pipe 3 way handshake.
Sets *to_client to the file descriptor to the downstream pipe.

returns the file descriptor for the upstream pipe.
=========================*/
int server_handshake(int *to_client) {
	//create well known pipe, open, and block
	if (mkfifo("wkp", 0600) == -1) {
		printf("[server] error creating WPK: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[server] WPK created!\n");
	int wkp = open("wkp", O_RDONLY);
	if (wkp == -1) {
		printf("[server] error opening WPK: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[server] WPK opened!\n");

	char client_stream[HANDSHAKE_BUFFER_SIZE]; //name of private fifo carrying data away
	//waiting for name of private FIFO
	read(wkp, client_stream, sizeof(client_stream));
	printf("[server] name of private FIFO received thru WPK: %s\n", client_stream);
	remove("wkp"); //receiving works, remove WPK

	*to_client = open(client_stream, O_WRONLY);
	if (*to_client == -1) {
		printf("[server] error opening private FIFO %s: %s\n", client_stream, strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[server] opened private FIFO %s!\n", client_stream);
	write(*to_client, ACK, sizeof(ACK));
	printf("[server] sending msg thru private FIFO %s: %s\n", client_stream, ACK);
	char buf[HANDSHAKE_BUFFER_SIZE];
	read(wkp, buf, sizeof(buf));
	printf("[server] received msg thru WPK: %s\n", buf);
	return wkp;
}


/*=========================
  client_handshake
args: int * to_server

Performs the client side pipe 3 way handshake.
Sets *to_server to the file descriptor for the upstream pipe.

returns the file descriptor for the downstream pipe.
=========================*/
int client_handshake(int *to_server) {
	//open WPK
	*to_server = open("wkp", O_WRONLY);
	if (*to_server == -1) {
		printf("[client] error opening WPK: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[client] WPK opened!\n");

	//create private FIFO
	char private[HANDSHAKE_BUFFER_SIZE];
	snprintf(private, sizeof(private), "%d", getpid());
	if (mkfifo(private, 0600) == -1) {
		printf("[client] error creating private FIFO: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[client] private FIFO created!\n");

	//send name of private FIFO
	write(*to_server, private, sizeof(private));
	printf("[client] name of FIFO sent!: %s\n", private);

	//open private FIFO
	int priv = open(private, O_RDONLY);
	if(priv == -1) {
		printf("[client] error opening private FIFO: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[client] private FIFO opened!\n");

	char server_stream[BUFFER_SIZE];
	read(priv, server_stream, sizeof(server_stream));
	printf("[client] received msg from server: %s\n", server_stream);
	write(*to_server, "hello", 6);
	printf("[client] sent msg thru WPK\n");
	remove(private); //receiving works, remove private FIFO

	return priv;
}
