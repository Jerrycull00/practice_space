#include "shell.h"

/**
 * _bfree_ - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int _bfree_(void **ptr)
{
	while (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;

		return (1);
	}

	return (0);
}
