#include <stdio.h>

#include "launch.h"
#define ANSI_PURPLE "\x1b[35m"
#define ANSI_RESET "\x1b[0m"

void print_phoenix()
{
	printf("%s .\\\\            //.\n\
. \\ \\          / /.\n\
.\\  ,\\     /` /,.-\n\
 -.   \\  /'/ /  .\n\
 ` -   `-'  \\  -\n\
   '.       /.\\`\n\
      -    .-\n\
      :`//.'\n\
      .`.'\n\
      .'\n%s", ANSI_PURPLE, ANSI_RESET);
}

void print_disclaimer()
{
	printf("DISCLAIMER: USE AT YOUR OWN RISK!\n");
	printf("DO NOT USE Ctrl-D: OTHERWISE YOU MIGHT NEED TO USE SIGKILL TO STOP THE SHELL\n");
}
