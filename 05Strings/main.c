#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strh.h"

int main() {
	char s1[50] = "bob says hi";
	char s2[50] = "jenny says bye";
	char s3[50] = "i say die";

	printf("s1: [%s]\n", s1);
	printf("s2: [%s]\n", s2);
	printf("s3: [%s]\n", s3);

	printf("\nTesting my_strlen(s1):\n");
	printf("[standard]: %lu\n", strlen(s1));
	printf("[mine]: %i\n", my_strlen(s1));

	printf("\nTesting my_strcpy(s1, s2)\n");
	printf("[standard]: [%s]\n", strcpy(s1, s2));
	printf("[mine]: [%s]\n", my_strcpy(s1, s2));

	printf("\nTesting my_strncpy(s1, s3, 3)\n");
	printf("[standard]: [%s]\n", strncpy(s1, s3, 3));
	printf("[mine]: [%s]\n", my_strncpy(s1, s3, 3));

	printf("\nTesting my_strcat(s1, s3)\n");
	printf("[standard]: [%s]\n", strcat(s1, s3));
	strcpy(s1, "i sny says bye");
	printf("[mine]: [%s]\n", my_strcat(s1, s3));

	printf("\nTesting my_strncat(s1, s2, 3)\n");
	printf("[standard]: [%s]\n", strncat(s1, s2, 3));
	strcpy(s1, "i sny says byei say die");
	printf("[mine]: [%s]\n", my_strncat(s1, s2, 3));

	printf("\nTesting my_strchr(s1, 's')\n");
	printf("[standard]: [%p]\n", strchr(s1, 's'));
	printf("[mine]: [%p]\n", my_strchr(s1, 's'));

	printf("\nTesting my_strchr(s1, 0)\n");
	printf("[standard]: [%p]\n", strchr(s1, 0));
	printf("[mine]: [%p]\n", my_strchr(s1, 0));

	printf("\nTesting my_strchr(s1, 'z')\n");
	printf("[standard]: [%p]\n", strchr(s1, 'z'));
	printf("[mine]: [%p]\n", my_strchr(s1, 'z'));

	printf("\nTesting my_strcmp\n");
	printf("Comparing ab to abc\n");
	printf("[standard]: [%d]\n", strcmp("ab", "abc"));
	printf("[mine]: [%d]\n", my_strcmp("ab", "abc"));

	printf("Comparing abc to ab\n");
	printf("[standard]: [%d]\n", strcmp("abc", "ab"));
	printf("[mine]: [%d]\n", my_strcmp("abc", "ab"));

	printf("Comparing abc to abc\n");
	printf("[standard]: [%d]\n", strcmp("abc", "abc"));
	printf("[mine]: [%d]\n", my_strcmp("abc", "abc"));

	printf("\nTesting my_strstr\n");
	printf("champ in champion?\n");
	printf("[standard]: [%s]\n", strstr("champion", "champ"));
	printf("[mine]: [%s]\n", my_strstr("champion", "champ"));
	printf("ion in champion?\n");
	printf("[standard]: [%s]\n", strstr("champion", "ion"));
	printf("[mine]: [%s]\n", my_strstr("champion", "ion"));
	printf("hapi in champion?\n");
	printf("[standard]: [%s]\n", strstr("champion", "hapi"));
	printf("[mine]: [%s]\n", my_strstr("champion", "hapi"));
	printf("amp in champion?\n");
	printf("[standard]: [%s]\n", strstr("champion", "amp"));
	printf("[mine]: [%s]\n", my_strstr("champion", "amp"));

	return 0;
}
