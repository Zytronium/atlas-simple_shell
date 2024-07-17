#include "main.h"

int main(void)
{
	shellLoop();

	/* first token */
    char* tok = strtok(input, " ");

        while (tok != NULL) {
        printf(" %s\n", tok); /* prints individually - should look into how to store all values instead of print */
		/* consider counting number of words after first word to keep track of arguments for a function */
		/* if the number of arguments matches the number required for the command in the first argument: fork command and input arguments */
		/* - if not either display an error, ignore the garbage words, or something else */
		/* keep an eye out for special characters that can change the meaning */

	    tok = strtok(NULL, " "); /* NULL as an argument informs strtok to continue using previous input */
    }

	/* run user-inputed commands - skeleton version */
//	fork_rtn = fork();
	if (fork_rtn == 0) /* child */
	{

//		execve();
	}
	else if (fork_rtn < 0) /* fork failed */
		perror("fork failed");
	else /* parent; fork_rtn contains pid of child process */
	{
//		wait(); /* waits until child process completes */
}

return (0);
}
