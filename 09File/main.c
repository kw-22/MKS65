#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int c[256];

	size_t f = open("hi.txt", O_RDWR);
	printf("READING MAX OF 100 BYTES OF hi.txt (input file)\n");
	int bytes_read = read(f, &c, 100);
	printf("%d bytes in total read\n\n", bytes_read);

	size_t g = open("bye.txt", O_RDWR);

	printf("WRITING 3 BYTES INTO bye.txt (output file) \n");
	int bytes_write = write(g, &c, 3);
	printf("%d bytes in total written\n\n", bytes_write);
	write(g, "[end of first write]", 20);
	printf("WRITING 100 BYTES INTO bye.txt (output file)- there may be extra (possibly non-printable) characters\n");
	bytes_write = write(g, &c, 100);
	printf("%d bytes in total written\n\n", bytes_write);

	close(f);
	close(g);

	return 0;
}
