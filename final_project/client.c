// #include "headers.h"
// #include "networking.h"
// #include "engine.h"

// #define READ 0
// #define WRITE 1

// int main(int argc, char *argv[])
// {
	// int server_socket;
	// char buffer[BUFFER_SIZE];

	// if (argc == 2) server_socket = client_setup(argv[1]);
	// else server_socket = client_setup(TEST_IP); //connect to itself

	// printf("\nHi! Welcome to Rypetacer!\nTo play, type \"play\":");

	// while (1) {
		// printf("Enter an alphabetic letter: ");
		// fgets(buffer, sizeof(buffer), stdin);
		// *strchr(buffer, '\n') = 0;
		// if (buffer[0] == 'p' || buffer[0] == 'P') {
			// printf("Enter the first four letters of your name: ");
			// fgets(buffer, 4, stdin);
			// *strchr(buffer, '\n') = '\0';
			// write(server_socket, buffer, sizeof(buffer));
			// printf("Waiting for game to start...\n");

			// char story_key;

			// if (read(server_socket, &story_key, 1)) { //server has replied meaning game will start
				// int pipefd[2];
				// pid_t cpid;
				// char buffstat[BUFFER_SIZE]; //%d(wpm) SPACE %lf(accuracy) SPACE %d(correct words)
				// pipe(pipefd); //create the pipe
				// cpid = fork(); //duplicate the current process

				// if (cpid) { //i am the parent
					// close(pipefd[READ]); //close the read end of the pipe, parent only passes pipe through play
					// play(buffer, pipefd, story_key); //pass pipe through play, play will write to pipe
					// close(pipefd[WRITE]); //done writing after finished palying
					// waitpid(cpid, NULL, 0);
					// exit(EXIT_SUCCESS);
				// } else {
					// close(pipefd[WRITE]); //close write end, child only reads data from game
					// while (read(pipefd[READ], buffstat, sizeof(buffstat))) { //while parent is still sending game data
						// write(server_socket, buffstat, sizeof(buffstat)); //send server the data
					// }
					// close(pipefd[READ]); //done reading
					// exit(EXIT_SUCCESS);
					// read(server_socket, bufferstat, sizeof(buffer));
				// }
			// }
			// printf("received: [%s]\n", buffer);
		// }
	// }

	// return 0;
// }

#include "headers.h"
#include "networking.h"
#include "engine.h"

#define READ 0
#define WRITE 1

int main(int argc, char **argv) {

    int server_socket;
	char buffstat[BUFFER_SIZE];
    char name[BUFFER_SIZE];
    char game_key[2];

	if (argc == 2) server_socket = client_setup(argv[1]);
	else server_socket = client_setup(TEST_IP); //connect to itself

	printf("\nHi! Welcome to Rypetacer!\nTo play, type a lowercase letter for a command:");
    
    while (1) {
        printf("Enter name: ");
        fgets(name, sizeof(name), stdin);
		*strchr(name, '\n') = 0;
        
		printf("Enter command: ");
		fgets(game_key, sizeof(game_key), stdin);
		*strchr(game_key, '\n') = 0;
        
        int pipefd[2];
        pid_t cpid;
        pipe(pipefd);
        cpid = fork();
        if (cpid) { //i am the parent
			close(pipefd[READ]); //close the read end of the pipe, parent only passes pipe through play
            play(name, pipefd, game_key[0]); //pass pipe through play, play will write to pipe
			close(pipefd[WRITE]); //done writing after finished palying
			waitpid(cpid, NULL, 0);
            exit(EXIT_SUCCESS);
        }
        else {
			close(pipefd[WRITE]); //close write end, child only reads data from game
			while (read(pipefd[READ], buffstat, sizeof(buffstat))) { //while parent is still sending game data
                write(server_socket, buffstat, sizeof(buffstat)); //send server the data
			}
			close(pipefd[READ]); //done reading
			exit(EXIT_SUCCESS);
			// read(server_socket, bufferstat, sizeof(buffer));
		}
    }
    return 0;
}
