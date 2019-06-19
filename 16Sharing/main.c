#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#include <sys/ipc.h>
#include <sys/shm.h>


int main()
{
	key_t key;
	int shmid;
	char *data;
	char ans[3];

	//create and connect segment
	if ((key = ftok("main.c", 'R')) == -1) {
		printf("Error %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if ((shmid = shmget(key, 200, 0644 | IPC_CREAT)) == -1) {
		printf("Error %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	//attach segment
	if ((data = (char *)shmat(shmid, 0, 0)) == (char *)-1) {
		printf("Error %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	!(*data) ? printf("Segment just created!\n") : printf("Here is the shared content: %s\n", data);

	printf("Do you want to change the data? [y/n] \n");
	fgets(ans, sizeof(ans), stdin);
	ans[1] = '\0';
	if (!strcmp("y", ans)) {
		printf("Enter a new string: ");
		fgets(data, 200, stdin);
	}

	//detach segment
	if (shmdt(data) == -1) {
		printf("Error %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("Do you want to delete the segment? [y/n] \n");
	fgets(ans, sizeof(ans), stdin);
	ans[1] = '\0';
	if (!strcmp("y", ans)) {
		//delete segment
		if (shmctl(shmid, IPC_RMID, NULL) == -1) {
			printf("Error %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

	}

	return 0;
}
