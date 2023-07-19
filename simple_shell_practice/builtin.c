#include "shell.h"

/**
 * _exit_ - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _exit_(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi_(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error_(info, "Illegal number: ");
			__eputs_(info->argv[1]);
			__eputchar_('\n');
			return (1);
		}
		info->err_num = _erratoi_(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _cd_ - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _cd_(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts_("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv_(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv_(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp_(info->argv[1], "-") == 0)
	{
		if (!_getenv_(info, "OLDPWD="))
		{
			_puts_(s);
			_putchar_('\n');
			return (1);
		}
		_puts_(_getenv_(info, "OLDPWD=")), _putchar_('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv_(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error_(info, "can't cd to ");
		__eputs_(info->argv[1]), __eputchar_('\n');
	}
	else
	{
		_setenv_(info, "OLDPWD", _getenv_(info, "PWD="));
		_setenv_(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help_ - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _help_(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts_("help call works. Function not yet implemented \n");
	if (0)
		_puts_(*arg_array); /* temp att_unused workaround */
	return (0);
}
