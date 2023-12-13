#include "shell.h"

/**
 *verify_cmd - a funtion that shows if a file is an executable command
 *@args: the args struct
 *@_path: _path to the file
 *
 *Return: 1 if true, else 0
 */
int verify_cmd(info_type *args, char *_path)
{
	struct stat st;

	(void) args;
	if (!_path || stat(_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 *replicate_chars - duplicating a characters
 *@path_str: the path to the string
 *@start: beginning index
 *@stop: ending count
 *
 *Return: pointer to a new buffer
 */
char *replicate_chars(char *path_str, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (path_str[i] != ':')
			buf[k++] = path_str[i];
	buf[k] = 0;
	return (buf);
}

/**
 *compute_path - finds this cmd in the path string
 *@args: the args struct
 *@path_str: the path string
 *@_cmd: the cmd to find
 *
 *Return: the path of the cmd if found, else NULL
 */
char *compute_path(info_type *args, char *path_str, char *_cmd)
{
	int i = 0, curr_pos = 0;
	char *_path;

	if (!path_str)
		return (NULL);
	if ((_strlen(_cmd) > 2) && starts_with(_cmd, "./"))
	{
		if (verify_cmd(args, _cmd))
			return (_cmd);
	}

	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			_path = replicate_chars(path_str, curr_pos, i);
			if (!*_path)
				_strcat(_path, _cmd);
			else
			{
				_strcat(_path, "/");
				_strcat(_path, _cmd);
			}

			if (verify_cmd(args, _path))
				return (_path);
			if (!path_str[i])
				break;
			curr_pos = i;
		}

		i++;
	}

	return (NULL);
}
