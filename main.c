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
	return (0);
}
