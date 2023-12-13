#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination to copy to
 *@src: the source to copy from
 *@n: the number of characters to copy
 *Return: the copied string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *output = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}

	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}

	return (output);
}

/**
 **_strncat - merges two string
 *@dest: the first parameter
 *@src: the second parameter
 *@n: the amount of bytes to use
 *Return: the combined string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *output = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	if (j < n)
		dest[i] = '\0';
	return (output);
}

/**
 **_strchr - finds a character in a string
 *@s: the string to check
 *@c: the search character
 *Return: the search character
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
