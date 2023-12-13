#include "shell.h"

/**
 * hash_function - main shell loop
 * @args : the parameter & return args  struct
 * @arg_vect: the args vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hash_function(info_type *args , char **arg_vect)
{
	ssize_t t = 0;
	int output = 0;

	while (t != -1 && output != -2)
	{
		initialize_info_type(args );
		if (check_interactive(args ))
			_puts("$ ");
		print_standard_error(BUFFER_FLUSH_STATUS);
		t = _extract_inputs(args );
		if (t != -1)
		{
			set_info_type(args , arg_vect);
			output = retrieve_builtin(args );
			if (output == -1)
				retrieve_cmd(args );
		}
		else if (check_interactive(args ))
			_putchar('\n');
		free_info_type(args , 0);
	}
	add_to_history_file(args );
	free_info_type(args , 1);
	if (!check_interactive(args ) && args ->status)
		exit(args ->status);
	if (output == -2)
	{
		if (args ->error_number == -1)
			exit(args ->status);
		exit(args ->error_number);
	}
	return (output);
}

/**
 * retrieve_builtin - finds a in-built command
 * @args : the parameter & return args  struct
 *
 * Return: 0 if in-built executed successfully,
 * -1 if in-built not found,
 * -2 if in-built signals exit()
 * 1 if in-built found but not successful,
 * 
 */
int retrieve_builtin(info_type *args )
{
	int count, result = -1;
	table_builtin built_in[] = {
		{"exit", _exit_shell},
		{"env", print_my_env},
		{"help", _change_directory},
		{"history", _tranverse_history},
		{"setenv", initialize_my_env},
		{"unsetenv", _clear_environment},
		{"cd", _mycd},
		{"alias", _custom_alias},
		{NULL, NULL}};

	for (count = 0; built_in[count].type; count++)
		if (_strcmp(args ->argv[0], built_in[count].type) == 0)
		{
			args ->line_number++;
			result = built_in[count].func(args );
			break;
		}
	return (result);
}

/**
 * retrieve_cmd - finds a command in the path
 * @args : the parameter and return args struct
 *
 * Return: void
 */
void retrieve_cmd(info_type *args )
{
	char *_path = NULL;
	int count, counter;

	args ->_path = args ->argv[0];
	if (args ->linenumber_tag == 1)
	{
		args ->line_number++;
		args ->linenumber_tag = 0;
	}
	for (count = 0, counter = 0; args ->arg[count]; count++)
		if (!check_delimiter(args ->arg[count], " \t\n"))
			counter++;
	if (!counter)
		return;

	_path = compute_path(args , _get_env(args , "PATH="), args ->argv[0]);
	if (_path)
	{
		args ->_path = _path;
		command_fork(args );
	}
	else
	{
		if ((check_interactive(args ) || _get_env(args , "PATH=") || args ->argv[0][0] == '/') && verify_cmd(args , args ->argv[0]))
			command_fork(args );
		else if (*(args ->arg) != '\n')
		{
			args ->status = 127;
			error_printer(args , "not found\n");
		}
	}
}

/**
 * command_fork - forks a an executable thread to run the cmd
 * @args : the parameter and return args struct
 *
 * Return: nothing
 */
void command_fork(info_type *args )
{
	pid_t sub_child;

	sub_child = fork();
	if (sub_child == -1)
	{
		perror("Error:");
		return;
	}
	if (sub_child == 0)
	{
		if (execve(args ->_path, args ->argv, get_environment_variables(args )) == -1)
		{
			free_info_type(args , 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(args ->status));
		if (WIFEXITED(args ->status))
		{
			args ->status = WEXITSTATUS(args ->status);
			if (args ->status == 126)
				error_printer(args , "Permission denied\n");
		}
	}
}

