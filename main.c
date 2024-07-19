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

	/* ------------------- On exit - one time execution ------------------- */
	printf(CLR_DEFAULT); /* reset output text color */
	return (EXIT_SUCCESS);
	/* -------------------------------------------------------------------- */
}
