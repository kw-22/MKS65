#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int array[10];
	srand(time(NULL)); //seed RNG

	int i;

	//populate array
	for (i = 0; i < sizeof(array) / 4; i++)
		array[i] = rand();

	printf("The array...\n");
	for (i = 0; i < sizeof(array) / 4; i++)
		printf("ele %d is: %d\n", i, array[i]);

	array[9] = 0;
	printf("\nThe array after last element became 0...\n");
	for (i = 0; i < sizeof(array) / 4; i++)
		printf("ele %d is: %d\n", i, array[i]);

	int array2[10];

	//create pointers to arrays
	int *pt = array;
	int *pt2 = array2;

	//populate array2 in reverse order
	for (i = 0; i < sizeof(array2) / 4; i++)
		*(pt2 + i) = *(pt + 9 - i);

	printf("\nThe new array...\n");
	for (i = 0; i < sizeof(array2) / 4; i++)
		printf("ele %d is: %d\n", i, array2[i]);

	return 0;
}
