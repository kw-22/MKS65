#include "headers.h"
#include "networking.h"
#include "display.h"
#include "server.h"

#define READ 0
#define WRITE 1

// int main()
// {


	// int listen_socket;
	// int f;
	// listen_socket = server_setup();
	// char game_key;

	// printf("Enter in a lowercase letter to get game key");
	// game_key = getchar();
    
    // int p0_to_server[2]; //the pipe that subserver player0 uses to talk to main server
    // int p1_to_server[2]; //the pipe that subserver player1 uses to talk to main server
    // int server_to_p0[2]; //the pipe that main server uses to talk to subserver player0
    // int server_to_p1[2]; //the pipe that main server uses to talk to subserver player1
    
    // pid_t player0; //the process id for subserver player0
    // pid_t player1; //the process id for subserver player1
    
    // int players = 0; //no players have joined yet
	// while (players < 2) {
	  // int client_socket = server_connect(listen_socket);
      // if (players == 0) { //aka the first player to join
        // if((player0 = fork()) == 0) { //fork off a child who is player0 subserver
            // close(p0_to_server[READ]); 
            // close(server_to_p0[WRITE]);
            // players++; //the players variable for player0 is 1, used for tracking
        // }
      // }
      // else if (players == 1) { //the main server increased players variable by 1 after having made the first child
        // if((player1 = fork()) == 0){ //fork off a child who is player1 subserver
            // close(p1_to_server[READ]);
            // close(server_to_p1[WRITE]);
            // players++; //the players variable for player1 is 2, used for tracking
        // }
      // }
      // else if (f) {
          // if (players == 0) {
            // close(p0_to_server[WRITE]);
            // close(server_to_p0[READ]);
          // }
          // else if (players == 1) {
            // close(p1_to_server[WRITE]);
            // close(server_to_p1[READ]);
          // }
          // close(client_socket);
          // players++;
      // }
	// }
    
    // if (player0 != 1 || player1 != 1) {
        // the parent gets the info for display from write(p0..) and write(p1..)
    // }
    
    // if (player0 == 0 || player1 == 0) { //for the child processes 
        // player0 should have its players variable set to 1
        // player1 should have its players variable set to 2
        // char name[5];
        // read(client_socket, name, sizeof(name)) //KERWIN 
        // printf("Hello %s",name);
        // write(client_socket, &game_key, 1);
        
        // char stat[BUFFER_SIZE];
        
        // while (read(client_socket, stat, sizeof(stat))) {
            // if (players == 0) {
                // write(p0_to_server[WRITE],stat,sizeof(stat));
            // }
            // if (players == 1) {
                // write(p1_to_server[WRITE], stat, sizeof(stat));
            // }
        // }
        
        
        // close(client_socket);
        // exit(EXIT_SUCCESS);
    // }
    
	// return 0;
// }

int main() {

  int listen_socket;
  int f;
  listen_socket = server_setup();
  char stat[BUFFER_SIZE];

  while (1) {
    int client_socket = server_connect(listen_socket);
    int pipefd[2];
    pid_t cpid;
    pipe(pipefd);
    cpid = fork();
    
    if (!cpid) {
        // subserver(client_socket);
        close(pipefd[READ]);
        while (read(client_socket, stat, sizeof(stat))) {
            write(pipefd[WRITE], stat, sizeof(stat));
        }
    }
    else {
        close(client_socket);
        close(pipefd[WRITE]);
        while (read(pipefd[READ], stat, sizeof(stat))) {
            printf("%s",stat);
        }
    }
  }
}
