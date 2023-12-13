#include "shell.h"

/**
 **_memset - loads the  memory with a constant_byte
 *@str: the pointer to the memory_alloc
 *@_byte: the byte to load *str with
 *@byte_num: the amount of bytes to be loaded
 *Return: (str) a pointer to the memory_alloc of str
 */
char *_memset(char *str, char _byte, unsigned int byte_num)
{
	unsigned int count;

	for (count = 0; count < byte_num; count++)
		str[count] = _byte;
	return (str);
}

/**
 *free_strings - releases a string from the strings
 *@st_str: a string inside a strings
 */
void free_strings(char **st_str)
{
	char **c = st_str;

	if (!st_str)
		return;
	while (*st_str)
		free(*st_str++);
	free(c);
}

/**
 *_realloc_block - reallocates a block of memory
 *@_ptr: pointer to previous malloc'ated block
 *@older_size: byte size of previous block
 *@newest_size: byte size of new block
 *
 *Return: pointer to da ol'block nameen.
 */
void *_realloc_block(void *_ptr, unsigned int older_size,
		unsigned int newest_size)
{
	char *b;

	if (!_ptr)
		return (malloc(newest_size));
	if (!newest_size)
		return (free(_ptr), NULL);
	if (newest_size == older_size)
		return (_ptr);

	b = malloc(newest_size);
	if (!b)
		return (NULL);

	older_size = older_size < newest_size ? older_size : newest_size;
	while (older_size--)
		b[older_size] = ((char *) _ptr)[older_size];
	free(_ptr);
	return (b);
}
