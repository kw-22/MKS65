#ifndef ENGINE_H
#define ENGINE_H

#define ANSI_BLACK "\x1b[30m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_BG_RED "\x1b[41m"
#define ANSI_BG_GREEN "\x1b[42m"
#define ANSI_RESET "\x1b[0m"
#define clear_screen() printf("\e[1;1H\e[2J");
#define BACKSPACE 8
#define CHARS_PER_WORD 5

int print_text(char *s1, char *s2);

int count_correct(char *s1, char *s2);

int count_incorrect(char *s1, char *s2);

int all_correct(char *s1, char *s2);

double timer();

int calculate_wpm(int num_typed, char *s1, char *s2, double t1, double t2);

double calculate_accuracy(int accu_counter, char *s1, char *s2);

int last_word_correct(int pos, char *s1, char *s2);

void write_results(double time, int WPM, double accuracy);

void play(char *name, int pipefd[], char letter);

#endif
