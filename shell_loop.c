#include "main.h"
/**
 * shellLoop - main loop for input/output.
 */
void shellLoop(void)
{
	char *input; /* user input */
	char path[PATH_MAX];
	size_t size = 0; /* size variable for getline */
	pid_t fork_rtn, wait_rtn; /* return values of fork_rtn; also counts as process IDs */
	int exec_rtn = 0; /* return value of execve; default to 0 */
	int child_status, i;
	char *cmd_token;
	char **tokens = malloc(64 * sizeof(char *));
	int tokens_count = 0;
	char *paths[1] = {"#/bin/bash"}; /* first draft */
	/*
	for (int j = 0; j < 1; j++)
	{
		printf("%d: %s\n", j, paths[j]);
	}
	*/
	//printf("getenv: %s\n", getenv("PATH"));

	/* test getenv */
	char *pathz = getenv("PATH");
	char *pathz_token = strtok(pathz, ":");
	int pathz_count = 0;
	char **pathzz = malloc (64 * sizeof(char *));
	while (pathz_token != NULL)
	{
		pathzz[pathz_count] = strdup(pathz_token);
		pathz_token = strtok(NULL, ":");
		pathz_count++;
	}
	pathzz[pathz_count] = NULL;
	for (int j = 0; pathzz[j] != NULL; j++)
		printf("env[%d]: %s\n", j, pathzz[j]);
	/* end test getenv */

	getcwd(path, sizeof(path));

	/* get & save input */
	printf("%s$ ", path);
	getline(&input, &size, stdin);
	printf("Input: %s", input);

	/* PARSING */
	cmd_token = strtok(input, " "); /* first token */
	printf("1: %s\n", cmd_token);

    while (cmd_token != NULL)
	{
		if (tokens_count >= 64)
		{
			tokens = realloc(tokens, (tokens_count + 64) * sizeof(char *));
		}
		tokens[tokens_count] = strdup(cmd_token);
		printf("2: %s\n", tokens[tokens_count]);
		if (tokens_count != 0)
			printf("arg %d: %s\n", tokens_count, tokens[tokens_count]);
		else
			printf("command: %s\n", tokens[0]);
		cmd_token = strtok(NULL, " ");
		printf("3: %s\n", cmd_token);
		tokens_count++;
	}
	tokens[tokens_count] = NULL;
	/* keep an eye out for special characters that can change the meaning */

	/* RUN USER COMMANDS - skeleton version */
	printf("4: %s\n", cmd_token);
	if (tokens[0] != NULL && (strcmp(tokens[0], "q") == 0 || strcmp(tokens[0], "quit") == 0))
		exit(EXIT_SUCCESS);

	fork_rtn = fork();
	if (fork_rtn < 0) /* fork failed */
	{
		perror("fork failed");
		exit(EXIT_FAILURE); /* consider changing exits to continues to return to the user input */
	}
	else if (fork_rtn == 0) /* child */
	{
		exec_rtn = execve(tokens[0], tokens, pathzz);
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

	shellLoop();
}
