#include "main.h"

/**
 * read_input - reads the string input from the getline function
 * @num: value returned from the getline
 * @status: flag for determining if a shell is inetractive
 *
 * Return: string returned by the getline function.
 */

char *read_input(int status, int *num)
{
	size_t b_size = 0;
	char *buffer = NULL;

	_prompt(status);
	*num = getline(&buffer, &b_size, stdin);

	return (buffer);
}
