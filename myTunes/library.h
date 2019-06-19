#ifndef LIB_H
#define LIB_H

struct node *table[27];

void insert(char *song, char *artist);

struct node* find_song(char *song, char *artist);
struct node* find_artist(char *artist);

void print_all_letter(char l);
void print_all_artist(char *artist);
void print_all();

void shuffle();

void del(char *song, char *artist);
void clear();

#endif
