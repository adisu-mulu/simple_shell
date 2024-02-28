#include <stddef.h>
#include<stdlib.h>
#include "main.h"
/**
 * custom_strdup - function
 * @str: character pointer
 * Return: copy
 */
char *custom_strdup(const char *str)
{
	size_t len = custom_strlen(str) + 1;
	char *copy = (char *)malloc(len);

	if (copy != NULL)
	{
		custom_strcpy(copy, str);
	}
	return (copy);
}
