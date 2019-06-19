#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct node {
	char song[100];
	char artist[100];
	struct node *next;
};

//length
int length(struct node *p);

//printing
void print_list(struct node *p);
void print_node(struct node *p);

//finding
struct node *first_song(struct node *p, char *artist);
struct node *find_songll(struct node *p, char *song, char *artist);
struct node *random_song(struct node *p);

//inserting
struct node *insert_front(struct node *p, char *song, char *artist);
struct node *insert_in_order(struct node *p, char *song, char *artist);
struct node *insert_io_helper(struct node *head, struct node *prev_node, struct node *curr_node, char *song, char *artist);

//removing
struct node *remov(struct node *head, char *song, char *artist);

//freeing
struct node *free_list(struct node *p);

#endif
