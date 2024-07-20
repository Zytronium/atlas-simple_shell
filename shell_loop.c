#include "main.h"
#include "colors.h"

/**
 * shellLoop - main loop for input/output.
 */
void shellLoop(char *argv[])
{
	char *input; /* user input */
	char path[PATH_MAX]; /* current working dir path */
	size_t size; /* size variable for getline */
	char *cmd_token;
	char **tokens = NULL;
	int tokens_count;
	char *cmd;
	char *bash_dir = "/usr/bin/";
	char *paths[1] = {NULL};
	int getline_rtn;
	int i;
	/* TODO: consider changing to multiple locations that will be searched with algo that combines cmd_token and if (access ... true) */

	while (1)
	{
		/* ---------------- variable (re)initializations ---------------- */
		getcwd(path, sizeof(path));
		tokens_count = 0;
		getline_rtn = 0;
		size = 0;
		input = "";
		tokens = malloc(64 * sizeof(char *));
		if (tokens == NULL)
			exit(EXIT_FAILURE);

		/* initialize all tokens in array to null */
		for (i = 0; i < 64; i++)
			tokens[i] = NULL;

		/* print prompt (path + '$') */
		if (stylePrints)
		{
			printf(CLR_BLUE_BOLD); /* sets the text color to blue */
			printf("%s", path); /* prints the path in blue */
			printf("%s$ ", CLR_DEFAULT); /* resets text color and prints '$' */
		}

		/* get & save input */
		getline_rtn = getline(&input, &size, stdin);
		if (getline_rtn == -1) /* End Of File (^D) */
		{
			if (stylePrints)
				printf("\n%sCtrl-D Entered. %s\nThe %sGates Of Shell%s have closed. "
					"Goodbye.\n%s\n", CLR_DEFAULT_BOLD, CLR_YELLOW_BOLD,
					CLR_RED_BOLD, CLR_YELLOW_BOLD, CLR_DEFAULT);
			free_all(tokens, input, NULL);
			exit(EXIT_SUCCESS);
		}
		input[strlen(input) - 1] = '\0'; /* delete newline at end of string *//* TODO: consider checking if this char acutally is a newline */

		/* parse the input */
		cmd_token = strtok(input, " "); /* first token */
		if (cmd_token == NULL) /* blank command - only spaces or newline */
		{
			free_all(tokens, input, NULL);
			continue;
		}
		cmd = malloc(strlen(bash_dir) + strlen(cmd_token) + 1);
		if (cmd == NULL) /* malloc fail check */
		{
			free_all(tokens, cmd, input, NULL);
			exit(EXIT_FAILURE); /* TODO: might want to consider printing an error message and skipping to the end of loop instead of terminating program */
		}
		/* initialize cmd to the command to pass to execve */
		if (cmd_token[0] != '/' && cmd_token[0] != '.')
		{
			strcpy(cmd, bash_dir); /* insert bash path if command is not already a path */
			strcat(cmd, cmd_token); /* add input command */
		}
		else /* if user input a path */
			strcpy(cmd, cmd_token); /* initialize cmd to the input path */

		while (cmd_token != NULL)
		{
			if (tokens_count >= 64)
				tokens = realloc(tokens, (tokens_count + 64) * sizeof(char *));

			tokens[tokens_count] = strdup(cmd_token);

			cmd_token = strtok(NULL, " ");
			tokens_count++;
		}
		tokens[tokens_count] = NULL;

		/* RUN USER COMMANDS */

		/* ↓----------------- custom command "exit" -----------------↓ */
		if (tokens[0] != NULL && (strcmp(tokens[0], "exit") == 0 || strcmp(tokens[0], "quit") == 0))
		{
			free_all(tokens, cmd, input, NULL);
			exit(EXIT_SUCCESS);
		}
		/* ↑----------------- custom command "exit" -----------------↑ */

		/* ↓------------- custom command "self-destruct" -------------↓ */
		if (tokens[0] != NULL && (strcmp(tokens[0], "self-destruct") == 0 || strcmp(tokens[0], "selfdestr") == 0))
		{
			int countdown = 5; /* number of seconds to countdown from */
			/* initialized to 5 in case user doesn't give a number */

			/* check if user gave any args and if it's a valid positive number */
			if (tokens[1] != NULL && isNumber(tokens[1]) && atoi(tokens[1]) > 0)
				countdown = atoi(tokens[1]); /* set countdown to given number */
				/*
				* NOTE: I'd use abs() instead of checking if its positive, but
				* abs() is not an allowed function and I don't want to code it.
				*/
			free_all(tokens, cmd, input, NULL);
			selfDestruct(countdown);
			/* TODO: should we handle the condition if the cmd has too many arguments? */
		}
		/* ↑------------- custom command "self-destruct" -------------↑ */

		/* run command; if child process fails, stop the child process from re-entering loop */
		runCommand(cmd, tokens, paths, argv);

		free_all(tokens, cmd, input, NULL);
	}
}

/**
 * free_all - frees all dynamically allotted memory
 * @tokens: array of strings needing free()
 */
void free_all(char **tokens, ...)
{
	va_list vars;
	int i;
	char *free_me;

	/* fflush(NULL); */
	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);
	free(tokens);
	va_start(vars, tokens);
	free_me = va_arg(vars, char *);
	while (free_me != NULL)
	{
		free(free_me);
		free_me = va_arg(vars, char *);
	}
	va_end(vars);
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

/**
 * runCommand - runs execve on a commandPath, handles forking and errors.
 *
 * @commandPath: command to run, including path(?)
 * @args: array of args for commandPath, including the commandPath (without path)
 * @envPaths: paths for the environment(?)
 *
 * Return: 0 on success, -1 on failure, -2 on failure from child process.
 */
int runCommand(char *commandPath, char **args, char **envPaths, char *argv[])
{
	int exec_rtn = 0, child_status, errnum;
	pid_t fork_rtn, wait_rtn;

	fork_rtn = fork();
	if (fork_rtn == -1) /* Fork! It failed */
	{
		perror("An error occurred while running command"); /* error message */
		return (-1); /* indicate error */
	}
	if (fork_rtn == 0) /* child process */
	{
		exec_rtn = execve(commandPath, args, envPaths); /* executes user-command */
		if (exec_rtn == -1)
		{
			/* perror("An error occurred while running command"); error message */
			errnum = errno;
			fprintf(stderr, "%s: 1: %s: %s\n", argv[0], commandPath, strerror(errnum));
			return(errnum); /* indicate error */
		}
	}
	else /* parent process; fork_rtn contains pid of child process */
	{
		wait_rtn = waitpid(fork_rtn, &child_status, WUNTRACED); /* waits until child process terminates */
		if (wait_rtn == -1)
		{
			perror("An error occurred while running command"); /* error message */
			return (-1); /* indicate error */
		}
	}

	return (0); /* success */
}
