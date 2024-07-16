#include <stdio.h>
#include <malloc.h>

int main(void)
{
	char *num = malloc(sizeof(char) * (unsigned) -1); /* allocate OVER 4 GB OF MEMORY AAAAA*/

	if (num == NULL)
	{
		printf("failed to allocate %u bytes of memory\n", (unsigned) -1);
		return (-1);
	}

	printf("Enter a string: ");
	scanf("%s", &num);
	printf("You entered ");
	printf("%s\n", num);
	/* TEST */
	free(num);
	/* snewby changes */
	/* branch change? */

	/* first token */
    char* tok = strtok(num, " ");

        while (tok != NULL) {
        printf(" % s\n", tok); /* prints individually - should look into how to store all values instead of print */
		/* consider counting number of words after first word to keep track of arguments for a function */
		/* if the number of arguments matches the number required for the command in the first argument: fork command and input arguments */
		/* - if not either display an error, ignore the garbage words, or something else */
		/* keep an eye out for special characters that can change the meaning */
     
	    tok = strtok(NULL, " "); /* NULL as an argument informs strtok to continue using previous input */
    }
	return (0);
}
