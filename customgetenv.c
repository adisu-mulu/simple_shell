#include <stddef.h>
#include <stdlib.h>
#include "main.h"
#include <stdio.h>
#include <string.h>
/**
 * custom_getenv - function
 * @name: character pointer
 * Return: value on success, NULL on failure
 */

char *custom_getenv(const char *name)
{
	size_t len = custom_strlen(name);
	extern char **environ;
	char **env = environ;

	while (*env != NULL)
	{
		if (strncmp(*env, name, len) == 0 && (*env)[len] == '=')
		{
			return &((*env)[len + 1]);
		}
		env++;
	}
	return (NULL);
}
