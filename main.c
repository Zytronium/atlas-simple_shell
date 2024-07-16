#include <stdio.h>
#include <malloc.h>

int main(void)
{
	char *num = malloc(sizeof(char) * (unsigned) -1); /* allocate OVER 4 GB OF MEMORY AAAAA*/

	printf("Enter a string: ");
	scanf("%s", &num);
	printf("You entered: %s\n", num);
	/* TEST */
	free(num);
	/* snewby changes */
	/* branch change? */
	return (0);
}
