#include "shell.h"

/**
 *__eputs_ - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void __eputs_(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		__eputchar_(str[i]);
		i++;
	}
}

/**
 * __eputchar_ - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int __eputchar_(char c)
{
	static int i;
	static char buf[_WRITE_BUF_SIZE_];

	if (c == BUF_FLUSH || i >= _WRITE_BUF_SIZE_)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * __putfd_ - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int __putfd_(char c, int fd)
{
	static int i;
	static char buf[_WRITE_BUF_SIZE_];

	if (c == BUF_FLUSH || i >= _WRITE_BUF_SIZE_)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *__putsfd_ - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int __putsfd_(char *str, int fd)
{
	int i = 0;

	while (!str)
		return (0);
	while (*str)
	{
		i += __putfd_(*str++, fd);
	}
	return (i);
}
