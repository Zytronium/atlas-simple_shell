#include "main.h"

/**
 * main - starts the program and the loop
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0
 */
int main(int argc, char *argv[])
{
	int isInteractive = isatty(STDIN_FILENO);

	/* ------------------- On entry - one time execution ------------------- */
	(void) argc;
	/* if argc == 1, meaning no args given, meaning it's in interactive mode */
	if (isInteractive && stylePrints == 1)
		printf("%sWelcome to the %sGates Of Shell%s. Type 'exit' to quit.\n\n",
			   CLR_YELLOW_BOLD, CLR_RED_BOLD, CLR_YELLOW_BOLD);
	/* --------------------------------------------------------------------- */

	shellLoop(isInteractive, argv); /* main shell loop */

	/* ------------------- On exit - one time execution ------------------- */
	if (isInteractive && stylePrints == 1)
		printf("%s\nThe %sGates Of Shell%s have closed. Goodbye.\n%s",
		   CLR_YELLOW_BOLD, CLR_RED_BOLD, CLR_YELLOW_BOLD, CLR_DEFAULT);

	return (EXIT_SUCCESS);
	/* -------------------------------------------------------------------- */
	/*
	 * note: 'On exit' code will probably never run unless something goes wrong.
	 * TODO: We should consider returning EXIT_FAILURE
	 *  or using break instead of exit(EXIT_SUCCESS)
	 */
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
