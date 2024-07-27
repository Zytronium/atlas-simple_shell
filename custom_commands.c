#include "main.h"

/**
 * customCmd - checks if the given input is a custom command. If so, executes it
 *
 * @tokens: tokens.
 * @interactive: if the shell is running in interactive mode (isAtty)
 * @f1: variable to be freed if the command exits. (i.e. input)
 * @f2: variable to be freed if the command exits. (i.e. cmd)
 * @f3: variable to be freed if the command exits. (i.e. cmd_token)
 *
 * Return: 1 if it was a custom command and it was successfully executed,
 * 0 if it's not a custom command,
 * -1 on error
 */
 int customCmd(char **tokens, int interactive, char *f1, char *f2, char *f3)
 {
	 /* ------------------ custom command "env" ------------------ */
	 if (ifCmdEnv(tokens))
		 return (1);

	 /* ----------------- custom command "exit" ----------------- */
	 ifCmdExit(tokens, interactive, f1, f2, f3);

	 /* ------------- custom command "self-destruct" ------------- */
	 if (ifCmdSelfDestruct(tokens, f1, f2, f3) == -1)
		 return (-1);

	 return (0); /* indicate that the input is not a custom command */
 }
/*
 * note: customCmd() was variadic, but we undid that because of
 * problems calling freeAll() using the args variable.
 */

/**
 * ifCmdSelfDestruct - self destruct oscar mike golf
 * @tokens: tokenized array of user-inputs
 * @f1: variable to be freed if the command exits. (i.e. input)
 * @f2: variable to be freed if the command exits. (i.e. cmd)
 * @f3: variable to be freed if the command exits. (i.e. cmd_token)
 * Return: 0 if successful, -1 otherwise
 */
 int ifCmdSelfDestruct(char **tokens, const char *f1, const char *f2,
					   const char *f3)
 {
	 if (tokens[0] != NULL && (strcmp(tokens[0], "self-destruct") == 0 ||
							   strcmp(tokens[0], "selfdestr") == 0))
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
		 freeAll(tokens, f1, f2, f3, NULL);
		 selfDestruct(countdown); /* runs exit() when done */
		 return (-1); /* indicate error if selfDestruct never exits */
		 /* TODO: should we handle the condition if the cmd has too many args? */
	 }
	 return (0);
 }

/**
 * ifCmdExit: if user-input is "exit" or "quit"
 * @tokens: tokenized array of user-inputs
 * @interactive: isatty() return value. 1 if interactive, 0 otherwise
 * @f1: variable to be freed if the command exits. (i.e. input)
 * @f2: variable to be freed if the command exits. (i.e. cmd)
 * @f3: variable to be freed if the command exits. (i.e. cmd_token)
 */
 void ifCmdExit(char **tokens, int interactive, const char *f1, const char *f2,
				const char *f3)
 {
	 if (tokens[0] != NULL &&
		 (strcmp(tokens[0], "exit") == 0 || strcmp(tokens[0], "quit") == 0))
	 {
		 freeAll(tokens, f1, f2, f3, NULL);

		 if (interactive && stylePrints)
			 printf("%s\nThe %sGates Of Shell%s have closed. Goodbye.\n%s",
					CLR_YELLOW_BOLD, CLR_RED_BOLD, CLR_YELLOW_BOLD, CLR_DEFAULT);

		 exit(EXIT_SUCCESS);
	 }
 }

int ifCmdEnv(char **tokens)
{
	int i;

	if (tokens[0] != NULL && (strcmp(tokens[0], "env") == 0))
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);

		return (1); /* indicate success */
	}
	return (0); /* indicate that input is not "env" */
}
