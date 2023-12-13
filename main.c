#include "shell.h"

/**
 *main - the entry point of the program
 *@ac: the argument count
 *@av: the argument vector (command line arguments)
 *Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_type info[] = { INIT_INFO };

	int file_descriptor = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0" : "=r"(file_descriptor) : "r"(file_descriptor));

	if (ac == 2)
	{
		file_descriptor = open(av[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_input(av[0]);
				print_input(": 0: Can't open ");
				print_input(av[1]);
				print_standard_error('\n');
				print_standard_error(BUFFER_FLUSH_STATUS);
				exit(127);
			}

			return (EXIT_FAILURE);
		}

		info->readfiledata = file_descriptor;
	}

	populate_environment(info);
	read_history_file(info);
	hash_function(info, av);
	return (EXIT_SUCCESS);
}
