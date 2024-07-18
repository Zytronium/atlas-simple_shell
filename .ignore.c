#include "main.h"

void primary(void)
{
	int countdown = 5;
	printf("Segmentation fault: Success\n");
	sleep(1);
	fprintf(stderr, "Self destruct mode activated.\n\n");
	sleep(2);
	while (countdown)
	{
		fprintf((countdown > 2) ? stdout : stderr, "%d\n", countdown--);
		sleep(1);
	}
	/*exit((int) (((unsigned int) -1) / 2) + 1);*/

	fprintf(stdout, "Self destruct mode aborted.\n");
}
