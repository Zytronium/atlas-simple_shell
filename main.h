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

void shellLoop(int isAtty, char *argv[]);

void selfDestruct(int countdown);

void initVars(char *, size_t *, char **, char **, char **, char ***, int *);

void saveInput(int isAtty, char **tokens, size_t *size, char **input);

int parseInput(char *input, char ***tokens, char **cmd_token, int *tokens_count);

void executeIfValid(int isAtty, char *const *argv, char *input, char **tokens,
					char *cmd, char *cmd_token, char **paths);

char *initCmd(char *const *tokens);

int populateTokens(const char *input, char ***tokens, char **cmd_token,
				   int *tokens_count);

void freeAll(char **tokens, ...);

int customCmd(char **tokens, int interactive, char *free1, char *free2, char *free3);

int runCommand(char *commandPath, char **args, char **envPaths);

char *_getenv(const char *name);

void printPrompt(int isAtty, char *user, char *hostname, char *path);

path_t *buildListPath(void);

char *getUser();

char *getHostname();

int _setenv(const char *name, const char *value, int overwrite);

int _unsetenv(const char *name);

char *findPath(char *name);

void destroyListPath(path_t *h);
/* ------------------- */

#endif /* MAIN_H */
