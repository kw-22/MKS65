#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <fcntl.h>

#include <signal.h>

#include <time.h>

static void sighandler(int signo)
{
	if (signo == SIGINT) {
		char c[256];
		time_t rawtime;
		struct tm *timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		sprintf(c, "program exited due to SIGINT at %s\n", asctime(timeinfo));

		int fd = open("log.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (write(fd, c, strlen(c)) == -1)
			printf("Error %s\n", strerror(errno));
		if (close(fd) == -1)
			printf("Error %s\n", strerror(errno));
		exit(0);
	} else if (signo == SIGUSR1)
		printf("parent pid: %d\n", getppid());
}

int main()
{
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);

	while (1) {
		printf("my pid: %d\n", getpid());
		sleep(1);
	}

	return 0;
}
