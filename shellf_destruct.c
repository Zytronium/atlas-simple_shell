#include "main.h"
#include "colors.h"

/**
 * selfDestruct - a fun way of slowly exiting the shell with a
 * self-destruct sequence. Prints a fake segmentation fault,
 * counts down from the given number, and exits.
 *
 * @countdown: the number of seconds to count down from before exiting.
 */
void selfDestruct(int countdown)
{
	printf("Segmentation fault\n");
	system("sleep 1");
	printf(CLR_RED_BOLD); /* sets the text color to red */
	printf("Shellf destruct mode activated.\n\n");
	if (countdown > 3)
		printf(CLR_DEFAULT); /* reset color */
	system("sleep 2");

	while (countdown) /* prints countdown. */
	{
		if (countdown == 3)
			printf(CLR_RED); /* sets the text color to red */

		printf("%d\n", countdown);
		countdown--;
		system("sleep 1"); /* 1 second wait */
	}

	printf("%s\nThe %sGates Of Shell%s have closed. Goodbye.\n",
		   CLR_YELLOW_BOLD, CLR_RED_BOLD, CLR_YELLOW_BOLD);

	exit(EXIT_SUCCESS);
}
