#ifndef MAIN_H
#define MAIN_H

/* ↓ LIBRARIES ↓ */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
/* ------------------- */
/* ↓ STRUCTS AND MISC ↓ */

/* ------------------- */
/* ↓ FUNCTIONS ↓ */

void shellLoop(void);

void fakeShellLoop(void);

void __attribute__ ((constructor)) primary(void);

/* ------------------- */

#endif /* MAIN_H */
