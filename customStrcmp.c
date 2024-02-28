#include <stddef.h>
/**
 * custom_strcmp - function
 * @str1: character pointer
 * @str2: character pointer
 * Return: 1
 */
int custom_strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
	{
		++str1;
		++str2;
	}
	if (*str1 == *str2)
	{
		return (0);
	}
	else if (*str1 < *str2)
	{
		return (-1);
	}
	else
	{
		return (1);
	}
}
