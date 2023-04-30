#include "stshell.h"

/**
 * Opening message during startup shell
 */
void init_shell()
{
	clear();
	printf("\n\n**"
		"**");
	printf("\n\n\t STSHELL");
	printf("\n\n***"
		"*");
	char* username = getenv("USER");
	printf("\n\nUSER is: @%s", username);
	printf("\n");
	sleep(2);
	clear();
}

/**
 * Function to print current directory
 */
void printDir()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
    char* username = getenv("USER");
    printf("%s:%s$ ", username, cwd);
}

/**
 * Redirects stdout to a file.
 * 
 * @param fileName the file to redirect to
 * @param count the number of '>' characters found in the input
 */
void redirectOut(char *fileName,int count)
{
    int inFD;
    if (count == 1) // '>'
    {
        inFD = open(fileName, O_WRONLY | O_APPEND | O_CREAT, 0600);
        if(inFD == -1)
        {
            perror("open file");
        }
    }
    else if (count == 2) // '>>'
    {
        
        inFD = open(fileName, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if(inFD == -1)
        {
            perror("open file");
        }
    }
    dup2(inFD, 1);
    close(inFD);
}

/**
 * Redirects stdin from a file.
 * 
 * @param fileName the file to redirect from
 */
void redirectIn(char *fileName)
{
    int in = open(fileName, O_RDONLY);
    dup2(in, 0);
    close(in);
}

/**
 * Runs a command.
 * 
 * @param *args[] the args to run
 */
void run(char *args[])
{
    pid_t pid;
    if (strcmp(args[0], "Exit") != 0)
        {
            pid = fork();
            if (pid < 0) { 
                fprintf(stderr, "Fork Failed");
            }
            else if ( pid == 0) { // child proccess
                signal(SIGINT, SIG_DFL); // handling SIGINT signals as default 
                execvp(args[0], args);
            }
            else { // parent proccess
                if (should_wait) {
                    waitpid(pid, NULL, 0);
                } else {
                    should_wait = 0;
                }
            }
            redirectIn("/dev/tty");
            redirectOut("/dev/tty",1);
        }
    else {
        should_run = 0;
    }
}

/**
 * Creates a pipe
 * 
 * @param args [description]
 */
void createPipe(char *args[])
{
    int fd[2];
    pipe(fd);

    dup2(fd[1], 1);
    close(fd[1]);

    printf("args = %s\n", *args);

    run(args);

    dup2(fd[0], 0);
    close(fd[0]);
}

/**
 * Signal handler for the SIGINT signal in the parent process
 * 
 * @param sig the signal number
*/
void sigint_handler_p(int sig) {

    printf("\n");
}

/**
 * Prints the help menu for the shell
*/
void openHelp()
{
	puts("\n*WELCOME TO STSHELL HELP!*"
		"\nList of Commands supported:"
		"\n> cd"
		"\n> ls"
		"\n> exit"
		"\n> Pipe handling"
        "\n> Output redirection - append or overwrite"
        "\n> All other general commands available in UNIX shell");

	return;
}

/**
 * Handles built-in commands for the shell
 * 
 * @param parsed the parsed command arguments
 * @return 1 if the command is a built-in command, 0 otherwise
*/
int ownCommands(char** parsed)
{
	int numOfCommands = 4, i, switchOwnArg = 0;
	char* listOfCommands[numOfCommands];
	char* username;

	listOfCommands[0] = "exit";
	listOfCommands[1] = "help";
	listOfCommands[2] = "hello";

	for (i = 0; i < numOfCommands; i++) {
		if (strcmp(parsed[0], listOfCommands[i]) == 0) {
			switchOwnArg = i + 1;
			break;
		}
	}

	switch (switchOwnArg) {
	case 1:
		printf("\nGoodbye\n");
		exit(0);
	case 2:
		openHelp();
		return 1;
	case 3:
		username = getenv("USER");
		printf("\nHello %s.\nMind that this is "
			"not a place to play around."
			"\nUse help to know more..\n",
			username);
		return 1;
	default:
		break;
	}

	return 0;
}

/**
 * Creates a tokenized form of the input with spaces to separate words
 * 
 * @param  *input the input string
 * @return tokenized the tokenized stirng
 */
char * tokenize(char *input)
{
    int i;
    int j = 0;
    char *tokenized = (char *)malloc((MAX_LINE * 2) * sizeof(char));

    // add spaces around special characters
    for (i = 0; i < strlen(input); i++) {
        if (input[i] != '>' && input[i] != '|') {
            tokenized[j++] = input[i];
        } else {
            tokenized[j++] = ' ';
            tokenized[j++] = input[i];
            tokenized[j++] = ' ';
        }
    }
    tokenized[j++] = '\0';

    // add null to the end
    char *end;
    end = tokenized + strlen(tokenized) - 1;
    end--;
    *(end + 1) = '\0';

    return tokenized;
}

/**
 * Main function of the program
 * 
 * @return 0 upon completion
 */
int main(void)
{
    char *args[MAX_LINE]; // command line arguments
    init_shell();
    while (should_run) {
        printDir();
        fflush(stdout);
        signal(SIGINT, sigint_handler_p);
        
        char input[MAX_LINE];
        
        fgets(input, MAX_LINE, stdin);
        if (strcmp(input,"\n") == 0)
        {
            continue;
        }
        char *tokens;
        tokens = tokenize(input);

        if (tokens[strlen(tokens) - 1] == '&') {
            should_wait = 0;
            tokens[strlen(tokens) - 1] = '\0';
        }

        char *arg = strtok(tokens, " ");
        int i = 0;
        int flag = 0;
        while (arg) {
            if(strcmp(arg,"cd") == 0)
            {
                char dir[260] = {0};
                int j = 3; // index 3: 2 chars of 'cd' + 1 space
                while (input[j] != '\0' && input[j] != '\n')
                {
                    dir[j-3] = input[j];
                    j++;
                }
                chdir(dir);
            }
            if (ownCommands(&arg))
            {
                flag = 1;
            }
            if (*arg == '>') { 
                char* s = strtok(NULL, " ");
                if (strcmp(s,">") == 0)
                {
                    redirectOut(strtok(NULL, " "),2);
                }
                else
                {
                redirectOut(s,1);
                }
            }
            else if (*arg == '|') {
                args[i] = NULL;
                createPipe(args);
                i = 0;
            } else {
                args[i] = arg;
                i++;
            }
            arg = strtok(NULL, " ");
        }
        if (flag == 1)
        {
            continue;
        }
        args[i] = NULL;
        run(args);
    }
    return 0;
    
}