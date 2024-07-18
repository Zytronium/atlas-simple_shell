#include "main.h"
#include "colors.h"

/**
 * shellLoop - main loop for input/output.
 */
void shellLoop(void)
{
	char *input; /* user input */
	char path[PATH_MAX]; /* current working dir path */
	size_t size = 0; /* size variable for getline */
	pid_t fork_rtn, wait_rtn; /* return values of fork_rtn; also counts as process IDs */
	int exec_rtn = 0; /* return value of execve; default to 0 */
	int child_status;
	char *cmd_token;
	char **tokens = malloc(64 * sizeof(char *));
	int tokens_count = 0;
	char *paths[3] = {".", "/bin/bash", "/usr/bin/env bash"}; /* first draft */

	getcwd(path, sizeof(path));

	/* get & save input */
	printf(SET_CLR_BLUE_BOLD); /* sets the text color to blue */
	printf("%s", path); /* prints the path in blue */
	printf("%s$ ", SET_CLR_DEFAULT); /* rests text color and prints '$' */
	getline(&input, &size, stdin);
	printf("Input: %s", input);
	input[strlen(input) - 1] = '\0'; /* delete newline at end of string */

	/* PARSING */
	cmd_token = strtok(input, " "); /* first token */

    while (cmd_token != NULL)
	{
		if (tokens_count >= 64)
			tokens = realloc(tokens, (tokens_count + 64) * sizeof(char *));

		tokens[tokens_count] = strdup(cmd_token);

		if (tokens_count != 0)
			printf("arg %d: %s\n", tokens_count, tokens[tokens_count]);
		else
			printf("command: %s\n", tokens[0]);

		cmd_token = strtok(NULL, " ");
		tokens_count++;
	}
	tokens[tokens_count] = NULL;
	printf("\n"); /* visually separate debug prints from output */

	/* ↓------------- custom command "self-destruct" -------------↓ */
	if (tokens[0] != NULL && strcmp(tokens[0], "self-destruct") == 0)
	{
		int countdown = 5; /* number of seconds to countdown from */
		/* initialized to 5 in case user doesn't give a number */

		/* check if user gave any args and if it's a valid positive number */
		if (tokens[1] != NULL && isNumber(tokens[1]) && atoi(tokens[1]) > 0)
			countdown = atoi(tokens[1]); /* set countdown to given number */
			/*
			 * note: I'd use abs() instead of checking if its positive, but
			 * abs() is not an allowed function and I don't want to code it.
			 */

		selfDestruct(countdown);
		/* should we handle the condition if the cmd has too many arguments? */
	}
	/* ↑------------- custom command "self-destruct" -------------↑ */

	if (tokens[0] != NULL && strcmp(tokens[0], "exit") == 0)
		exit(EXIT_SUCCESS);

	/* consider counting number of words after first word to keep track of arguments for a function */
	/* if the number of arguments matches the number required for the command in the first argument: fork command and input arguments */
	/* - if not either display an error, ignore the garbage words, or something else */
	/* keep an eye out for special characters that can change the meaning */

	/* run user-inputed commands - skeleton version */

	/*if (strcmp(cmd_token, "q") == 0 || strcmp(cmd_token, "exit") == 0)
		exit(EXIT_SUCCESS);

	fork_rtn = fork();
	if (fork_rtn < 0) *//* fork failed *//*
	{
		perror("fork failed");
		exit(EXIT_FAILURE); *//* consider changing exits to continues to return to the user input *//*
	}
	else if (fork_rtn == 0) *//* child *//*
	{
		exec_rtn = execve(cmd_token, tokens, paths);
		if (exec_rtn == -1)
		{
			perror("execute failure");
			exit(EXIT_FAILURE);
		}
	}
	else *//* parent; fork_rtn contains pid of child process *//*
	{
		wait_rtn = waitpid(fork_rtn, &child_status, 0); *//* waits until child process terminates *//*
		if (wait_rtn == -1)
		{
			perror("wait failed");
			exit(EXIT_FAILURE);
		}
	}*/

	shellLoop();
}

/**
 * isNumber - check for non-number characters in a string.
 * If any of the supplied numbers have non-number characters in them,
 * return 0.
 *
 * @number: string to be checked if it's all numbers
 *
 * Return: 1 if it's all numbers; 0 if not.
 */
int isNumber(char *number)
{
	unsigned int i;

	for (i = 0; i < strlen(number); i++)
	{
		if (number[i] > '9' || number[i] < '0')
			return (0);
	}

	return (1);
}