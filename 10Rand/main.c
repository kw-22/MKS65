#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int random_int()
{
	int fd = open("/dev/urandom", O_RDONLY);
	int rand;

	if (read(fd, &rand, sizeof(int)) == -1)
		printf("Error %s\n", strerror(errno));
	if (close(fd) == -1)
		printf("Error %s\n", strerror(errno));

	return rand;
}

int main()
{
	umask(0000);

	int i;
	int c[10], cc[10];

	printf("Generating random numbers:\n");

	for (i = 0; i < 10; i++) {
		c[i] = random_int();
		printf("\trandom %d: %d\n", i, c[i]);
	}

	printf("Writing numbers to a file...\n\n");
	int fd_w = open("out.txt", O_CREAT | O_RDWR, 0655);
	if (write(fd_w, &c, sizeof(c)) == -1)
		printf("Error %s\n", strerror(errno));
	if (close(fd_w) == -1)
		printf("Error %s\n", strerror(errno));

	printf("Reading numbers from file...\n\n");
	int fd_r = open("out.txt", O_RDONLY);
	if (read(fd_r, &cc, sizeof(cc)) == -1)
		printf("Error %s\n", strerror(errno));
	if (close(fd_r) == -1)
		printf("Error %s\n", strerror(errno));

	printf("Verification that written values were the same:\n");
	for (i = 0; i < 10; i++)
		printf("\trandom %d: %d\n", i, cc[i]);

	return 0;
}
