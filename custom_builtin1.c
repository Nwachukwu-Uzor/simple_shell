#include "shell.h"

/**
 *_tranverse_history - prints the history list
 *@args: the arguments
 *Return: Always 0
 */
int _tranverse_history(info_type *args)
{
	print_list(args->history);
	return (0);
}

/**
 *unset_alias - unsets a given alias
 *@args: parameter struct
 *@str: the string alias
 *
 *Return: Always 0 on success, 1 on error
 */
int unset_alias(info_type *args, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = remove_node_at_index(&(args->alias),
		find_node_at_index(args->alias, node_start_prefix(args->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 *set_alias - creates an alias
 *@args: the arguments
 *@str: the alias to set
 *Return: 0 on success, 1 on failure
 */
int set_alias(info_type *args, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(args, str));

	unset_alias(args, str);
	return (append_node(&(args->alias), str, 0) == NULL);
}

/**
 *print_alias - displays the alias
 *@node: the node for the alias
 *Return: 0 on success, 1 on failure
 */
int print_alias(list_type *node)
{
	char *p1 = NULL, *p2 = NULL;

	if (node)
	{
		p1 = _strchr(node->str, '=');
		for (p2 = node->str; p2 <= p1; p2++)
			_putchar(*p2);
		_putchar('\'');
		_puts(p1 + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}

/**
 *_custom_alias - replicates the built-in alias
 *@args: the command arguments
 *Return: 0
 */
int _custom_alias(info_type *args)
{
	int i = 0;
	char *p = NULL;
	list_type *node = NULL;

	if (args->argc == 1)
	{
		node = args->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}

		return (0);
	}

	for (i = 1; args->argv[i]; i++)
	{
		p = _strchr(args->argv[i], '=');
		if (p)
			set_alias(args, args->argv[i]);
		else
			print_alias(node_start_prefix(args->alias, args->argv[i], '='));
	}

	return (0);
}
