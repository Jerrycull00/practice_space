#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void _clear_info_(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * _set_info_ - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void _set_info_(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow_(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup_(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias_(info);
		replace_vars_(info);
	}
}

/**
 * _free_info_ - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void _free_info_(info_t *info, int all)
{
	ffree_(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			_free_list_(&(info->env));
		if (info->history)
			_free_list_(&(info->history));
		if (info->alias)
			_free_list_(&(info->alias));
		ffree_(info->environ);
			info->environ = NULL;
		_bfree_((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar_(BUF_FLUSH);
	}
}
