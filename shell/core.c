#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "core.h"
#define READ 0
#define WRITE 1

int count(char *line, char *delim)
{
	int i;
	int token = 0;
	//find # of tokens
	for (i = 0; line[i]; i++)
		if ((line[i] != delim[0] && line[i] != '\0') && (line[i + 1] == delim[0] || line[i + 1] == '\0')) token++;

	return token;
}

char **sep_line(char *line, char *delim)
{
	int token = count(line, delim);

	int i = 0;
	char *sline = line;
	char **split = calloc(token + 1, sizeof(char *));
	while (sline && sline[0] != '\0') {
		//as long as there are delim keep strsep
		while (sline && sline[0] == delim[0])
			strsep(&sline, delim);
		if (sline[0] != '\0')
			split[i] = sline;
		strsep(&sline, delim);
		i++;
	}

	return split;
}

char *cd(char *line)
{
	int token = count(line, " ");
	//there should only be 1 arg to cd
	if (token > 2) return 0x0;

	//reached this point, so there is a valid # of arguments
	int i = 0;
	char *sline = line;
	char **arg = calloc(3, sizeof(char *));
	while (sline && sline[0] != '\0') {
		//as long as there are spaces keep strsep
		while (sline && sline[0] == ' ')
			strsep(&sline, " ");
		if (sline[0] != '\0')
			arg[i] = sline;
		strsep(&sline, " ");
		i++;
	}

	char *arg1 = arg[1];
	free(arg);
	//no arg provided
	if (arg1 == 0x0)
		return "~";
	return arg1;
}

void redir_out(char **arg, int pos)
{
	arg[pos] = NULL;
	int fd = open(arg[pos + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	int out = dup(STDOUT_FILENO);
	//change stdout to the file
	dup2(fd, STDOUT_FILENO);
	execvp(arg[0], arg);
	dup2(STDOUT_FILENO, out);
	close(fd);
}

void redir_in(char **arg, int pos)
{
	arg[pos] = NULL;
	int fd = open(arg[pos + 1], O_RDONLY);
	int in = dup(STDIN_FILENO);
	//change stdin  to the file
	dup2(fd, STDIN_FILENO);
	execvp(arg[0], arg);
	dup2(in, STDIN_FILENO);
	close(fd);
}

void redir_in_out(char **arg, int pos, int pos2)
{
	arg[pos] = NULL;
	arg[pos2] = NULL;
	int fd_r = open(arg[pos + 1], O_RDONLY);
	int in = dup(STDIN_FILENO);
	int fd_w = open(arg[pos2 + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	int out = dup(STDOUT_FILENO);
	//change stdin  to the file
	dup2(fd_r, STDIN_FILENO);
	//change stdout to the file
	dup2(fd_w, STDOUT_FILENO);
	execvp(arg[0], arg);
	dup2(STDOUT_FILENO, out);
	close(fd_w);
	dup2(in, STDIN_FILENO);
	close(fd_r);
}

void redir_pipe(char **arg, char **arg2)
{
	int fd[2];
	pipe(fd);
	int f1 = fork();
	if (f1) {
		int f2 = fork();
		if (f2) { //parent now with two children
			close(fd[0]);
			close(fd[1]);
			int statusf1, statusf2;
			waitpid(f1, &statusf1, 0);
			waitpid(f2, &statusf2, 0);
			if (WIFEXITED(statusf1)) WEXITSTATUS(statusf1);
			if (WIFEXITED(statusf2)) WEXITSTATUS(statusf2);
		} else { //read child
			close(fd[WRITE]);
			dup2(fd[READ], STDIN_FILENO);
			execvp(arg2[0], arg2);
			close(fd[READ]);
			exit(EXIT_SUCCESS);
		}
	} else { //write child
		close(fd[READ]);
		dup2(fd[WRITE], STDOUT_FILENO);
		execvp(arg[0], arg);
		close(fd[WRITE]);
		exit(EXIT_SUCCESS);
	}
}

void exec(char **arg)
{
	//if command is history
	int f = fork();
	if (f) {
		int status;
		waitpid(f, &status, 0);
		if (WIFEXITED(status)) WEXITSTATUS(status);
	}
	else {
		int i, j;
		//special chars in input
		for (i = 0; arg[i]; i++) {
			if (!strcmp(arg[i], ">")) {
				redir_out(arg, i);
				exit(EXIT_SUCCESS);
			} else if (!strcmp(arg[i], "<")) {
				for (j = i; arg[j]; j++) {
					if (!strcmp(arg[j], ">")) {
						redir_in_out(arg, i, j);
						exit(EXIT_SUCCESS);
					}
				}
				redir_in(arg, i);
				exit(EXIT_SUCCESS);
			} else if (!strcmp(arg[i], "|")) {
				//create arrays corresponding to the left and right of pipe
				char *arg2[i + 1];
				for (j = 0; j < i; j++)
					arg2[j] = arg[j];
				arg2[j] = NULL;
				for (j = i; arg[j]; j++);
				char *arg3[j - i];
				for (j = 0; j < sizeof(arg3) / sizeof(char *); j++)
					arg3[j] = arg[j + i + 1];
				arg3[j] = NULL;
				redir_pipe(arg2, arg3);
				exit(EXIT_SUCCESS);
			}
		}
		//no special chars
		int err = execvp(arg[0], arg);
		if (err) {
			printf("Error %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
}

void exec_line(char *line)
{
	int i;
	char **commands = sep_line(line, ";");
	for (i = 0; commands[i]; i++) {
		char **arg = sep_line(commands[i], " ");
		if (arg[0]) {
			if (!strcmp(arg[0], "exit") || !strcmp(arg[0], "logout")) {
				free(arg);
				free(commands);
				exit(EXIT_SUCCESS);
			}
			exec(arg);
		}
		free(arg);
	}
	free(commands);
}
