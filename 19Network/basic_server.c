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

int main()
{
	signal(SIGINT, sighandler);

	int to_client;
	int from_client;
	char buffer[BUFFER_SIZE];

	while (1) {
		from_client = server_handshake(&to_client);

		printf("Waiting for food...\n");
		while (read(from_client, buffer, sizeof(buffer))) {
			printf("Received: %s\n", buffer);
			meme(buffer);
			write(to_client, buffer, sizeof(buffer));
		}
		close(from_client);
		remove("wkp");
	}

	return 0;
}
