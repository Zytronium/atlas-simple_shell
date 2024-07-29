#include "main.h"
#include "colors.h"

/*
 * shellLoop variables descriptions - because we can't put them on
 * the line they are declared due to betty forcing us to put multiple
 * on each line to shorten the function below 40 lines
 *
 * @size: size for getline()
 * @user: current user name
 * @hostname: host name or device name
 * @path: current working directory
 * @input: user input
 * @tokens: array of strings of tokenized user inputs deliminated by spaces
 * @cmd: user-inputed command with possible path prefixed
 * @cmd_token: tool for strtok
 * @paths: array of strings of env paths
 * @custom_cmd_rtn: return value of customCmd()
 * @run_cmd_rtn: return value of runCommand()
 * @tokens_count: number of tokens while initializing the tokens
 * @i: iterator variable for a for loop somewhere
 */

/**
 * shellLoop - main loop for input/output.
 *
 * @isAtty: is interactive mode
 * @argv: args passed into main()
 */
void shellLoop(int isAtty, char *argv[])
{
	size_t size;
	char /**user, *hostname, */path[PATH_MAX], *input, **tokens = NULL;
	char *cmd, *cmd_token, *paths[1] = {NULL};
	int tokens_count, i;

	while (1)
	{
		/* initialize vars */
		getcwd(path, sizeof(path));
		/*user = getUser();
		hostname = getHostname();*/
		tokens_count = 0;
		size = 0;
		input = NULL;
		tokens = malloc(64 * sizeof(char *));
		if (tokens == NULL) /* malloc fail check */
			exit(EXIT_FAILURE);

		/* initialize all tokens in array to null */
		for (i = 0; i < 64; i++)
			tokens[i] = NULL;

		/*printPrompt(isAtty, user, hostname, path);*/
		if (isAtty)
			printf("$ ");
		saveInput(isAtty, tokens, &size, &input);
		if (parseInput(input, &tokens, &cmd_token, &tokens_count) == -1)
		{
			if (isAtty)
				continue;
			exit(EXIT_SUCCESS);
		}
		initCmd(&cmd, tokens);
		executeIfValid(isAtty, argv, input, tokens, cmd, cmd_token, paths);
	}
}

/**
 * printPrompt - prints prompt in color ("[Go$H] | user@hostname:path$ ")
 *
 * @isAtty: is interactive mode
 * @user: environment variable for user's username
 * @hostname: environment variable for user's hostname or device name.
 * @path: current working directory
 */
void printPrompt(int isAtty, char *user, char *hostname, char *path)
{
	if (isAtty && stylePrints) /* checks interactive mode */
	{
		/* print thing to let us know we're in this shell, not the real one */
		printf("%s[%sGo$H%s]%s | ", CLR_YELLOW_BOLD, CLR_RED_BOLD,
			   CLR_YELLOW_BOLD, CLR_DEFAULT); /*Go$H stands for Gates of Shell*/
		/* prints user@host in green (i.e. julien@ubuntu) */
		printf("%s%s@%s", CLR_GREEN_BOLD, user, hostname);
		/* prints the path in blue */
		printf("%s:%s%s", CLR_DEFAULT_BOLD, CLR_BLUE_BOLD, path);
		/* resets text color and prints '$ ' */
		printf("%s$ ", CLR_DEFAULT);
	}
	else if (isAtty && !stylePrints)
		printf("$");

	free(user);
	free(hostname);
}

/**
 * saveInput - get & save input
 *
 * @isAtty: isatty() return. if 1 interactive, 0 otherwise
 * @tokens: empty container for tokenized inputs
 * @getline_rtn: return value of getline() function
 * @size: size of input
 * @input: user-input
 */
void saveInput(int isAtty, char **tokens, size_t *size, char **input)
{
	if (getline(input, size, stdin) == -1) /* gets input; plus EOF (^D) check */
	{
		if (isAtty && stylePrints)
			printf("\n%sCtrl-D Entered. %s\nThe %sGates Of Shell%s have closed."
				   " Goodbye.\n%s\n", CLR_DEFAULT_BOLD, CLR_YELLOW_BOLD,
				   CLR_RED_BOLD, CLR_YELLOW_BOLD, CLR_DEFAULT);
		freeAll(tokens, (*input), NULL);
		exit(EXIT_SUCCESS);
	}
	/* (*input)[strlen((*input)) - 1] = '\0'; */ /* delete newline at end of string */
}

/**
 * parseInput - parsed the user-input into tokens
 * @input: user-input
 * @tokens: empty token containers
 * @cmd_token: strtok tool
 * @tokens_count: token counter
 *
 * Return: 1 if successful, -1 if failed
 */
int parseInput(char *input, char ***tokens, char **cmd_token, int *tokens_count)
{
	(*cmd_token) = strtok(input, " \n\t\r"); /* first token */
	if ((*cmd_token) == NULL) /* blank command - only spaces or newline */
	{
		freeAll((*tokens), input, NULL);
		return (-1); /* go back to start of the loop */
	}

	if (populateTokens(input, tokens, cmd_token, tokens_count) == -1)
		return (-1);

	if ((*tokens) == NULL)
	{
		freeAll((*tokens), /*cmd, */input, NULL);
		return (-1);
	}
	(*tokens)[(*tokens_count)] = NULL;

	return (1);
}

/**
 * populateTokens: populates the tokens with user-inputs
 * @input: user-input
 * @tokens: populates tokens with parsed cmd_token
 * @cmd_token: container of delimited tokens
 * @tokens_count: token counter
 *
 * Return: 1 if successful, -1 if not
 */
int populateTokens(const char *input, char ***tokens, char **cmd_token,
				   int *tokens_count)
{
	while ((*cmd_token) != NULL)
	{
		if ((*tokens_count) >= 64)
			(*tokens) = realloc((*tokens), (*tokens_count) * sizeof(char *));

		if ((*tokens) == NULL)
		{
			freeAll((*tokens), input, NULL);
			return (-1);
		}

		(*tokens)[(*tokens_count)] = strdup((*cmd_token));
		(*cmd_token) = strtok(NULL, " \n\t\r");
		(*tokens_count)++;
	}
	return (1);
}

/**
 * initCmd - initialize cmd to the command to pass to execve
 * @cmd: variable to be initialized
 * @tokens: tokens
 *
 * Return: command
 */
void initCmd(char **cmd, char *const *tokens)
{
	if (tokens[0][0] != '/' && tokens[0][0] != '.') /* if input isn't a path */
		*cmd = findPath(tokens[0]);
	else /* if user's input is a path */
		*cmd = strdup(tokens[0]); /* initialize cmd to the input path */
}

/**
 * executeIfValid - check if a command is a valid custom or built-in command;
 * run the command if it is valid; if child process fails,stop it
 * from re-entering loop
 *
 * @isAtty: result of isatty(), 1 if interactive, 0 otherwsie
 * @argv: carrier of filename in [0]
 * @input: user-input
 * @tokens: array of strings of user inputs delimited by spaces
 * @cmd: first argument of user-input prefixed with found filepath
 * @cmd_token:last arguments from strtok'd input
 * @paths:array of strings of filepaths
 * @run_cmd_rtn: return value of run_command function
 */
void executeIfValid(int isAtty, char *const *argv, char *input, char **tokens,
					char *cmd, char *cmd_token, char **paths)
{
	int run_cmd_rtn;

	/* run command */
	if (customCmd(tokens, isAtty, input, cmd, cmd_token) == 0)
	{ /* if input is not a custom command */
		/* runs the command if it is a valid built-in */
		run_cmd_rtn = runCommand(cmd, tokens, paths);
		/* prints error if command is invalid or another error occurs */
		if (run_cmd_rtn != 0)
		{
			if (run_cmd_rtn == 127)
				fprintf(stderr, "%s: 1: %s: %s\n", argv[0], cmd,
					"not found");
			else if (run_cmd_rtn == 13)
				perror(cmd);
			else
				fprintf(stderr, "%s: 1: %s: %s\n", argv[0], cmd,
						strerror(run_cmd_rtn));
			if (!isAtty)
			{
				freeAll(tokens, cmd, input, NULL);
				exit(run_cmd_rtn);
			}
		}
	}

	freeAll(tokens, cmd, input, NULL);
}

/**
 * free_all - frees all dynamically allotted memory
 * @tokens: array of strings needing free()
 * ...: list of variables to free
 */
void freeAll(char **tokens, ...)
{
	va_list vars;
	int i;
	char *free_me;

	/*fflush(NULL);*/
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
 * Return: 0 on success, -1 on failure, errno on failure from child process.
 */
int runCommand(char *commandPath, char **args, char **envPaths)
{
	int exec_rtn = 0, child_status, wexitstat;
	pid_t fork_rtn, wait_rtn;

	if (commandPath == NULL)
	{
		if (isatty(STDIN_FILENO))
			return (0);
		else
			exit(0);
	}

	if (access(commandPath, F_OK) != 0) /* checks if cmd doesn't exist */
	{
		return (127);
		/* if (isatty(STDIN_FILENO))
			return (127);
		else
			errno = 127;
			exit(127);
		*/
	}

	fork_rtn = fork(); /* split process into 2 processes */
	if (fork_rtn == -1) /* Fork! It failed */
	{
		return (EXIT_FAILURE); /* indicate error */
	}
	if (fork_rtn == 0) /* child process */
	{
		exec_rtn = execve(commandPath, args, envPaths);/*executes user-command*/
		if (exec_rtn == -1)
		{
			exit(errno); /* indicate error */
		}
	} else /* parent process; fork_rtn contains pid of child process */
	{
		wait_rtn = waitpid(fork_rtn, &child_status, WUNTRACED); /* waits until
		child process terminates */
		if (WIFEXITED(child_status))
		{
			wexitstat = WEXITSTATUS(child_status);
			return (wexitstat);
		}
		else if (wait_rtn == -1)
		{
			return (-1); /* indicate error */
		}
	}
	return (0); /* success */
}
