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
#include <sys/types.h>
#include "colors.h"
/* ------------------- */

/* ↓ STRUCTS AND MISC ↓ */
#ifndef stylePrints
#define stylePrints 0
/* set to 0 for checker, set to 1 to prettify shell */
/*
 * Note to Stephen: in every case, 1 means TRUE and 0 means FALSE. It's just like
 * simple binary code: 0 is 0ff, 1 is on. 0 is nothing, 0%, and
 * 1 is everything, 100%. The only exception is EXIT_SUCCESS == 0 and
 * EXIT_FAILURE == 1, but that's probably because I heard it's faster
 * to check if a number is 0 than to check if it's 1, which is why
 * old code used to actually loop counting down to 0 instead of up,
 * because it was a micro-optimization that most compilers today probably
 * take care of for you. When you're checking an int used as a boolean value
 * (1 or 0), instead of as a number value, I believe it's best to do
 * "if (stylePrints)" instead of "if (stylePrints == 1)." I hope this helps.
 *
 * TLDR:
 *
 * 0: false;	off;	0%; 	nothing
 * 1: true; 	on; 	100%;	everything
 *
 * TODO: Remove this note before Tuesday.
 */
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

void saveInput(int isAtty, char **tokens, size_t *size, char **input);

int parseInput(char *input, char ***tokens, char **cmd_token, int *tokens_count);

void executeIfValid(int isAtty, char *const *argv, char *input, char **tokens,
					char *cmd, char *cmd_token, char **paths);

void initCmd(char **cmd, char *const *tokens);

int populateTokens(const char *input, char ***tokens, char **cmd_token,
				   int *tokens_count);

void freeAll(char **tokens, ...);

void ifCmdExit(char **tokens, int interactive, const char *f1, const char *f2,
			   const char *f3);

int ifCmdSelfDestruct(char **tokens, const char *f1, const char *f2,
					  const char *f3);
int customCmd(char **tokens, int interactive, char *f1, char *f2, char *f3);

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

int ifCmdEnv(char **tokens);
/* ------------------- */

#endif /* MAIN_H */
