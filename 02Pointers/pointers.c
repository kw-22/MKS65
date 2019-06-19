#include <stdio.h>
#include <stdlib.h>

int main()
{
	//unsigned int n = 2536184303;
	unsigned int n = 2536184253;
	//char *pt = &n; //creates a warning
	char *pt = (char *)&n;

	printf("n in decimal is: %u, in hex is: 0x%x\n", n, n);

	//prints out each byte of n
	printf("\nPrinting out each byte of n\n");
	int i;
	for (i = 0; i < 4; i++) {
		printf("byte #%d of n is: %hhx\n", i + 1, *pt);
		pt++;
	}

	pt -= 4; //reset pointer location

	//increments each byte of n by 1
	printf("\nIncrementing each byte of n by 1\n");
	for (i = 0; i < 4; i++) {
		(*pt)++;
		pt++;
		printf("n in decimal is now: %u, and in hex is: 0x%x\n", n, n);
	}

	pt -= 4; //reset pointer location

	//increment each byte of n by 16
	printf("\nIncrementing each byte of n by 16\n");
	printf("%p", pt);
	for (i = 0; i < 4; i++) {
		*pt += 16;
		pt++;
		printf("n in decimal is now: %u, and in hex is: 0x%x\n", n, n);

	}

	//pointer arithmetic is more like modular arithmetic than ordinary arithmetic
	//in the case of 2536184303, 982c1af0 became 982c1a00

	return 0;
}
