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
#include <stdarg.h>
/* ------------------- */

/* ↓ STRUCTS AND MISC ↓ */
#ifndef stylePrints
#define stylePrints 0
/* set to 0 for checker, set to 1 to prettify shell */
#endif /* stylePrints */
/* ------------------- */

/* ↓ FUNCTIONS ↓ */
int isNumber(char *number);

void shellLoop(char *argv[]);

void selfDestruct(int countdown);

void freeAll(char **tokens, ...);

int customCmd(char **tokens, char *input, char *cmd);

int runCommand(char *commandPath, char **args, char **envPaths, char *argv[]);
/* ------------------- */

#endif /* MAIN_H */
