#include <malloc.h>
#include "main.h"
#include "shell_loop.c"

int main(void)
{
	printf("Welcome to the Gates Of Shell. Type \"help\" for a list of commands.\n\n"); /* only say once. (added touch, not required) */

	shellLoop();

	return (EXIT_SUCCESS);
}
