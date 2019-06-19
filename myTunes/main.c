#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "linked_list.h"
#include "library.h"

int main() {

	struct node *head = insert_in_order(0x0, "dying in la", "panic! at the disco");
	head = insert_in_order(head, "vegas lights", "panic! at the disco");
	head = insert_in_order(head, "miss jackson", "panic! at the disco");
	head = insert_in_order(head, "neon gravestones", "twenty one pilots");
	head = insert_in_order(head, "e", "panic! at the disco");

	printf("            TESTING LINKED LIST FUNCTIONS\n");
	printf("=========================================\n\n");

	printf("            TESTING PRINTING THE LIST:\n");
	printf("=========================================\n\n");
	printf("testing the null case -- print a null list:\n");
	printf("expect: \nactual: ");
	print_list(NULL);
	printf("\ntesting on a longer list:\n");
	printf("expect: panic! at the disco : dying in la | panic! at the disco : e | panic! at the disco : miss jackson | panic! at the disco : vegas lights | twenty one pilots : neon gravestones |\n\nactual:");
	print_list(head);
	printf("=========================================\n\n");

	printf("\n\n           TESTING PRINTING A NODE:\n");
	printf("=========================================\n\n");
	printf("expect: panic! at the disco : dying in la |\nactual:");
	print_node(head);
	printf("\n=========================================\n\n");

	printf("\n\n           TESTING ADDING IN ORDER:\n");
	printf("=========================================\n\n");
	printf("adding i write sins not tragedies by panic! at the disco\n");
	head = insert_in_order(head, "i write sins not tragedies", "panic! at the disco");
	printf("expect: panic! at the disco : dying in la | panic! at the disco : e | panic! at the disco : i write sins not tragedies | panic! at the disco : miss jackson | panic! at the disco : vegas lights | twenty one pilots : neon gravestones |\n\nactual:");
	print_list(head);
	printf("\n=========================================\n");
	printf("adding a by panic! at the disco\n");
	head = insert_in_order(head, "a", "panic! at the disco");
	printf("expect: panic! at the disco : a | panic! at the disco : dying in la | panic! at the disco : e | panic! at the disco : i write sins not tragedies | panic! at the disco : miss jackson | panic! at the disco : vegas lights | twenty one pilots : neon gravestones |\n\nactual:");
	print_list(head);
	printf("=========================================\n\n");

	printf("\n\n           TESTING FIRST SONG OF AN ARTIST:\n");
	printf("=========================================\n\n");
	printf("first song by panic! at the disco:\n");
	printf("expect: panic! at the disco : a |\nactual:");
	print_node(first_song(head, "panic! at the disco"));
	printf("\n\n");
	printf("first song by twenty one pilots:\n");
	printf("expect: twenty one pilots : neon gravestones |\nactual:");
	print_node(first_song(head, "twenty one pilots"));
	printf("\n\n");
	printf("first song by me:\n");
	printf("expect: artist not found\nactual:");
	print_node(first_song(head, "me"));
	printf("=========================================\n\n");

	printf("\n\n           TESTING FIND NODE:\n");
	printf("=========================================\n\n");
	printf("find vegas lights by patd: (should find it)");
	print_node(find_songll(head, "vegas lights", "panic! at the disco"));
	printf("\nfind high hopes by top (shouldn't find anything):");
	print_node(find_songll(head, "high hopes", "twenty one pilots"));
	printf("=========================================\n\n");

	printf("\n\n           TESTING RANDOM SONG:\n");
	printf("=========================================\n\n");
	srand(time(NULL));
	print_node(random_song(head));
	printf("\n");
	print_node(random_song(head));
	printf("\n");
	printf("=========================================\n\n");

	printf("\n\n           TESTING REMOVE:\n");
	printf("=========================================\n\n");
	print_list(head);
	printf("==========================================================\n");
	printf("\nremoving vegas lights by panic! at the disco\n");
	head = remov(head, "vegas lights", "panic! at the disco");
	print_list(head);
	printf("==========================================================\n");
	printf("\nremoving a by panic! at the disco\n");
	head = remov(head, "a", "panic! at the disco");
	print_list(head);
	printf("==========================================================\n");
	printf("\nremoving a by panic! at the disco\n");
	head = remov(head, "a", "panic! at the disco");
	printf("==========================================================\n");
	printf("\nremoving neon gravestones by twenty one pilots\n");
	head = remov(head, "neon gravestones", "twenty one pilots");
	print_list(head);
	printf("==========================================================\n");

	printf("\n\n           TESTING FREEING THE LIST:\n");
	printf("=========================================\n\n");
	printf("testing the null case -- free a null list:\n");
	free_list(NULL);
	printf("> null list has been freed with no problems\n");
	printf("\ntesting on a longer list:\n");
	printf("Now freeing: ");
	print_list(head);
	head = free_list(head);
	printf("expect: \nactual: ");
	print_list(head);
	printf("=========================================\n\n");

	printf("\n\n           TESTING ADDING TO THE FRONT:\n");
	printf("=========================================\n\n");
	printf("adding oh comely by neutral milk hotel\n");
	head = insert_front(head, "oh comely", "neutral milk hotel");
	print_list(head);
	printf("adding born to be blonde by jesse rutherford\n");
	head = insert_front(head, "born to be blonde", "jesse rutherford");
	print_list(head);
	printf("adding fools by troye sivan\n");
	head = insert_front(head, "fools", "troye sivan");
	print_list(head);
	head = free_list(head);
	printf("=========================================\n\n");


	printf("\n             TESTING LIB FUNCTIONS\n");
	printf("=========================================\n\n");
	insert("pyramid song", "radiohead");
	insert("flamingo", "kero kero bonito");
	insert("bandito", "twenty one pilots");
	insert("isle of flightless birds", "twenty one pilots");
	insert("green", "cavetown");
	insert("27", "fall out boy");
	insert("idol", "bts");
	insert("ramune", "snail's house");
	insert("king of carrot flowers pt. 1", "neutral milk hotel");
	insert("in the aeroplane over the sea", "neutral milk hotel");
	insert("teen idle","marina and the diamonds");
	insert("introduction and rondo capriccioso","saint-saens");
	insert("pixel galaxy","snail's house");
	insert("primadonna","marina and the diamonds");
	insert("love4eva","loona");
	insert("terrible things","mayday parade");
	insert("perfect man","shinhwa");
	insert("blood sweat and tears","bts");
	insert("lake effect kid","fall out boy");
	insert("happier","marshmello");
	insert("a song","!an artist");
	insert("another song","@nother @rtist");
	insert("two headed boy","neutral milk hotel");
	insert("bodys","car seat headrest");
	insert("up on melancholy hill","gorillaz");

	printf("\n\n            TESTING PRINT ALL:\n");
	printf("==========================================================\n");
	print_all();
	printf("==========================================================\n");

	printf("\n\n            TESTING ADDING A SONG:\n");
	printf("==========================================================\n");
	printf("adding monster by exo:\n");
	insert("monster", "exo");
	print_all();
	printf("==========================================================\n");

	printf("\n\n            TESTING FIND SONG:\n");
	printf("==========================================================\n");
	printf("find \"a good song\" by me: (there shouldn't be one)\n");
	print_node(find_song("a good song", "me"));
	printf("\n");
	printf("find love4eva by loona: (there should be one)\n");
	print_node(find_song("love4eva", "loona"));
	printf("\n");
	printf("==========================================================\n");

	printf("\n\n            TESTING FIND ARTIST:\n");
	printf("==========================================================\n");
	printf("finding artist bts (shoudl be one)\n");
	print_node(find_artist("bts"));
	printf("\n");
	printf("finding artist aristotle (shoudln't be one)\n");
	print_node(find_artist("aristotle"));
	printf("==========================================================\n");


	printf("\n\n            TESTING PRINT ALL UNDER A LETTER:\n");
	printf("==========================================================\n");
	print_all_letter('a');
	print_all_letter('b');
	printf("==========================================================\n");

	printf("\n\n            TESTING PRINT ARTIST:\n");
	printf("==========================================================\n");
	printf("printing all songs by marina and the diamonds\n");
	print_all_artist("marina and the diamonds");
	printf("printing all songs by me\n");
	print_all_artist("me");
	printf("==========================================================\n");

	printf("\n\n            TESTING DELETE SONG:\n");
	printf("==========================================================\n");
	printf("deleting perfect man by shinhwa\n");
	del("perfect man", "shinhwa");
	printf("also deleting idol by bts\n");
	del("idol", "bts");
	printf("updated library:\n");
	print_all();
	printf("==========================================================\n");



	printf("\n\n            TESTING SHUFFLE:\n");
	printf("==========================================================\n");
	shuffle();
	printf("\n");
	shuffle();
	printf("\n");
	printf("==========================================================\n");


	printf("\n\n            TESTING CLEAR:\n");
	printf("==========================================================\n");
	clear();
	print_all();
	printf("==========================================================\n");

	return 0;
}
