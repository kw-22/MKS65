#ifndef CORE_H
#define CORE_H

//inputs: char *line, char *delim
//returns: # of tokens separated by the delim in it
//strseps through the string and increases the count by one if delim is encountered after
//non-delim char
int count(char *line, char *delim);

//inputs: char *line, char *delim
//returns: an array of pointers pointing to the beginning of line and all non-delim chars
//following a delim
//first calculates the # of tokens in line to determine the size of the array
//strseps through line and points a pointer to the address of a char if the char has the
//right properties
char **sep_line(char *line, char *delim);

//inputs: char *line
//returns: a string of the desired path to cd into
//assuming first token is cd, strseps through line and either finds or generates the proper
//arg to chdir
char *cd(char *line);

//inputs: char **arg, int pos
//returns: void
//sets arg[pos] to NULL and uses arg[pos + 1] as the file to redirect stdout to and execvp using
//the valid args of arg
void redir_out(char **arg, int pos);

//inputs: char **arg, int pos
//returns: void
//sets arg[pos] to NULL and uses arg[pos + 1] as the file to redirect stdin from and execvp using
//the valid args of arg
void redir_in(char **arg, int pos);

//inputs: char **arg, int pos, int pos2
//returns: void
//sets arg[pos] and arg[pos2] to NULL and uses arg[pos + 1] as the file to redirect stdin from
//and arg[pos2 + 1] as the file to redirect stdout to and execvp using the valid args of arg
void redir_in_out(char **arg, int pos, int pos2);

//inputs: char **arg, char **arg2
//returns: void
//creates a pipe and uses the output of execvp on arg and uses it as the input of execvp on arg2
void redir_pipe(char **arg, char **arg2);

//inputs: char **arg
//returns: void
//uses the elements of arg as args to execvp and runs different functions depending on the
//existence and type of special chars
void exec(char **arg);

//inputs: char *line
//returns: void
//splits the line by ; and cleans the resulting strings of spaces before passing each of them
//to exec
void exec_line(char *line);

#endif
