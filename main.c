#include "main.h"
#include "colors.h"

int main(int argc, char *argv[])
{
	/* ------------------- On entry - one time execution ------------------- */
	(void) argc;
	/*setenv("PATH", "", 1);*/
	if (stylePrints)
		printf("%sWelcome to the %sGates Of Shell%s. Type \"help\" for a list of "
		   "commands. Type \"exit\" to quit.\n\n",
		   CLR_YELLOW_BOLD, CLR_RED_BOLD, CLR_YELLOW_BOLD);
	/* --------------------------------------------------------------------- */

	shellLoop(argv); /* main shell loop. (what else?) */

	/* ------------------- On exit - one time execution ------------------- */
	if (stylePrints)
		printf("%s\nThe %sGates Of Shell%s have closed. Goodbye.\n%s",
		   CLR_YELLOW_BOLD, CLR_RED_BOLD, CLR_YELLOW_BOLD, CLR_DEFAULT);

	return (EXIT_SUCCESS);
	/* -------------------------------------------------------------------- */
}
