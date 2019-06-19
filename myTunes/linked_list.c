#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "linked_list.h"

/*********  LENGTH  *********/
int length(struct node *p) {
	int ans = 0;
	while (p) {
		ans++;
		p = p->next;
	}
	return ans;
}

/*******  PRINTING FUNCTIONS  *******/
void print_list(struct node *p) {
	print_node(p);
	if (p)
		print_list(p->next);
}

void print_node(struct node *p) {
	if (p)
		printf(" %s : %s |", p->artist, p->song);
	else
		printf("\n");
}

/********   FINDING THINGS   *********/
struct node *first_song(struct node *p, char *artist) {
	if (p) {
		//artist names don't match
		if (strcmp(p->artist, artist))
			return first_song(p->next, artist);
		return p;
	}
	printf(" artist not found");
	return 0x0;
}

struct node *find_songll(struct node *p, char *song, char *artist) {
	if (p) {
		//artist and song names match
		if (!strcmp(p->artist, artist) && !strcmp(p-> song, song))
			return p;
		return find_songll(p->next, song, artist);
	}
	printf(" song not found");
	return 0x0;
}

struct node *random_song(struct node *p) {
	int len = length(p);
	if (len) { //doesn't make sense if len is 0
		int r = rand() % len;
		while (r) {
			r--;
			p = p->next;
		}
		return p;
	}
	return 0x0;
}


/********  INSERTING THINGS   ***********/
struct node *insert_front(struct node *p, char *song, char *artist) {
	struct node *head = malloc(sizeof(struct node));
	strncpy(head->song, song, 100);
	strncpy(head->artist, artist, 100);
	head->next = p;
	return head;
}

struct node *insert_in_order(struct node *head, char *song, char *artist) {
	if (head) {
		if (strcmp(head->artist, artist) <= 0 && strcmp(head->song, song) < 0)
			return insert_io_helper(head, head, head->next, song, artist);
	}
	return insert_front(head, song, artist);
}

struct node *insert_io_helper(struct node *head, struct node *prev_node, struct node *curr_node, char *song, char *artist) {
	if (curr_node) {
		if (strcmp(curr_node->artist, artist) < 0) //artist is alphabetically later
			return insert_io_helper(head, prev_node->next, curr_node->next, song, artist);
		else if (!strcmp(curr_node->artist, artist) && strcmp(curr_node->song, song) < 0) //same artist but song is alphabetically later.
			return insert_io_helper(head, prev_node->next, curr_node->next, song, artist);
	}
	prev_node->next = insert_front(curr_node, song, artist);
	return head;
}

/*********   REMOVING STUFF  **********/
struct node *remov(struct node *head, char *song, char *artist)
{
	struct node *prev = head; //pointer to original head

	//if head is what we want, easy!
	if (head && (strcmp(head->artist, artist) == 0 && strcmp(head->song, song) == 0)) {
		head = head->next;
		free(prev);
		return head;
	}

	struct node *temp = head; //current struct to compare
	struct node *temp_prev = head; //struct that was compared before temp
	while (temp) {
		//match did not occur
		if (strcmp(temp->artist, artist) || strcmp(temp->song, song)) {
			temp_prev = temp;
			temp = temp->next;
		} else
			break;
	}

	//temp was last struct in linked list
	if (temp) {
		if (!(temp->next)) {
			temp_prev->next = 0x0;
			free(temp);
			temp = 0x0;
		} else
			temp_prev->next = temp->next;
	} else
		printf("%s by %s not found\n", song, artist);
	return head;
}

/********   FREEING STUFF   ***********/
struct node *free_list(struct node *p) {
	if (p) {
		free_list(p->next);
		free(p);
		p = 0x0;
	}
	return 0x0;
}
