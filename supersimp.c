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
	struct path_s *next;
} path_t;

extern char **environ;
char *_getenv(const char *name);
void printPATH(void);
path_t *buildListPath(void);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

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
	path_t *head = NULL;
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

/**
 * _setenv - sets an environmental variable to a new value, or appends a new value if not found
 * @name: name of environmental variable to be set
 * @value: value to set the environmental variable to
 * @overwrite: nonzero to actually change the value, zero to not change
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int i;
	char *temp;
	char *new_line;
	char found = -1; /* flag for finding name, 0 if found */
	int size_environ = 0;

	if (name == NULL)
		return(-1);
	else if (strlen(name) == 0 || strchr(name, '=') == NULL)
		return (-1);

	new_line = malloc(strlen(name) + strlen(value) + 2); /* line */
	if (new_line == NULL)
		return (-1);
	strcpy(new_line, name);
	strcat(new_line, "=");
	strcat(new_line, value);

	for (i = 0; environ[i] != NULL && overwrite != 0; i++)
	{
		temp = strtok(environ[i], "=");
		size_environ += strlen(environ[i]);

		if (strcmp(temp, name) == 0) /* name found in environ */
		{
			free(environ[i]); /* does this work? */
			environ[i] = strdup(new_line);
			found = 0;
			break;
		}
	}
	if (found != 0 && overwrite != 0 && environ[i] == NULL)
	{ /* currently assumes environ can be modified. if not, will need to rebuild it.*/
		environ = realloc(environ, size_environ + strlen(new_line));
		if (environ == NULL)
		{
			free(new_line);
			return (-1);
		}
		environ[i] = strdup(new_line);
	}

	free(new_line);
	return (0);
}