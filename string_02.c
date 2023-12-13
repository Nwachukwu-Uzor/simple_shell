#include "shell.h"

/**
 *_strcpy - copy the content of a string
 *@_dest: the destination
 *@src: the source
 *
 *Return: pointer to destination
 */
char *_strcpy(char *_dest, char *src)
{
	int count = 0;

	if (_dest == src || src == 0)
		return (_dest);
	while (src[count])
	{
		_dest[count] = src[count];
		count++;
	}

	_dest[count] = 0;
	return (_dest);
}

/**
 *_strdup - a function that duplicates a string
 *@_str: the string to be duplicated
 *
 *Return: pointer to the duplicated string
 */
char *_strdup(const char *_str)
{
	int _len = 0;
	char *result;

	if (_str == NULL)
		return (NULL);
	while (*_str++)
		_len++;
	result = malloc(sizeof(char) *(_len + 1));
	if (!result)
		return (NULL);
	for (_len++; _len--;)
		result[_len] = *--_str;
	return (result);
}

/**
 *_puts - prints an input string
 *@_str: the string to be printed
 *
 *Return: Nothing
 */
void _puts(char *_str)
{
	int count = 0;

	if (!_str)
		return;
	while (_str[count] != '\0')
	{
		_putchar(_str[count]);
		count++;
	}
}

/**
 *_putchar - writes the character to standard output
 *@c: The character
 *
 *Return: Upon success 1, else -1 is returned, and errno is set
 */
int _putchar(char c)
{
	static int count;
	static char _buff[MAX_BUFFER_WRITE_SIZE];

	if (c == BUFFER_FLUSH_STATUS || count >= MAX_BUFFER_WRITE_SIZE)
	{
		write(1, _buff, count);
		count = 0;
	}

	if (c != BUFFER_FLUSH_STATUS)
		_buff[count++] = c;
	return (1);
}
