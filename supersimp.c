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
typedef struct path_s {
	char *directory;
	//unsigned int len;
	struct node_s *next;
} path_t;

extern char **environ;
char *_getenv(const char *name);
void printPATH(void);
path_t *buildListPath(void);

int main(int argc, char *argv[], char **env)
{
	for (size_t i = 0; environ[i] != NULL; i++)
	{
		printf("environ: %s\n", environ[i]);
		//printf("env    : %s\n", env[i]);
	}

	if (argc > 0)
		printf("\n%s\n", getenv((const char *)argv[1]));
	printPATH();
	path_t *pathList = buildListPath();
	return 0;
}

char *getenv(const char *name)//gets an environmental variable
{
	char **current = environ;
	char *token;

    for (; *current; current++)
	{
        token = strtok(*current, "=");
        if (token && strcmp(token, name) == 0)
            return strtok(NULL, "=");
    }
    return NULL;
}

void printPATH()
{
	char *path = getenv("PATH");
	char *token = strtok(path,":");
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, ":");
	}
	//printf("%s\n",path);
}

path_t *buildListPath(void)
{
	path_t *new_node = NULL;
	path_t *head;
	char *path = getenv("PATH");
	char *token = strtok(path, ":");

	while (token != NULL)
	{
		new_node = (path_t *)malloc(sizeof(path_t));
		if (new_node == NULL)
			return(NULL);
		new_node->directory = token;
		new_node->next = head;
		head = new_node;
		token = strtok(NULL, ":");
	}
	return (head);
}