#include "shell.h"

/**
 *add_node - adding a node to the beginning of the linked list
 *@_head: addressing of pointer to the head node
 *@str: str field of the node
 *@numb: index of node used by history document
 *
 *Return: size of list
 */
list_type *add_node(list_type **_head, const char *str, int numb)
{
	list_type *newest_head;

	if (!_head)
		return (NULL);
	newest_head = malloc(sizeof(list_type));
	if (!newest_head)
		return (NULL);
	_memset((void *) newest_head, 0, sizeof(list_type));
	newest_head->numb = numb;
	if (str)
	{
		newest_head->str = _strdup(str);
		if (!newest_head->str)
		{
			free(newest_head);
			return (NULL);
		}
	}

	newest_head->next = *_head;
	*_head = newest_head;
	return (newest_head);
}

/**
 *append_node - adding a node to the end of the linked list
 *@_head: addressing of pointer to the head node
 *@str: str field of the node
 *@numb: index of node used by history document
 *
 *Return: size of list
 */
list_type *append_node(list_type **_head, const char *str, int numb)
{
	list_type *new_node, *node;

	if (!head)
		return (NULL);

	node = *_head;
	new_node = malloc(sizeof(list_type));
	if (!new_node)
		return (NULL);
	_memset((void *) new_node, 0, sizeof(list_type));
	new_node->numb = numb;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*_head = new_node;
	return (new_node);
}

/**
 *print_string_elements - prints only the string
 *elements of a list_type linked list
 *@first_node: the pointer to the first node
 *
 *Return: the size of the linked list
 */
size_t print_string_elements(const list_type *first_node)
{
	size_t count = 0;

	while (first_node)
	{
		_puts(first_node->str ? first_node->str : "(nil)");
		_puts("\n");
		first_node = first_node->next;
		count++;
	}

	return (count);
}

/**
 *remove_node_at_index - a function that deletes node at given index
 *@_head: addressing of pointer to the first node
 *@index: the index of node to be deleted
 *
 *Return: 1 on success, else 0
 */
int remove_node_at_index(list_type **_head, unsigned int index)
{
	list_type *node, *prev_node;
	unsigned int count = 0;

	if (!_head || !*_head)
		return (0);

	if (!index)
	{
		node = *_head;
		*_head = (*_head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *_head;
	while (node)
	{
		if (count == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}

		count++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 *clear_list - releases all nodes of a linked list
 *@_head_ptr: address of pointer to the head node
 *
 *Return: void
 */
void clear_list(list_type **_head_ptr)
{
	list_type *node, *next_node, *_head;

	if (!_head_ptr || !*_head_ptr)
		return;
	_head = *_head_ptr;
	node = _head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*_head_ptr = NULL;
}
