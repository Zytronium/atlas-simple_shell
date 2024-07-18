#include "main.h"
#include "colors.h"

int main(void)
{
	/* ------------------- On entry - one time execution ------------------- */
	printf("%sWelcome to the %sGates Of Shell%s. Type \"help\" for a list of "
		   "commands. Type \"exit\" to quit.\n\n",
		   SET_CLR_YELLOW_BOLD, SET_CLR_RED_BOLD, SET_CLR_YELLOW_BOLD);
	/* --------------------------------------------------------------------- */

	shellLoop(); /* main shell loop. (what else?) */

	/* ------------------- On exit - one time execution ------------------- */
	return (EXIT_SUCCESS);
	/* -------------------------------------------------------------------- */
}
