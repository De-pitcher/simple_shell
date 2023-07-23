#include "main.h"

/**
 * _strlen - returns the length of a string
 * @s: pointer to the string.
 *
 * Return: length of the string inputed.
 */

int _strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

/**
 * _strdup - Creates the same exact copy of the input string but in
 * a newly-allocated space in memory.
 * @str: Input string.
 *
 * Return: NULL if it is not sucessful else a newly-allocated string.
 */

char *_strdup(char *str)
{
	unsigned int i = 0;
	unsigned int strlen = 0;
	char *cpy_str = NULL;

	if (str == NULL)
		return (NULL);

	for (strlen = 0; str[strlen] != '\0'; strlen++)
		;

	cpy_str = malloc((strlen + 1) * sizeof(char));

	if (cpy_str == NULL)
		return (NULL);

	for (i = 0; i < strlen; i++)
	{
		cpy_str[i] = str[i];
	}

	cpy_str[strlen] = '\0';

	return (cpy_str);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination of the pointer
 * @src: source of the pointer
 *
 * Return: destination address
 */

char *_strcat(char *dest, char *src)
{
	int a = -1, i = 0;

	for (i = 0; dest[i] != '\0'; i++)
	;

	do {
		a++;
		dest[i] = src[a];
		i++;
	} while (src[a] != '\0');

	return (dest);
}

/**
 * _strcpy - copies the pointed string and the terminating null byte
 * @dest: pointer to the buffer from which string is copied
 * @src: the string to be copied
 *
 * Return: the pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int len = 0, i = 0;
	char *srcpy = src;

	while (srcpy[len] != '\0')
	{
		len++;
	}

	for (i = 0; i < len; i++)
	{
		dest[i] = srcpy[i];
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * gettoks - obtains tokens from user input
 *
 * @args: input string
 * @delimiter: delimiter.
 * Return: vector of splited input strings.
 */

char **gettoks(char *args, char *delimiter)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = MAXARGS;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(args, delimiter);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += MAXARGS;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, delimiter);
		tokens[i] = token;
	}

	return (tokens);
}
