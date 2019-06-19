#ifndef NETWORKING_H
#define NETWORKING_H

#define BUFFER_SIZE 256
#define PORT "18633"
#define TEST_IP "127.0.0.1"

void error_check(int i, char *s);
int server_setup();
int server_connect(int sd);
int client_setup(char *server);

#endif
