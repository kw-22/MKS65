#include "pipe_networking.h"

int main()
{
	int to_server;
	int from_server;
	char input[BUFFER_SIZE];
	char data[BUFFER_SIZE];

	from_server = client_handshake(&to_server);

	while (1) {
		printf("Type something: ");
		if (!fgets(input, sizeof(input), stdin))
			printf("Error: %s\n", strerror(errno));
		input[strlen(input) - 1] = '\0';

		if (write(to_server, input, sizeof(input)) == -1)
			printf("Error: %s\n", strerror(errno));
		if (read(from_server, data, sizeof(data)) == -1)
			printf("Error: %s\n", strerror(errno));
		printf("Received: %s\n", data);
	}

	return 0;
}
