#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	srand(time(NULL));
	printf("I am parent %d\n", getpid());
	printf("Forking...\n");

	int f1, f2, s;
	f1 = fork();
	if (f1) f2 = fork();
	if (!f1 || !f2) {
		printf("I am child %d\n", getpid());
		if(!f1) rand();
		int s = rand() % 16 + 5;
		/* printf("Child %d is going to sleep for %d seconds...\n", getpid(), s); */
		sleep(s);
		printf("Child %d has exited\n", getpid());
		exit(s);
	} else {
		int child = wait(&s);
		printf("Child %d slept for %d seconds\n", child, WEXITSTATUS(s));
		printf("Parent finished running\n");
	}

	return 0;
}
