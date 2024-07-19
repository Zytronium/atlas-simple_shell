#ifndef MAIN_H
#define MAIN_H

/* ↓ LIBRARIES ↓ */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <linux/limits.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
/* ------------------- */

/* ↓ STRUCTS AND MISC ↓ */
/* ------------------- */

/* ↓ FUNCTIONS ↓ */
int isNumber(char *number);

void shellLoop(void);

void selfDestruct(int countdown);
/* ------------------- */

#endif /* MAIN_H */
