#include "main.h"
#include "colors.h"

/**
 * shellLoop - main loop for input/output.
 */
void shellLoop(int isAtty, char *argv[])
{
	char *input; /* user input */
	char path[PATH_MAX]; /* current working dir path */
	char *user = _getenv("USER") ? _getenv("USER") : _getenv("LOGNAME"); /* current user name */
	char *hostname = _getenv("NAME") ? _getenv("NAME") : _getenv("HOSTNAME") ? _getenv("HOSTNAME") : _getenv(("WSL_DISTRO_NAME")); /* PC name or host name */
	size_t size; /* size variable for getline */
	char *cmd_token;
	char **tokens = NULL;
	int tokens_count;
	char *cmd;
	char *paths[1] = {NULL};
	int custom_cmd_rtn, getline_rtn, run_cmd_rtn;
	int i;

	while (1)
	{
		/* ---------------- variable (re)initializations ---------------- */
		getcwd(path, sizeof(path));
		tokens_count = 0;
		getline_rtn = 0;
		size = 0;
		input = NULL;
		tokens = malloc(64 * sizeof(char *));
		if (tokens == NULL)
			exit(EXIT_FAILURE);

		/* initialize all tokens in array to null */
		for (i = 0; i < 64; i++)
			tokens[i] = NULL;

		if (isAtty) /* checks interactive mode */
		{
			/* print prompt in color ("[Go$H] | user@hostname:path$ ") */
			printf("%s[%sGo$H%s]%s | ", CLR_YELLOW_BOLD, CLR_RED_BOLD,
			CLR_YELLOW_BOLD, CLR_DEFAULT); /* print thing to let me know I'm in this shell, not the real one */
			printf("%s%s@%s", CLR_GREEN_BOLD, user, hostname); /* prints user@host in green (i.e. julien@ubuntu) */
			printf("%s:%s%s", CLR_DEFAULT_BOLD, CLR_BLUE_BOLD, path); /* prints the path in blue */
			printf("%s$ ", CLR_DEFAULT); /* resets text color and prints '$ ' */
		}
		/* get & save input */
		getline_rtn = getline(&input, &size, stdin);
		if (getline_rtn == -1) /* End Of File (^D) */
		{
			if (isAtty)
				printf("\n%sCtrl-D Entered. %s\nThe %sGates Of Shell%s have closed. "
					"Goodbye.\n%s\n", CLR_DEFAULT_BOLD, CLR_YELLOW_BOLD,
					CLR_RED_BOLD, CLR_YELLOW_BOLD, CLR_DEFAULT);
			freeAll(tokens, input, hostname, user, NULL);
			exit(EXIT_SUCCESS);
		}
		input[strlen(input) - 1] = '\0'; /* delete newline at end of string */

		/* PARSE INPUT */
		cmd_token = strtok(input, " "); /* first token */
		if (cmd_token == NULL) /* blank command - only spaces or newline */
		{
			freeAll(tokens, input, NULL);
			continue; /* go back to start of the loop */
		}

		while (cmd_token != NULL)
		{
			if (tokens_count >= 64)
			{
				tokens = realloc(tokens, (tokens_count + 64) * sizeof(char *));
				if (tokens == NULL)
				{
					freeAll(tokens, cmd, input, NULL);
					continue;
				}
			}
			tokens[tokens_count] = strdup(cmd_token);
			cmd_token = strtok(NULL, " ");
			tokens_count++;
		}
		tokens[tokens_count] = NULL;

		/* ------------------- RUN USER COMMANDS -------------------  */
		/* initialize cmd to the command to pass to execve */
		if (tokens[0][0] != '/' && tokens[0][0] != '.')/*if input isn't a path*/
			cmd = findPath(tokens[0]);
		else /* if user's input is a path */
			cmd = strdup(tokens[0]); /* initialize cmd to the input path */
		/* check if input is a custom command; run it if it is one */
		custom_cmd_rtn = customCmd(tokens, isAtty, input, cmd, user, hostname, NULL);

		/* run command; if child process fails, stop the child process from re-entering loop */
		if (custom_cmd_rtn == 0) /* input is not a custom command */
		{
			run_cmd_rtn = runCommand(cmd, tokens, paths); /* runs the command otherwise */
			if (run_cmd_rtn != 0)
				fprintf(stderr, "%s: 1: %s: %s\n", argv[0], cmd, strerror(run_cmd_rtn));
		}
		freeAll(tokens, cmd, input, NULL);
	}
}

/**
 * free_all - frees all dynamically allotted memory
 * @tokens: array of strings needing free()
 */
void freeAll(char **tokens, ...)
{
	va_list vars;
	int i;
	char *free_me;

	/* fflush(NULL); */
	if (tokens != NULL)
	{
		for (i = 0; tokens[i] != NULL; i++)
			free(tokens[i]);
		free(tokens);
	}
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
 * runCommand - runs execve on a command. Handles forking and errors.
 *
 * @commandPath: command to run, including path
 * @args: array of args for commandPath, including the command (without path)
 * @envPaths: paths for the environment
 *
 * Return: 0 on success, -1 on failure, -2 on failure from child process.
 */
int runCommand(char *commandPath, char **args, char **envPaths)
{
	int exec_rtn = 0, child_status;
	pid_t fork_rtn, wait_rtn;

	if (access(commandPath, F_OK) != 0) /* checks if cmd doesn't exists */
		return(127);
	fork_rtn = fork(); /* split process into 2 processes */
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
			perror("An error occurred while running command");
			return(-1); /* indicate error */
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

/**
 * customCmd - checks if the given input is a custom command. If so, executes it
 *
 * @tokens: tokens.
 * @input: the user's input, aka the command.
 * @interactive: if the shell is running in interactive mode (argc)
 * ...: any additional variables to be freed if the command exits. (i.e. user)
 *
 * Return: 1 if it was a custom command and it was successfully executed,
 * 0 if it's not a custom command,
 * -1 on error
 */
int customCmd(char **tokens, int interactive, ...)
{
	va_list args;

	va_start(args, interactive);
	/* ↓----------------- custom command "exit" -----------------↓ */
	if (tokens[0] != NULL && (strcmp(tokens[0], "exit") == 0 || strcmp(tokens[0], "quit") == 0))
	{
		freeAll(tokens, args);

		if (interactive)
			printf("%s\nThe %sGates Of Shell%s have closed. Goodbye.\n%s",
			   CLR_YELLOW_BOLD, CLR_RED_BOLD, CLR_YELLOW_BOLD, CLR_DEFAULT);

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
		freeAll(tokens, args);
		selfDestruct(countdown); /* runs exit() when done */
		return (-1); /* indicate error if selfDestruct never exits */
		/* TODO: should we handle the condition if the cmd has too many arguments? */
	}
	/* ↑------------- custom command "self-destruct" -------------↑ */
	va_end(args);

	return (0);
}
