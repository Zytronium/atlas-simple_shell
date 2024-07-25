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
/**
 * struct path_s - singly linked list for PATH environ variable
 * @directory: string of directory
 * @next: next location directory
 *
 * Description: singly linked list node structure
 */
typedef struct path_s
{
	char *directory;
	struct path_s *next;
} path_t;
extern char **environ;
/* ------------------- */

/* ↓ FUNCTIONS ↓ */

int isNumber(char *number);

void shellLoop(int argc, char *argv[]);

void selfDestruct(int countdown);

void freeAll(char **tokens, ...);

int customCmd(char **tokens, int interactive, ...);

int runCommand(char *commandPath, char **args, char **envPaths);

char *_getenv(const char *name);

void printPATH(void);

path_t *buildListPath(void);

int _setenv(const char *name, const char *value, int overwrite);

int _unsetenv(const char *name);

char *findPath(char *name);

void destroyListPath(path_t *h);
/* ------------------- */

#endif /* MAIN_H */
