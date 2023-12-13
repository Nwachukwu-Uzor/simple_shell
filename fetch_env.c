#include "shell.h"

/**
 *get_environment_variables - displays a copy of the environment variables
 *@args: the command line arguments
 *Return: 0
 */
char **get_environment_variables(info_type *args)
{
	if (!args->environ || args->environment_change)
	{
		args->environ = print_list_string(args->env);
		args->environment_change = 0;
	}

	return (args->environ);
}

/**
 *_remove_set_env - clears the environment variables
 *@args: the command line arguments
 *Return: 1 if deleted, 0 otherwise
 *@var: the string var character
 */
int _remove_set_env(info_type *args, char *
	var)
{
	list_type *node = args->env;
	size_t size = 0;
	char *pointer;

	if (!node || !
		var)
		return (0);

	while (node)
	{
		pointer = starts_with(node->str,
			var);
		if (pointer && *pointer == '=')
		{
			args->environment_change = remove_node_at_index(&(args->env), size);
			size = 0;
			node = args->env;
			continue;
		}

		node = node->next;
		size++;
	}

	return (args->environment_change);
}

/**
 *_add_new_env - initializes or modifies the environment
 *@args: the command line arguments
 *@var: the string env var property
 *@value: the string value of the string env property
 *Return: 0
 */
int _add_new_env(info_type *args, char *
	var, char *value)
{
	char *buf = NULL;
	list_type *node;
	char *pointer;

	if (!
		var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf,
		var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = args->env;
	while (node)
	{
		pointer = starts_with(node->str,
			var);
		if (pointer && *pointer == '=')
		{
			free(node->str);
			node->str = buf;
			args->environment_change = 1;
			return (0);
		}

		node = node->next;
	}

	append_node(&(args->env), buf, 0);
	free(buf);
	args->environment_change = 1;
	return (0);
}
