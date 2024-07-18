#include "main.h"

int main(void)
{
	printf("Welcome to the Gates Of Shell. Type \"help\" for a list of commands. Type \"quit\" to exit.\n\n"); /* only say once. (added touch, not required) */

	shellLoop();

	return (EXIT_SUCCESS);
}

/*
void fakeShellLoop(void)
{
	char *input, path[PATH_MAX]; *//* user input *//*

	size_t size = 0;

	if (getcwd(path, sizeof(path)) != NULL)
	{
		printf("%s$ ", path);
	}
	getline(&input, &size, stdin);

	system(input);

	fakeShellLoop();
}
*/
