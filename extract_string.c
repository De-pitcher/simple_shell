#include "main.h"

/**
 * extract_string - extracts the string in a comment
 * @input: input argument.
 *
 * Return: string without comment sign.
 */

char *extract_string(char *input)
{
	int i, j = 0;

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				j = i;
		}
	}

	if (j != 0)
	{
		input = _realloc(input, i, j + 1);
		input[j] = '\0';
	}

	return (input);
}
