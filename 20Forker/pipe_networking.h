#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

#ifndef NETWORKING_H
#define NETWORKING_H

#define ACK "HOLA"

#define HANDSHAKE_BUFFER_SIZE 10
#define BUFFER_SIZE 1000

int server_setup();

int subserver_setup(int from_client);

int client_handshake(int *to_server);

#endif
