#ifndef PIPE_NETWORKING_H
#define PIPE_NETWORKING_H

#define ACK "HOLA"
#define HANDSHAKE_BUFFER_SIZE 10
#define BUFFER_SIZE 1000

int server_handshake(int *to_client);

int client_handshake(int *to_server);

#endif
