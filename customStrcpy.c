#include <stddef.h>
/**
 * custom_strcpy - function
 * @dest: destination
 * @src: source
 * Return: void
 */
void custom_strcpy(char *dest, const char *src)
{
	size_t i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
