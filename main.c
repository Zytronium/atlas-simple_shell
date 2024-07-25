#include "main.h"
#include "colors.h"

int main(int argc, char *argv[])
{
	/* ------------------- On entry - one time execution ------------------- */
	/*setenv("PATH", "", 1);*/
	if (argc) /* if argc == 1, meaning args are not given, meaning it's in interactive mode */
		printf("%sWelcome to the %sGates Of Shell%s. Type \"exit\" to quit.\n\n",
		   CLR_YELLOW_BOLD, CLR_RED_BOLD, CLR_YELLOW_BOLD);
	/* --------------------------------------------------------------------- */

	shellLoop(argc, argv); /* main shell loop. (what else?) */

	/* ------------------- On exit - one time execution ------------------- */
	if (argc)
		printf("%s\nThe %sGates Of Shell%s have closed. Goodbye.\n%s",
		   CLR_YELLOW_BOLD, CLR_RED_BOLD, CLR_YELLOW_BOLD, CLR_DEFAULT);

	return (EXIT_SUCCESS);
	/* -------------------------------------------------------------------- */
	/*
	 * note: 'On exit' code will probably never run unless something goes wrong.
	 * TODO: We should consider returning EXIT_FAILURE
	 *  or using break instead of exit(EXIT_SUCCESS)
	 */
}
