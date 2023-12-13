#include "shell.h"

/**
 *check_interactive - check if we are using an interactive
 *@param: address of the struct
 *Return: 1 for interactive shell, 0 otherwise
 */
int check_interactive(info_type *param)
{
	return (isatty(STDIN_FILENO) && param->readfiledata <= 2);
}

/**
 *check_delimiter - checks if an input character is a delimeter
 *@ch: the input char
 *@delimiter: the delimeter to check for
 *Return: 1 if true, 0 if false
 */
int check_delimiter(char ch, char *delimiter)
{
	while (*delimiter)
	{
		if (*delimiter++ == ch)
		{
			return (1);
		}
	}

	return (0);
}

/**
 *check_alpha - checks for if a character is an alphabet
 *@ch: the character to check
 *Return: 1 if ch is alphabetic, 0 otherwise
 */

int check_alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	{
		return (1);
	}

	return (0);
}

/**
 *_integer_convert - converts a string character to an integer
 *@ch: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _integer_convert(char *ch)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; ch[i] != '\0' && flag != 2; i++)
	{
		if (ch[i] == '-')
			sign *= -1;

		if (ch[i] >= '0' && ch[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (ch[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
