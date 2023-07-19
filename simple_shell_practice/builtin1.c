#include "shell.h"

/**
 * _history_ - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _history_(info_t *info)
{
	_print_list_(info->history);
	return (0);
}

/**
 * _unset_alias_ - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _unset_alias_(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr_(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = _delete_node_at_index_(&(info->alias),
		_get_node_index_(info->alias, _node_starts_with_(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * _set_alias_ - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _set_alias_(info_t *info, char *str)
{
	char *p;

	p = _strchr_(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_unset_alias_(info, str));

	_unset_alias_(info, str);
	return (_add_node_end_(&(info->alias), str, 0) == NULL);
}

/**
 * _print_alias_ - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int _print_alias_(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr_(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar_(*a);
		_putchar_('\'');
		_puts_(p + 1);
		_puts_("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias_ - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _alias_(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_print_alias_(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr_(info->argv[i], '=');
		if (p)
			_set_alias_(info, info->argv[i]);
		else
			_print_alias_(_node_starts_with_(info->alias, info->argv[i], '='));
	}

	return (0);
}
