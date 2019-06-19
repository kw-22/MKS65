# shell

## Features:

* Prints a phoenix on shell launch

* Command prompt with more detailed info than the typical ```BASH```

* Forks and executes commands

* Parses multiple commands on one line

* Redirects using ```<```, ```>``` (limited use - must put whitespace before and after them)

* Piping (limited to single pipe - must put whitespace before and after it)

* Excess spaces in commands allowed

* Option to view commands history

* Doesn't include full path if current directory is subdirectory of home directory

* Handles directory changing

* Catches ```Ctrl-C```

* Putting a bunch of ;'s next to each other work

* Exits with either ```exit``` or ```logout```

* Pretty good at not having memory leaks

## Attempted:

* Using ```~``` with ```cd``` (```cd ~``` works though)

* Find a way to deal with ```Ctrl-D``` that works on all computers

* Display a command prompt after catching ```Ctrl-C```

* Recreate a commands history file after it has been deleted during the time when the shell is running

* Using redirection with pipes

## Bugs and Issues:

* Sometimes ```Ctrl-D``` causes the shell to keep on printing command prompts (might be an issue of OS)

* When redirecting a file as ```stdin```, some commands print the command prompt a couple of times while others don't work (like ```history```)

* Cannot deal with tabs in command input

* Input cannot be more than 127 chars

## Files and Function Headers:

launch.c

```
	The functions executed when shell first launched

	===========    void print_phoenix()    =============
	inputs: none
	returns: returns void
	prints out a purple phoenix ASCII art when shell is first launched

	===========    void print_disclaimer()    =============
	inputs: none
	returns: void
	prints out a disclaimer when shell is first launched
```

core.c

```
	Most of the parsing and executing of functions occur here

	============     int count(char *line, char *delim)    =============


	inputs: char *line, char *delim

	returns: # of tokens separated by the delim in it

	strseps through the string and increases the count by one if delim is encountered after

	non-delim char

	=========    char **sep_line(char *line, char *delim)    ===========

	inputs: char *line, char *delim

	returns: an array of pointers pointing to the beginning of line and all non-delim chars

	following a delim

	first calculates the # of tokens in line to determine the size of the array

	strseps through line and points a pointer to the address of a char if the char has the

	right properties

	============     char *cd(char *line)     ==============

	inputs: char *line

	returns: a string of the desired path to cd into

	assuming first token is cd, strseps through line and either finds or generates the proper

	arg to chdir

	=======    void redir_out(char **arg, int pos)    ========

	inputs: char **arg, int pos

	returns: void

	sets arg[pos] to NULL and uses arg[pos + 1] as the file to redirect stdout to and execvp using

	the valid args of arg

	=========     void redir_in(char **arg, int pos)     ===========

	inputs: char **arg, int pos

	returns: void

	sets arg[pos] to NULL and uses arg[pos + 1] as the file to redirect stdin from and execvp using

	the valid args of arg

	=========    void redir_in_out(char **arg, int pos, int pos2)   =========

	inputs: char **arg, int pos, int pos2

	returns: void

	sets arg[pos] and arg[pos2] to NULL and uses arg[pos + 1] as the file to redirect stdin from

	and arg[pos2 + 1] as the file to redirect stdout to and execvp using the valid args of arg

	==========      void redir_pipe(char **arg, char **arg2)      =========

	inputs: char **arg, char **arg2

	returns: void

	creates a pipe and uses the output of execvp on arg and uses it as the input of execvp on arg2

	========     void exec(char **arg)    ===========

	inputs: char **arg

	returns: void

	uses the elements of arg as args to execvp and runs different functions depending on the

	existence and type of special chars

	======    void exec_line(char *line)    =========

	inputs: char *line

	returns: void

	splits the line by ; and cleans the resulting strings of spaces before passing each of them

	to exec
```

shell.c

```
	The shell interface
```
