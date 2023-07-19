#include "shell.h"

/**
 * _myenv_ - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myenv_(info_t *info)
{
	_print_list_str_(info->env);
	return (0);
}

/**
 * _getenv_ - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv_(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with_(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv_ - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mysetenv_(info_t *info)
{
	if (info->argc != 3)
	{
		__eputs_("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv_(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv_ - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myunsetenv_(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		__eputs_("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv_(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list_ - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int populate_env_list_(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_add_node_end_(&node, environ[i], 0);
	info->env = node;
	return (0);
}
