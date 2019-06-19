#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#include "core.h"
#include "launch.h"

#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

static void sighandler(int signo)
{
	if (signo == SIGINT) printf("SURPRISE\n");
}

int main()
{
	signal(SIGINT, sighandler);

	int i;

	/*************************         SETUP          ************************/

	char input[256]; //user command line input
	char input_copy[256];

	char hostname[128];
	hostname[127] = '\0';
	gethostname(hostname, 127);
	char *user = getenv("USER"); //username

	char *home = getenv("HOME"); //home dir
	char cwd[128]; //current working dir
	char history_dir[116]; //path of history
	getcwd(history_dir, sizeof(history_dir));
	strcat(history_dir, "/.sh_history");
	printf("%s\n", history_dir);

	int history = open(".sh_history", O_CREAT | O_RDWR | O_APPEND, 0644); //file to log history

	print_disclaimer();
	print_phoenix();
	printf("\n");
	/**************************************************************************/

	while (1) {
		/****************        typical shell prompt        ******************/
		getcwd(cwd, sizeof(cwd));
		//cwd is not subdir of homedir
		if (!strstr(cwd, home)) printf("%s@%s%s%s %s%s%s> ", user, ANSI_RED, hostname, ANSI_RESET, ANSI_GREEN, cwd, ANSI_RESET);
		else { //don't need to include the entire path
			for (i = 0; home[i]; i++)
				cwd[i + 1] = cwd[i + strlen(home)]; //"shift" bytes over
			cwd[strlen(home) + 1] = '\0';
			cwd[0] = '~';
			printf("%s@%s%s%s %s%s%s> ", user, ANSI_RED, hostname, ANSI_RESET, ANSI_GREEN, cwd, ANSI_RESET);
		}
		//get input
		if (fgets(input, sizeof(input), stdin)) input[strlen(input) - 1] = '\0';

		//all empty spaces as input is boring
		int valid = 0;
		for (i = 0; input[i]; i++) {
			if (input[i] != ' ') {
				valid = 1;
				break;
			}
		}
		/**********************************************************************/

		if (valid) {
			//write to history
			char msg[257];
			sprintf(msg, "%s\n", input);
			if(write(history, &msg, strlen(msg)) == -1) printf("Error %s\n", strerror(errno));

			//cd-ing
			if ((input[0] == 'c' && input[1] == 'd') && (input[2] == '\0' || input[2] == ' ')) {
				strcpy(input_copy, input);
				char *path = cd(input);
				if (path == 0x0) printf("Too many arguments for cd\n");
				else {
					if (path[0] == '~') chdir(home);
					else {
						int err = chdir(path);
						if (err) printf("Error %s\n", strerror(errno));
					}
				}
			} else if ((input[0] == 'h' && input[1] == 'i' && input[2] == 's' && input[3] == 't' && input[4] == 'o' && input[5] == 'r' && input[6] == 'y') && (input[7] == '\0' || input[7] == ' ')) {
				FILE *hist = fopen(history_dir, "r");
				if (hist != NULL) {
					char c = fgetc(hist);
					while (c != EOF) {
						printf("%c", c);
						c = fgetc(hist);
					}
					fclose(hist);
				} else
					printf("\n");
			} else exec_line(input);
		}
	}

	if (close(history) == -1) printf("Error %s\n", strerror(errno));

	return 0;
}
