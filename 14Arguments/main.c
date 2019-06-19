#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char **parse_args(char *line)
{
	char **mem = calloc(sizeof(char **), 5);
	char *pline = line;
	char *s, count;
	for(; s = strsep(&pline, " "); mem[count++] = s);
	return mem;
}

int main()
{
	char *inp;
	printf("please input your function and its arguments:\n");
	scanf("%[^\n]%*c", inp);

	char **strmem = parse_args(inp);
	for(int i = 0; i < 5 && strmem[i]; i++)
		printf("Argument number %d: %s\n", i, strmem[i]);

	execvp(strmem[0], strmem);

	return 0;
}
