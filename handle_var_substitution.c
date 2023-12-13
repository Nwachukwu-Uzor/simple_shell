#include "shell.h"

/**
 *check_chain_delimeter - check we are using a chain delimiter
 *@args: the command line arguments
 *@buf: the buffer to be checked
 *@p: the address of the buffer
 *Return: 1 if successful, 0 otherwise
 */
int check_chain_delimeter(info_type *args, char *buf, size_t *p)
{
	size_t size = *p;

	if (buf[size] == '|' && buf[size + 1] == '|')
	{
		buf[size] = 0;
		size++;
		args->cmd_buffer_type = CHAIN_OR;
	}
	else if (buf[size] == '&' && buf[size + 1] == '&')
	{
		buf[size] = 0;
		size++;
		args->cmd_buffer_type = CHAIN_AND;
	}
	else if (buf[size] == ';')
	{
		buf[size] = 0;
		args->cmd_buffer_type = CHAIN_CMD;
	}
	else
		return (0);
	*p = size;
	return (1);
}

/**
 *check_chain - checks if we should chain a command
 *@args: the command line arguments
 *@buf: the character buffer
 *@p: the current buffer position
 *@i: the start index of buffer
 *@len: the size of the buffer
 *Return: Void
 */
void check_chain(info_type *args, char *buf, size_t *p, size_t i, size_t len)
{
	size_t size = *p;

	if (args->cmd_buffer_type == CHAIN_AND)
	{
		if (args->status)
		{
			buf[i] = 0;
			size = len;
		}
	}

	if (args->cmd_buffer_type == CHAIN_OR)
	{
		if (!args->status)
		{
			buf[i] = 0;
			size = len;
		}
	}

	*p = size;
}

/**
 *substitute_alias - substitutes an alias
 *@args: the command line arguments
 *Return: 1 if substituted, 0 otherwise
 */
int substitute_alias(info_type *args)
{
	int i;
	list_type *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_start_prefix(args->alias, args->argv[0], '=');
		if (!node)
			return (0);
		free(args->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		args->argv[0] = p;
	}

	return (1);
}

/**
 *substitute_vars - replaces command line variables
 *@args: the command line arguments
 *
 *Return: 1 if replaced, 0 otherwise
 */
int substitute_vars(info_type *args)
{
	int i = 0;
	list_type *node;

	for (i = 0; args->argv[i]; i++)
	{
		if (args->argv[i][0] != '$' || !args->argv[i][1])
			continue;

		if (!_strcmp(args->argv[i], "$?"))
		{
			substitute_string(&(args->argv[i]),
				_strdup(number_converter(args->status, 10, 0)));
			continue;
		}

		if (!_strcmp(args->argv[i], "$$"))
		{
			substitute_string(&(args->argv[i]),
				_strdup(number_converter(getpid(), 10, 0)));
			continue;
		}

		node = node_start_prefix(args->env, &args->argv[i][1], '=');
		if (node)
		{
			substitute_string(&(args->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}

		substitute_string(&args->argv[i], _strdup(""));
	}

	return (0);
}

/**
 *substitute_string - replaces a string
 *@old: the pointer to the address of the old string
 *@new: the pointer to the new string
 *
 *Return: 1 if replaced, 0 otherwise
 */
int substitute_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
