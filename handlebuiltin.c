#include "shell.h"

/**
 *_exit_shell - closes the shell
 *@args: potential system argument struct
 *Return: exit status code of the program
 */
int _exit_shell(info_type *args)
{
	int exit_status;

	if (args->argv[1]) /*If there is an exit arguement */
	{
		exit_status = _string_to_int(args->argv[1]);
		if (exit_status == -1)
		{
			args->status = 2;
			error_printer(args, "Illegal number: ");
			print_input(args->argv[1]);
			print_standard_error('\n');
			return (1);
		}

		args->error_number = _string_to_int(args->argv[1]);
		return (-2);
	}

	args->error_number = -1;
	return (-2);
}

/**
 *_mycd - handles directory change
 *@args: the argument struct
 *Return: 0
 */
int _mycd(info_type *args)
{
	char *ch, *cur_dir, buffer[1024];
	int dir_status;

	ch = getcwd(buffer, 1024);
	if (!ch)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!args->argv[1])
	{
		cur_dir = _get_env(args, "HOME=");
		if (!cur_dir)
			dir_status = chdir((cur_dir = _get_env(args, "PWD=")) ? cur_dir : "/");
		else
			dir_status = chdir(cur_dir);
	}
	else if (_strcmp(args->argv[1], "-") == 0)
	{
		if (!_get_env(args, "OLDPWD="))
		{
			_puts(ch);
			_putchar('\n');
			return (1);
		}

		_puts(_get_env(args, "OLDPWD=")), _putchar('\n');
		dir_status = chdir((cur_dir = _get_env(args, "OLDPWD=")) ? cur_dir : "/");
	}
	else
		dir_status = chdir(args->argv[1]);
	if (dir_status == -1)
	{
		error_printer(args, "can't cd to ");
		print_input(args->argv[1]), print_standard_error('\n');
	}
	else
	{
		_add_new_env(args, "OLDPWD", _get_env(args, "PWD="));
		_add_new_env(args, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}

/**
 *_change_directory - changes process directory
 *@args: arguments to change directory
 *Return: Always 0
 */
int _change_directory(info_type *args)
{
	char **arg_array;

	arg_array = args->argv;
	_puts("not implement\n");
	if (0)
		_puts(*arg_array);
	return (0);
}
