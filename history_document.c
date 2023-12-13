#include "shell.h"

/**
 * find_history_file - gets the history document
 * @mssg: parameter struct
 *
 * Return: assign string with the history document
 */

char *find_history_file(info_type *mssg)
{
	char *buff, *_dir;

	_dir = _get_env(mssg, "HOME=");
	if (!_dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(_dir) + _strlen(HISTORY_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, _dir);
	_strcat(buff, "/");
	_strcat(buff, HISTORY_FILE);
	return (buff);
}

/**
 * add_to_history_file - creates a file, or add to an already existing file
 * @mssg: the parameter struct
 *
 * Return: 1 upon success, else -1
 */
int add_to_history_file(info_type *mssg)
{
	ssize_t fd;
	char *file_name = find_history_file(mssg);
	list_type *node = NULL;

	if (!file_name)
		return (-1);

	fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (fd == -1)
		return (-1);
	for (node = mssg->history; node; node = node->next)
	{
		_print_standard_string(node->str, fd);
		_print_file_char('\n', fd);
	}
	_print_file_char(buffFER_FLUSH_STATUS, fd);
	close(fd);
	return (1);
}

/**
 * read_history_file - reads history from the file
 * @mssg: the parameter struct
 *
 * Return: number of history on success,else 0
 */
int read_history_file(info_type *mssg)
{
	int i, _last = 0, line_count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *file_name = find_history_file(mssg);

	if (!file_name)
		return (0);

	fd = open(file_name, O_RDONLY);
	free(file_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			create_history_list(mssg, buff + _last, line_count++);
			_last = i + 1;
		}
	if (_last != i)
		create_history_list(mssg, buff + _last, line_count++);
	free(buff);
	mssg->history_count = line_count;
	while (mssg->history_count-- >= MAX_HISTORY_COUNT)
		remove_node_at_index(&(mssg->history), 0);
	reorder_history(mssg);
	return (mssg->history_count);
}

/**
 * create_history_list - puts entry to a history list
 * @mssg: Struct containing potential args.
 * @buff: bufffer
 * @line_count: the history line_count, history_count
 *
 * Return: Always 0
 */
int create_history_list(info_type *mssg, char *buff, int line_count)
{
	list_type *node = NULL;

	if (mssg->history)
		node = mssg->history;
	append_node(&node, buff, line_count);

	if (!mssg->history)
		mssg->history = node;
	return (0);
}

/**
 * reorder_history - numbering again the history linked list after changes
 * @mssg: Struct containing likely args.
 *
 * Return: the new history_count
 */
int reorder_history(info_type *mssg)
{
	list_type *node = mssg->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (mssg->history_count = i);
}

