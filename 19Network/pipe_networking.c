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
	//create well known pipe, open, and block
	if (mkfifo("wkp", 0644) == -1) {
		printf("[server] error creating WKP: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[server] WKP created!\n");
	int wkp = open("wkp", O_RDONLY);
	if (wkp == -1) {
		printf("[server] error opening WKP: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[server] WKP opened!\n");

	char client_stream[HANDSHAKE_BUFFER_SIZE]; //name of private fifo carrying data away
	//waiting for name of private FIFO
	if (read(wkp, client_stream, sizeof(client_stream)) == -1) {
		printf("[server] error getting name of private FIFO thru WKP: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[server] name of private FIFO received thru WKP: %s\n", client_stream);

	*to_client = open(client_stream, O_WRONLY);
	if (*to_client == -1) {
		printf("[server] error opening private FIFO %s: %s\n", client_stream, strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[server] opened private FIFO %s!\n", client_stream);
	if (write(*to_client, ACK, sizeof(ACK)) == -1) {
		printf("[server] error sending msg thru private FIFO %s\n", client_stream);
		exit(EXIT_FAILURE);
	} else
		printf("[server] sent msg thru private FIFO %s\n", client_stream);
	if (read(wkp, client_stream, sizeof(client_stream)) == -1) {
		printf("[server] error completing handshake: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[server] handshake completed! Msg from client: %s\n", client_stream);

	//receiving works, remove WKP
	if (remove("wkp") == -1) {
		printf("[server] error removing WKP: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[server] WKP removed!\n");

	return wkp;
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
	//create private FIFO
	char priv[HANDSHAKE_BUFFER_SIZE];
	snprintf(priv, sizeof(priv), "%d", getpid()); //name of private FIFO
	if (mkfifo(priv, 0644) == -1) {
		printf("[client] error creating private FIFO: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[client] private FIFO created!\n");

	//open WPK
	*to_server = open("wkp", O_WRONLY);
	if (*to_server == -1) {
		printf("[client] error opening WKP: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[client] WKP opened!\n");

	//send name of private FIFO
	if (write(*to_server, priv, sizeof(priv)) == -1) {
		printf("[client] error sending name of private FIFO: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[client] name of private FIFO sent!: %s\n", priv);

	//open private FIFO
	char server_stream[BUFFER_SIZE];
	int private = open(priv, O_RDONLY);
	if (private == -1) {
		printf("[client] error opening private FIFO: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[client] private FIFO opened!\n");

	if (read(private, server_stream, sizeof(server_stream)) == -1) {
		printf("[client] error receiving data from private FIFO: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[client] received msg from server thru private FIFO: %s\n", server_stream);

	//receiving works, remove server_stream FIFO
	if (write(*to_server, "bonjour", 8) == -1) {
		printf("[client] error sending msg thru WKP: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[client] sent msg thru WKP!\n");
	if (remove(priv) == -1) {
		printf("[client] error removing private FIFO: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else
		printf("[client] removed private FIFO successfully!\n");

	return private;
}
