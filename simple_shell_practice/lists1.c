#include "shell.h"

/**
 * _list_len_ - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t _list_len_(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _list_to_strings_ - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **_list_to_strings_(list_t *head)
{
	list_t *node = head;
	size_t i = _list_len_(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	while (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen_(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy_(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * _print_list_ - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t _print_list_(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts_(convert_number_(h->num, 10, 0));
		_putchar_(':');
		_putchar_(' ');
		_puts_(h->str ? h->str : "(nil)");
		_puts_("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _node_starts_with_ - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *_node_starts_with_(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with_(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * _get_node_index_ - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t _get_node_index_(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
