#include "main.h"
#include <stdlib.h>

/**
 * shellLoop - main loop for input/output
 *
 * @param1:
 *
 * Return: 0 (success)
 */
int shellLoop(void)
{
	char *input; /* user input */
	size_t *__restrict size;
	pid_t fork_rtn;

	printf("Welcome to the Gates Of Shell. Type \"help\" for a list of commands.\n\n"); /* only say once. (added touch, not required) */

	/* get & save input */
	printf("%s $ ", path);
	getline(&input, size, stdin);
	printf("You entered ");
	printf("%s\n", input);

	/* parse the input */

	/* print any output (maybe)? */

	/* return -1 on error? | while loop or recursive function? */
	return (EXIT_SUCCESS);
}
