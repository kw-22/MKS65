#include "pipe_networking.h"
#include <ctype.h>
#include <signal.h>

static void sighandler(int signo)
{
	if (signo == SIGINT) {
		printf("Server is now closing...\n");
		remove("wkp");
		exit(EXIT_SUCCESS);
	}
}

void meme(char *s)
{
	int fd = open("/dev/urandom", O_RDONLY);
	int r;

	for (int i = 0; s[i]; i++) {
		if (read(fd, &r, sizeof(short)) == -1)
			printf("Error: %s\n", strerror(errno));

		if (r % 2) s[i] = toupper(s[i]);
		else s[i] = tolower(s[i]);
	}

	if (close(fd) == -1)
		printf("Error: %s\n", strerror(errno));
}

void subserver(int from_client)
{
	int to_client = subserver_setup(from_client);
	char buffer[BUFFER_SIZE];

	printf("[subsever %d] Waiting for food...\n", getpid());
	while (read(from_client, buffer, sizeof(buffer))) {
		printf("[subserver %d] Received: %s\n", getpid(), buffer);
		meme(buffer);
		write(to_client, buffer, sizeof(buffer));
	}
	close(to_client);
}

int main()
{
	signal(SIGINT, sighandler);

	int from_client;

	while (1) {
		int f = fork();
		if (f) from_client = server_setup();
		else {
			subserver(from_client);
			exit(EXIT_SUCCESS);
		}
	}

	return 0;
}
