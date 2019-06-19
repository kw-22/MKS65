#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

void print_list(struct node *n)
{
	while (n)
	{
		printf("%d ", n->i);
		n = n->next;
	}
	printf("\n");
}

struct node *insert_front(struct node *n, int a)
{
	struct node *new_node;
	new_node = (struct node *)malloc(sizeof(new_node));
	new_node->i = a;
	new_node->next = n;
	return new_node;
}

struct node *free_list(struct node *n)
{
	while (n)
	{
		struct node *removed = n;
		n = n->next;
		free(removed);
		removed = NULL;
	}
	return n;
}
