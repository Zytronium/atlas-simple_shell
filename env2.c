#include "main.h"

/**
 * findPath - finds the path of a given command
 * @name: name of command
 *
 * Return: path if found, name if not found
 */
char *findPath(char *name)
{
	path_t *temp = NULL;
	path_t *head = NULL;
	char *temp_path;

	head = buildListPath();
	temp = head;
	if (temp == NULL)
	{
		return (NULL);
	}
	while (temp != NULL)
	{
		temp_path = malloc(strlen(temp->directory) + strlen(name) + 2);
		strcpy(temp_path, temp->directory);
		strcat(temp_path, "/");
		strcat(temp_path, name);
		/* printf("temp_path: %s\n", temp_path); */
		if (access(temp_path, F_OK) == 0)
		{
			/* printf("findpath A\n"); */
			destroyListPath(head);
			/* printf("findpath B\n"); */
			return (temp_path);
		}
		free(temp_path);
		temp = temp->next;
	}
	destroyListPath(head);
	temp_path = strdup(name);
	return (temp_path);
}

void destroyListPath(path_t *h)
{
	path_t *temp = NULL;
	/* printf("destroyListPath A\n"); */
	while (h != NULL)
	{
		temp = h;
		h = h->next;
		free(temp->directory);
		free(temp);
		/* printf("destroyListPath B\n"); */
	}
	/* printf("destroyListPath C\n"); */
}