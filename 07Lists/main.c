#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

int main()
{
	int i;

	struct node *list = 0;
	printf("Adding 3...\n");
	list = insert_front(list, 3);
	printf("Adding 4...\n");
	list = insert_front(list, 4);
	printf("Data in list:\n");
	print_list(list);

	printf("Adding a bunch of #s\n");
	for (i = 0; i < 5; i++)
		list = insert_front(list, i);
	printf("Data in list:\n");
	print_list(list);

	list = free_list(list);
	printf("list cleared\n");
	print_list(list);

	return 0;
}
