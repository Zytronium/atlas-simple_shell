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
		return (NULL);
	while (temp != NULL)
	{
		temp_path = malloc(strlen(temp->directory) + strlen(name) + 2);
		strcpy(temp_path, temp->directory);
		strcat(temp_path, "/");
		strcat(temp_path, name);
		if (access(temp_path, F_OK) == 0)
		{
			destroyListPath(head);
			return (temp_path);
		}
		free(temp_path);
		temp = temp->next;
	}
	destroyListPath(head);
	temp_path = strdup(name);
	return (temp_path);
}
/**
 * destroyListPath - frees the ListPath
 * @h: head of listpath
 */
void destroyListPath(path_t *h)
{
	path_t *temp = NULL;
	while (h != NULL)
	{
		temp = h;
		h = h->next;
		free(temp->directory);
		free(temp);
	}
}
/**
 * getHostname - retrieves hostname from env or sets a new hostname
 *
 * Return: hostname
 */
char *getHostname(void)
{
	char *hostname = _getenv("NAME");

	if (!hostname)
		hostname = _getenv("HOSTNAME");
	if (!hostname)
		hostname = _getenv(("WSL_DISTRO_NAME"));
	if (!hostname)
	{
		hostname = malloc(8);
		strcpy(hostname, "unknown");
	}

	return (hostname);
}

/**
 * getUser - retrives user from env or sets a new user
 *
 * Return: user
 */
char *getUser(void)
{
	char *user = _getenv("USER");

	if(!user)
		user = _getenv("LOGNAME");
	if (!user)
	{
		user = malloc(8);
		strcpy(user, "unknown");
	}

	return (user);
}

/**
 * ifCmdUnsetEnv - unsets an env variable if found
 * @tokens: tokenized list of commands
 *
 * Return: 1 if successful, otherwise 0
 */
int ifCmdUnsetEnv(char **tokens)
{
	if (tokens[0] != NULL && (strcmp(tokens[0], "unsetenv") == 0))
	{
		if (_unsetenv(tokens[1]) == 0)
			return (1);
	}
	return (0);
}
