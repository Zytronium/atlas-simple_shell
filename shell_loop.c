#include "main.h"
#include <stdlib.h>

/**
 * shellLoop - main loop for input/output.
 */
void shellLoop(void)
{
	char *input; /* user input */
	char *path = "User"; //= getcwd();
	size_t *__restrict size;
	pid_t fork_rtn, wait_rtn; /* return values of fork_rtn; also counts as process IDs */
	int exec_rtn = 0; /* return value of execve; default to 0 */
	int child_status;
	char *cmd_token = NULL;
	char **tokens = NULL;
	int tokens_count = 0;

	/* get & save input */
	printf("%s $ ", path);
	getline(&input, size, stdin);
	printf("Command: ");

	/* PARSING */

	tokens = malloc(strlen(input)); /* might need to be changed */
    cmd_token = strtok(input, " "); /* first token */

    while (cmd_token != NULL) {
		tokens[tokens_count] = cmd_token;
		tokens_count++;
	}
	/* consider counting number of words after first word to keep track of arguments for a function */
	/* if the number of arguments matches the number required for the command in the first argument: fork command and input arguments */
	/* - if not either display an error, ignore the garbage words, or something else */
	/* keep an eye out for special characters that can change the meaning */

	/* run user-inputed commands - skeleton version */

	if (cmd_token == "q" || cmd_token == "quit")
		exit(EXIT_SUCCESS);

	fork_rtn = fork();
	if (fork_rtn < 0) /* fork failed */
	{
		perror("fork failed");
		exit(EXIT_FAILURE); /* consider changing exits to continues to return to the user input */
	}
	else if (fork_rtn == 0) /* child */
	{
		exec_rtn = (cmd_token, tokens, paths);
		if (exec_rtn == -1)
		{
			perror("execute failure");
			exit(EXIT_FAILURE);
		}
	}
	else /* parent; fork_rtn contains pid of child process */
	{
		wait_rtn = waitpid(fork_rtn, &child_status, 0); /* waits until child process terminates */
		if (wait_rtn == -1)
		{
			perror("wait failed");
			exit(EXIT_FAILURE);
		}
	}
}
