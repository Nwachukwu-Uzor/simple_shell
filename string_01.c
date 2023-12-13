#include "shell.h"

/**
 *_strlen - a function that returns the length of a string
 *@_str: the string whose to be checked
 *
 *Return: length of the string
 */
int _strlen(char *_str)
{
	int i = 0;

	if (!_str)
		return (0);

	while (*_str++)
		i++;
	return (i);
}

/**
 *_strcmp - comparison of two strings.
 *@str_1: str 0ne
 *@str_2: str two
 *
 *Return: negative if str_1<str_2, positive if str_1 > str_2, zero if str_1 == str_2
 */
int _strcmp(char *str_1, char *str_2)
{
	while (*str_1 && *str_2)
	{
		if (*str_1 != *str_2)
			return (*str_1 - *str_2);
		str_1++;
		str_2++;
	}

	if (*str_1 == *str_2)
		return (0);
	else
		return (*str_1<*str_2 ? -1 : 1);
}

/**
 *starts_with - checks if _train begins with _stack
 *@_stack: the string to be searched
 *@_train: the substring to find
 *
 *Return: address of next char of _stack or NULL
 */
char *starts_with(const char *_stack, const char *_train)
{
	while (*_train)
		if (*_train++ != *_stack++)
			return (NULL);
	return ((char*) _stack);
}

/**
 *_strcat - joins two strings together
 *@_dest: the destinatn buff
 *@src: the initial buff
 *
 *Return: pointer to destinatn buff
 */
char *_strcat(char *_dest, char *src)
{
	char *result = _dest;

	while (*_dest)
		_dest++;
	while (*src)
		*
		_dest++ = *src++;
	*_dest = *src;
	return (result);
}
