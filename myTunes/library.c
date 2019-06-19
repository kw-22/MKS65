#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "linked_list.h"
#include "library.h"

void insert(char *song, char *artist) {
	int i = artist[0] - 'a';
	if (i >= 27 || i < 0)
		i = 26;
	struct node *p = table[i];
	table[i] = insert_in_order(p, song, artist);
}

struct node *find_song(char *song, char *artist) {
	int i = artist[0] - 'a';
	if (i >= 27 || i < 0)
		i = 26;
	struct node *p = table[i];
	return find_songll(p, song, artist);
}

struct node *find_artist(char *artist) {
	int i = artist[0] - 'a';
	if (i >= 27 || i < 0)
		i = 26;
	struct node *p = table[i];
	return first_song(p, artist);
}

void print_all_letter(char l) {
	printf("%c:", l);
	print_list(table[l - 'a']);
}

void print_all() {
	int i = 27;
	while (i) {
		if (table[27 - i]) {
			printf("%c:", 27 - i + 'a');
			print_list(table[27 - i]);
		}
		i--;
	}
}

void print_all_artist(char *artist)
{
	struct node* p = find_artist(artist);
	while (p) {
		if (!strcmp(p->artist, artist))
			print_node(p);
		p = p->next;
	}
	printf("\n");
}

void shuffle() {
	int i = 10;
	while (i) {
		int r = rand() % 27;
		if (random_song(table[r])) {
			print_node(random_song(table[r]));
			printf("\n");
			i--;
		}
	}
}

void del(char *song, char *artist) {
	int i = artist[0] - 'a';
	if (i >= 27 || i < 0)
		i = 26;
	struct node *p = table[i];
	remov(p, song, artist);
}

void clear() {
	int i = 27;
	while (i) {
		free(table[i]);
		table[i] = 0x0;
		i--;
	}
}
