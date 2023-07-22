#include "main.h"

/**
 * _itoa - Converts an integer to string
 * @n: input.
 *
 * Return: converted string
 */

char *_itoa(int n)
{
	unsigned int n1;
	int len = getlen(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + len) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	len--;
	do {
		*(buffer + len) = (n1 % 10) + '0';
		n1 = n1 / 10;
		len--;
	}
	while (n1 > 0)
		;
	return (buffer);
}

/**
 * getlen - gets the length of a number
 * @n: input(int)
 *
 * Return: length of the number.
 */

int getlen(int n)
{
	unsigned int n1;
	int len = 1;

	if (n < 0)
	{
		len++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		len++;
		n1 = n1 / 10;
	}

	return (len);
}
