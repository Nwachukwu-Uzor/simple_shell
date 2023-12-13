#include "shell.h"

/**
 *initialize_info_type - create an args struct
 *@args: address of the args struct
 */
void initialize_info_type(info_type *args)
{
	args->arg = NULL;
	args->argv = NULL;
	args->path = NULL;
	args->argc = 0;
}

/**
 *set_info_type - updates an args struct
 *@args: the address of the truct
 *@av: argument vector
 */
void set_info_type(info_type *args, char **av)
{
	int i = 0;

	args->file_name = av[0];
	if (args->arg)
	{
		args->argv = str_tokenize(args->arg, " \t");
		if (!args->argv)
		{
			args->argv = malloc(sizeof(char *) * 2);
			if (args->argv)
			{
				args->argv[0] = _strdup(args->arg);
				args->argv[1] = NULL;
			}
		}

		for (i = 0; args->argv && args->argv[i]; i++)
		;
		args->argc = i;

		substitute_alias(args);
		substitute_vars(args);
	}
}

/**
 *free_info_type - frees the info struct
 *@args: the address of the info struct
 *@all: used to free all
 */
void free_info_type(info_type *args, int all)
{
	free_strings(args->argv);
	args->argv = NULL;
	args->path = NULL;
	if (all)
	{
		if (!args->cmd_buffer)
			free(args->arg);
		if (args->env)
			clear_list(&(args->env));
		if (args->history)
			clear_list(&(args->history));
		if (args->alias)
			clear_list(&(args->alias));
		free_strings(args->environ);
		args->environ = NULL;
		_free_pointers((void **) args->cmd_buffer);
		if (args->readfiledata > 2)
			close(args->readfiledata);
		_putchar(BUFFER_FLUSH_STATUS);
	}
}
