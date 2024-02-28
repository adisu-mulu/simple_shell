#include <stddef.h>
/**
 * custom_strlen - functions
 * @str: character pointer
 * Return: length
 */
size_t custom_strlen(const char *str)
{
	size_t length = 0;

	while (*str != '\0')
	{
		++length;
		++str;
	}
	return (length);
}
