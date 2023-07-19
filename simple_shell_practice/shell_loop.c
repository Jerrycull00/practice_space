#include "shell.h"

/**
 * _hsh_ - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int _hsh_(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		_clear_info_(info);
		if (_interactive_(info))
			_puts_("$ ");
		__eputchar_(BUF_FLUSH);
		r = _get_input_(info);
		if (r != -1)
		{
			_set_info_(info, av);
			builtin_ret = _find_builtin_(info);
			if (builtin_ret == -1)
				_find_cmd_(info);
		}
		else if (_interactive_(info))
			_putchar_('\n');
		_free_info_(info, 0);
	}
	_write_history_(info);
	_free_info_(info, 1);
	if (!_interactive_(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * _find_builtin_ - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int _find_builtin_(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = 
	{
		{"exit", _exit_},
		{"env", _myenv_},
		{"help", _help_},
		{"history", _history_},
		{"setenv", _mysetenv_},
		{"unsetenv", _myunsetenv_},
		{"cd", _cd_},
		{"alias", _alias_},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp_(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * _find_cmd_ - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void _find_cmd_(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!_is_delim_(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = _find_path_(info, _getenv_(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		_fork_cmd_(info);
	}
	else
	{
		if ((_interactive_(info) || _getenv_(info, "PATH=")
			|| info->argv[0][0] == '/') && _is_cmd_(info, info->argv[0]))
			_fork_cmd_(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error_(info, "not found\n");
		}
	}
}

/**
 * _fork_cmd_ - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void _fork_cmd_(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ_(info)) == -1)
		{
			_free_info_(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error_(info, "Permission denied\n");
		}
	}
}
