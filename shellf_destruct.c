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
	/*char *paths[1] = {NULL};
	char *sleepcmd = "/usr/bin/sleep";
	char **sleep1args = malloc(sizeof(char *) * 2);
	char **sleep2args = malloc(sizeof(char *) * 2);

	sleep1args[0] = sleepcmd;
	sleep2args[0] = sleepcmd;
	sleep1args[1] = "1";
	sleep2args[1] = "2";*/

	printf("Segmentation fault\n");
	sleep(1);
	/*execve(sleepcmd, sleep1args, NULL);*/ /* sys call to sleep for 1 sec */
	printf(CLR_RED_BOLD); /* sets the text color to red */
	printf("Shellf destruct mode activated.\n\n");
	if (countdown > 3)
		printf(CLR_DEFAULT); /* reset color */

	sleep(2);
	/*execve(sleepcmd, sleep2args, NULL);*/ /* sys call to sleep for 2 secs */

	while (countdown) /* prints countdown. */
	{
		if (countdown == 3)
			printf(CLR_RED); /* sets the text color to red */

		printf("%d\n", countdown);
		countdown--;
		sleep(1);
		/*execve(sleepcmd, sleep1args, NULL);*/ /* 1 second wait */
	}

	printf("%s\nThe %sGates Of Shell%s have closed. Goodbye.\n%s",
		   CLR_YELLOW_BOLD, CLR_RED_BOLD, CLR_YELLOW_BOLD, CLR_DEFAULT);

	/*free(sleep1args);
	free(sleep2args);*/

	exit(EXIT_SUCCESS);
}
