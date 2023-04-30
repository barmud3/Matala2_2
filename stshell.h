#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdlib.h>
#include <signal.h>

#define MAX_LINE 1024 // The maximum length command
#define clear() printf("\033[H\033[J") // Clearing the shell using escape sequences

int should_run = 1;  // flag to determine when to exit program
int should_wait = 1; // flag to determine if process should run in the background

void init_shell();
void printDir();
void redirectOut(char *fileName,int count);
void redirectIn(char *fileName);
void run(char *args[]);
void createPipe(char *args[]);
void sigint_handler_p(int sig);
int ownCommands(char** parsed);
char * tokenize(char *input);