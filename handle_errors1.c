#include "shell.h"

/**
 *_string_to_int - converts a string character to an integer
 *@s: the input string character
 *Return: 0, -1 or converted string
 */
int _string_to_int(char *s)
{
	int i = 0;
	unsigned long int output = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			output *= 10;
			output += (s[i] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (output);
}

/**
 *error_printer - displays an error message
 *@args: the command arguments
 *@estr: the specific error type
 *Return: 0, number of string, -1
 */
void error_printer(info_type *args, char *estr)
{
	print_input(args->file_name);
	print_input(": ");
	_print_decimal(args->line_number, STDERR_FILENO);
	print_input(": ");
	print_input(args->argv[0]);
	print_input(": ");
	print_input(estr);
}

/**
 *_print_decimal - prints a decimal number
 *@input: the input
 *@fd: the filedescriptor to use for the print
 *Return: the number of characters it prints
 */
int _print_decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, total = 0;
	unsigned int absolute, cur;

	if (fd == STDERR_FILENO)
		__putchar = print_standard_error;
	if (input < 0)
	{
		absolute = -input;
		__putchar('-');
		total++;
	}
	else
		absolute = input;
	cur = absolute;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute / i)
		{
			__putchar('0' + cur / i);
			total++;
		}

		cur %= i;
	}

	__putchar('0' + cur);
	total++;

	return (total);
}

/**
 *number_converter - converts a number
 *@num: number to convert
 *@base: the desired base
 *@flags: the conversion flasg
 *Return: the converted string
 */
char *number_converter(long int num, int base, int flags)
{
	static char *holder;
	static char buffer[50];
	char sign = 0;
	char *output;
	unsigned long n = num;

	if (!(flags & UNSIGNED_INT_CONVERSION_FLAG) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	holder = flags & LOWERCASE_CONVERSION_FLAG ?
		"0123456789abcdef" : "0123456789ABCDEF";
	output = &buffer[49];
	*output = '\0';

	do {
		*--output = holder[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*
		--output = sign;
	return (output);
}

/**
 *clear_comment - replace # with '\0'
 *@buf: address of the string to modify
 *Return: 0
 */
void clear_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
