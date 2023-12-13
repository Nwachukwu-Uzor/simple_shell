#include "shell.h"

/**
 *input_buf - performs buffering on chained command
 *@args: parameter struct
 *@buf: the address of the buffer
 *@len: the address of len buffer
 *Return: size of bytes read
 */
ssize_t input_buf(info_type *args, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t size = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, block_ctrc);
		#if FIND_STROKE_LINE
		r = getline(buf, &size, stdin);
		#else
			r = _get_line(args, buf, &size);
		#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}

			args->linenumber_tag = 1;
			clear_comment(*buf);
			create_history_list(args, *buf, args->history_count++);
			{
				*len = r;
				args->cmd_buffer = buf;
			}
		}
	}

	return (r);
}

/**
 *_extract_inputs - extracts all lines except new line character
 *@args: the command line arguments
 *Return: the size of the byte
 */
ssize_t _extract_inputs(info_type *args)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t output = 0;
	char **buf_p = &(args->arg), *pointer;

	_putchar(BUFFER_FLUSH_STATUS);
	output = input_buf(args, &buffer, &len);
	if (output == -1)
		return (-1);
	if (len)
	{
		j = i;
		pointer = buffer + i;

		check_chain(args, buffer, &j, i, len);
		while (j < len)
		{
			if (check_chain_delimeter(args, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			args->cmd_buffer_type = CMD_NORM;
		}

		*buf_p = pointer;
		return (_strlen(pointer));
	}

	*buf_p = buffer;
	return (output);
}

/**
 *buffer_reader - to buffer to read from
 *@args: command line arguments
 *@buf: buffer
 *@i: the size of the buffer
 *
 *Return: size of the buffer
 */
ssize_t buffer_reader(info_type *args, char *buf, size_t *i)
{
	ssize_t size = 0;

	if (*i)
		return (0);
	size = read(args->readfiledata, buf, MAX_BUFFER_READ_SIZE);
	if (size >= 0)
		*
		i = size;
	return (size);
}

/**
 *_get_line - gets the next line of input from STDIN
 *@args: the command line arguments
 *@ptr: the address to the output pointer
 *@length: the size th pointer
 *
 *Return: the line count
 */
int _get_line(info_type *args, char **ptr, size_t *length)
{
	static char buf[MAX_BUFFER_READ_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, output = 0;
	char *pointer = NULL, *new_p = NULL, *c;

	pointer = *ptr;
	if (pointer && length)
		output = *length;
	if (i == len)
		i = len = 0;

	r = buffer_reader(args, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc_block(pointer, output, output ? output + k : k + 1);
	if (!new_p)
		return (pointer ? free(pointer), -1 : -1);

	if (output)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	output += k - i;
	i = k;
	pointer = new_p;

	if (length)
		*
		length = output;
	*ptr = pointer;
	return (output);
}

/**
 *block_ctrc - blocks the use of ctr c
 *@sig_num: the signal number
 *
 *Return: void
 */
void block_ctrc(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH_STATUS);
}
