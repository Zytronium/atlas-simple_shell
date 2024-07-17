#include <malloc.h>
#include "main.h"

int main(void)
{
	char input[1024]; /* user input */
	pid_t fork_rtn, wait_rtn; /* return values of fork_rtn; also counts as process IDs */
	int exec_rtn = 0; /* return value of execve; default to 0 */
	int child_status;

	printf("Enter a string: ");
	scanf("%s", &input);
	printf("You entered ");
	printf("%s\n", input);
	/* TEST */

	/* first token */
    char* tok = strtok(input, " ");

        while (tok != NULL) {
        printf(" % s\n", tok); /* prints individually - should look into how to store all values instead of print */
		/* consider counting number of words after first word to keep track of arguments for a function */
		/* if the number of arguments matches the number required for the command in the first argument: fork command and input arguments */
		/* - if not either display an error, ignore the garbage words, or something else */
		/* keep an eye out for special characters that can change the meaning */

	    tok = strtok(NULL, " "); /* NULL as an argument informs strtok to continue using previous input */
    }

	/* run user-inputed commands - skeleton version */
	fork_rtn = fork();
	if (fork_rtn < 0) /* fork failed */
	{
		perror("fork failed");
		exit(EXIT_FAILURE); /* consider changing exits to continues to return to the user input */
	}
	else if (fork_rtn == 0) /* child */
	{
		exec_rtn = (tok[0], args, paths);
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
			perror("waiting failed");
			exit(EXIT_FAILURE);
		}
	}

	return (0);
}
