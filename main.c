#include "main.h"
#include "colors.h"

int main(void)
{
	/* ------------------- On entry - one time execution ------------------- */
	printf("%sWelcome to the %sGates Of Shell%s. Type \"help\" for a list of "
		   "commands. Type \"exit\" to quit.\n\n",
		   CLR_YELLOW_BOLD, CLR_RED_BOLD, CLR_YELLOW_BOLD);
	/* --------------------------------------------------------------------- */

	shellLoop(); /* main shell loop. (what else?) */

	printf(CLR_DEFAULT); /* reset output text color */
	/* ------------------- On exit - one time execution ------------------- */
	return (EXIT_SUCCESS);
	/* -------------------------------------------------------------------- */
}
