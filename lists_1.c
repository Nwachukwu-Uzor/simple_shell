#include "shell.h"

/**
 *calculate_list_length - function that shows the length of the linked list
 *@first_node: the pointer to first node
 *
 *Return: the size of the list
 */
size_t calculate_list_length(const list_type *first_node)
{
	size_t count = 0;

	while (first_node)
	{
		first_node = first_node->next;
		count++;
	}

	return (count);
}

/**
 *print_list_string - a funtion that returns an array
 *of strings of the linked list
 *@_head: pointer to first node
 *
 *Return: array of strings
 */
char **print_list_string(list_type *_head)
{
	list_type *node = _head;
	size_t count = calculate_list_length(_head), j;
	char **strs;
	char *str;

	if (!_head || !count)
		return (NULL);
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	for (count = 0; node; node = node->next, count++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < count; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[count] = str;
	}

	strs[count] = NULL;
	return (strs);
}

/**
 *print_list - prints all elements of a list_type linked list
 *@first_node: pointer to first node
 *
 *Return: size of list
 */
size_t print_list(const list_type *first_node)
{
	size_t count = 0;

	while (first_node)
	{
		_puts(number_converter(first_node->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(first_node->str ? first_node->str : "(nil)");
		_puts("\n");
		first_node = first_node->next;
		count++;
	}

	return (count);
}

/**
 *node_start_prefix - a function that returns the node
 *whose string starts with prefix
 *@node: the pointer to the linked list head
 *@_prefix: the string to be match
 *@c: the next character after prefix to match
 *
 *Return: the node that matches else null
 */
list_type *node_start_prefix(list_type *node, char *_prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, _prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}

	return (NULL);
}

/**
 *find_node_at_index - gets the index of a node
 *@_head: the pointer to the linked list head
 *@node: pointer to the node
 *
 *Return: index of node else -1
 */
ssize_t find_node_at_index(list_type *_head, list_type *node)
{
	size_t count = 0;

	while (_head)
	{
		if (_head == node)
			return (count);
		_head = _head->next;
		count++;
	}

	return (-1);
}
