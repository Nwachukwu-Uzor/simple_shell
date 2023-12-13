#include "shell.h"

/**
 *print_input - outputs the input string
 *@str: the input string
 *Return: void
 */
void print_input(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		print_standard_error(str[i]);
		i++;
	}
}

/**
 *print_standard_error - writes to the standard error
 *@ch: the character to write
 *Return: 1 on success, 0 on otherwise
 */
int print_standard_error(char ch)
{
	static int i;
	static char buf[MAX_BUFFER_WRITE_SIZE];

	if (ch == BUFFER_FLUSH_STATUS || i >= MAX_BUFFER_WRITE_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (ch != BUFFER_FLUSH_STATUS)
		buf[i++] = ch;
	return (1);
}

/**
 *_print_file_char - writes the character of file data
 *@ch: the character to be written
 *@fd: the filedescriptor to be written
 *Return: 1 on success, 0 on otherwise
 */
int _print_file_char(char ch, int fd)
{
	static int i;
	static char buf[MAX_BUFFER_WRITE_SIZE];

	if (ch == BUFFER_FLUSH_STATUS || i >= MAX_BUFFER_WRITE_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (ch != BUFFER_FLUSH_STATUS)
		buf[i++] = ch;
	return (1);
}

/**
 *_print_standard_string - displays an input string
 *@str: the string to display
 *@fd: the file descriptor for display
 *Return: number of characters written
 */
int _print_standard_string(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _print_file_char(*str++, fd);
	}

	return (i);
}
