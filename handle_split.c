#include "shell.h"

/**
 ***str_tokenize - split string ignoring repeated delimiters
 *@str: the string to split
 *@d: the delimeter for splitting
 *Return: a pointer to the split string
 */

char **str_tokenize(char *str, char *d)
{
	int i, j, k, m, word_count = 0;
	char **output;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!check_delimiter(str[i], d)
		&& (check_delimiter(str[i + 1], d) || !str[i + 1]))
			word_count++;

	if (word_count == 0)
		return (NULL);
	output = malloc((1 + word_count) * sizeof(char *));
	if (!output)
		return (NULL);
	for (i = 0, j = 0; j < word_count; j++)
	{
		while (check_delimiter(str[i], d))
			i++;
		k = 0;
		while (!check_delimiter(str[i + k], d) && str[i + k])
			k++;
		output[j] = malloc((k + 1) * sizeof(char));
		if (!output[j])
		{
			for (k = 0; k < j; k++)
				free(output[k]);
			free(output);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			output[j][m] = str[i++];
		output[j][m] = 0;
	}

	output[j] = NULL;
	return (output);
}

/**
 ***str_token - split a string
 *@str: the string to split
 *@d: the delimeter for splitting
 *Return: a pointer to the split string
 */
char **str_token(char *str, char d)
{
	int i, j, k, m, word_count = 0;
	char **output;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
			(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			word_count++;
	if (word_count == 0)
		return (NULL);
	output = malloc((1 + word_count) * sizeof(char *));
	if (!output)
		return (NULL);
	for (i = 0, j = 0; j < word_count; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		output[j] = malloc((k + 1) * sizeof(char));
		if (!output[j])
		{
			for (k = 0; k < j; k++)
				free(output[k]);
			free(output);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			output[j][m] = str[i++];
		output[j][m] = 0;
	}

	output[j] = NULL;
	return (output);
}
