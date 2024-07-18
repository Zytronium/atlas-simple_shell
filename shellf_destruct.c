#include "main.h"

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
	sleep(1);
	fprintf(stderr, "Shellf destruct mode activated.\n\n");
	sleep(2);

	while (countdown) /* prints countdown. */
	{ /* Prints to stdout, or to stderr if countdown is <= 3. See footnote1 */
		fprintf((countdown > 3) ? stdout : stderr, "%d\n", countdown);
		countdown--;
		sleep(1); /* 1 second wait */
	}

	fprintf(stderr, "The Gates Of Shell have closed. Goodbye.\n\n");
	exit(0);
}

/*
 * Footnotes:
 *
 * 1: prints to stderr simply because in some cases, that prints in red.
 */
