#include "headers.h"
#include "pipe_networking.h"

static void sighandler(int signo)
{
	if (signo == SIGINT) {
		remove("serverR");
		exit(EXIT_SUCCESS);
	}
}

void mom(char* str)
{
	int i = 0;
	while(str[i]) {
		str[i] = toupper(str[i]);
		i++;
	}
}

int main()
{
	signal(SIGINT, sighandler);

	int to_client;
	int from_client;

	from_client = server_handshake(&to_client);
	while(1) {
		char input[100];
		fgets(input, 100, stdin);
		//int fromserver;
		//scanf("%d", &fromserver);
		input[strlen(input) - 1] = '\0';

		write(to_client, input, 100);
	}

	return 0;
}
