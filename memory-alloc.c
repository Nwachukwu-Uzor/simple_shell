#include "shell.h"

/**
 *_free_pointers - a funtion that releases a pointer and NULLs the address
 *@_ptr: the address of the pointer to be released
 *
 *Return: 1 if released, else 0.
 */
int _free_pointers(void **_ptr)
{
	if (_ptr && *_ptr)
	{
		free(*_ptr);
		*_ptr = NULL;
		return (1);
	}

	return (0);
}
