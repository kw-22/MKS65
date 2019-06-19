#include "headers.h"
#include "display.h"
#include "engine.h"
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#include "pipe_networking.h"

int previous = 0;

void move(int spaces, char *binput, char *finput)
{
	//int i;
	//for(i = spaces; i != 0; i--) {
	strcat(binput, " ");
	int forlen = strlen(finput);
	//printf("forward: %s fwd length: %d", finput, forlen);
	finput[forlen - 1] = '\0';
	//}
}

void progress(int amount, char *binput, char *finput)
{
	if (amount != previous) {
		clear_screen();
		move(amount - previous, binput, finput);
		previous = amount;
	}
}

int main()
{
	int to_server;
	int from_server;

	from_server = client_handshake(&to_server);
	char response[100];
	int intresponse;
	setlocale(LC_ALL, "");
	wchar_t star = STAR;
	wchar_t princess = PRINCESS;
	char centerer[100] = "                             ";
	char one_back[100] = " ";
	char one_forward[] = "                        ";
	char two_back[100] = " ";
	char two_forward[] = "                        ";
	char ppl[] = "=";
	char dest[] = "|";
	char one_name[100] = "player 1"; 
	char one_wpm[100] = "0.0"; 
	char one_acc[100] = "0.0";
	char two_wpm[100] = "0.0";
	char two_acc[100] = "0.0";
	char two_name[100] = "player 2";
	//these two if statements help name the players
	if(read(from_server, response, 100) && !strcmp(one_name, "player 1")/*if read from server AND player 1 hasnt been named yet(still has default name)*/){
	  strcpy(one_name, response);
	}
	if(read(from_server, response, 100)/*for naming player 2*/){
	  strcpy(two_name, response);
	}
	while(read(from_server, response, 100)) {
	  //printf("%s\n", response);
	  int changed = 0;
	  char * data = strtok(response, " ");
	  //printf("%s\n", name);
	  /* name = strtok(NULL, " "); */
	  /* printf("%s\n", name); */
	  /* name = strtok(NULL, " "); */
	  /* printf("%s\n", name);	 */  
	  //char * wpm = strtok(NULL, " ");
	  //char * acc = strtok(response, " ");
	  //char * acc = strtok(NULL, " ");
	  //read(from_server, &intresponse, 8);
	  //read(from_server, response, 100);
	  if (!strcmp(data, one_name)) {
	    changed = 1;
	    progress(previous+1, one_back, one_forward);
	    //printf("%s\n", response); //strtok only copying the first item
	    //printf("%s\n", strtok(wpm, " "));
	    //printf("%s\n", strtok(NULL, " "));
	    data = strtok(NULL, " ");	
	    //name = strtok(NULL, "");
	    strcpy(one_wpm, data);
	    data = strtok(NULL, " ");
	    //name = strtok(NULL, " ");
	    strcpy(one_acc, data);
	    //name = "billy";
	  }
	  if (!strcmp(data, two_name)) {
	    changed = 1;
	    progress(previous+1, two_back, two_forward);
	    data = strtok(NULL, " ");	
	    //name = strtok(NULL, "");
	    strcpy(two_wpm, data);
	    data = strtok(NULL, " ");
	    //name = strtok(NULL, " ");
	    strcpy(two_acc, data);
	    //name = "billy";
	  }
	  if (changed) {
	    printf("\n\n\n\n\n\n\n                                         Type Racer\n\n");
	    printf("                                                                     wpm    accuracy\n");
	    printf("%s%s:%s%lc%s%lc  %s    %s%% \n", centerer, one_name, one_back, STAR, one_forward, PRINCESS, one_wpm, one_acc);
	    printf("%s%s:%s%lc%s%lc  %s    %s\%% \n", centerer, two_name, two_back, STAR, two_forward, PRINCESS, two_wpm, two_acc);
	    //printf("%splayer 2:%s%s%s%s %s\n", centerer, two_back, ppl, two_forward, dest);
	  }
	  //wprintf(L"%s%lc%s%lc\n", back, star, forward, princess);
		//printf("%s\n",response);
		//printf("%d\n", intresponse);
		//for (int i = 0; i < 25; i++) {
		//if (strcmp(&response[0], "o")) {
		//progress(previous+1, back, forward);


		//}

		//}
	}

	return 0;
}
