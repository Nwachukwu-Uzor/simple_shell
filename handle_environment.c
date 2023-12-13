#include "shell.h"

/**
 *print_my_env - list the environment variables
 *@args: the command arguments
 *Return: 0
 */
int print_my_env(info_type *args)
{
	print_string_elements(args->env);
	return (0);
}

/**
 *_get_env - finds the current environment variable
 *@args: arguments to the command
 *@env_name: the name of the environment variable
 *
 *Return: the value
 */
char *_get_env(info_type *args, const char *env_name)
{
	list_type *node = args->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, env_name);
		if (p && *p)
			return (p);
		node = node->next;
	}

	return (NULL);
}

/**
 *initialize_my_env - sets up a new environment variable
 *@args: the argument count
 *Return: Always 0
 */
int initialize_my_env(info_type *args)
{
	if (args->argc != 3)
	{
		print_input("Incorrect number of arguements\n");
		return (1);
	}

	if (_add_new_env(args, args->argv[1], args->argv[2]))
		return (0);
	return (1);
}

/**
 *_clear_environment - removes all environment variables
 *@args: the list of arguments
 *Return: 0
 */
int _clear_environment(info_type *args)
{
	int size;

	if (args->argc == 1)
	{
		print_input("Too few arguements.\n");
		return (1);
	}

	for (size = 1; size <= args->argc; size++)
		_remove_set_env(args, args->argv[size]);

	return (0);
}

/**
 *populate_environment - fills up the environment variables
 *@args: the arguments to the command
 *Return: 0
 */
int populate_environment(info_type *args)
{
	list_type *node = NULL;
	size_t size;

	for (size = 0; environ[size]; size++)
		append_node(&node, environ[size], 0);
	args->env = node;
	return (0);
}
