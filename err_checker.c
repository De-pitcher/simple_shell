#include "main.h"

int indexof_fchar(char *input, int *i);
void print_synterr(cmd_t *cmd, char *input, int i, int flag);
int find_error(char *input, int i, char last);
int count_repchar(char *input, int i);

/**
 * check_synterr - finds and print a syntax error
 *
 * @cmd: shell command
 * @input: inputted string
 * Return: 1 if there is an error, 0 in other case
 */

int check_synterr(cmd_t *cmd, char *input)
{
	int begin = 0, f_char = 0, i = 0;

	f_char = indexof_fchar(input, &begin);
	if (f_char == -1)
	{
		print_synterr(cmd, input, begin, 0);
		return (1);
	}

	i = find_error(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_synterr(cmd, input, begin + i, 1);
		return (1);
	}

	return (0);
}

/**
 * indexof_fchar - finds the index of the first character
 * @input: input string.
 * @i: index.
 *
 * Return: 0 on success else 1.
 */

int indexof_fchar(char *input, int *i)
{
	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_synterr - prints some messages to the console when the syntax
 * error is found.
 * @cmd: shell command variable.
 * @input: inputted string.
 * @i: index of error.
 * @flag: controls error message.
 *
 * Return: Nothing.
 */

void print_synterr(cmd_t *cmd, char *input, int i, int flag)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int len;

	if (input[i] == ';')
	{
		if (flag == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = _itoa(cmd->count);
	len = _strlen(cmd->argv[0]) + _strlen(counter);
	len += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, cmd->argv[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, len);
	free(error);
	free(counter);
}

/**
 * find_error - finds syntax errors
 * @input: inputted string
 * @i: index
 * @last: last character read
 * Return: index of error or 0 if no errors.
 */

int find_error(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (find_error(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = count_repchar(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = count_repchar(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (find_error(input + 1, i + 1, *input));
}

/**
 * count_repchar - counts character repetitions.
 * @input: inputted string
 * @i: index.
 *
 * Return: num of repetitions.
 */

int count_repchar(char *input, int i)
{
	if (*(input - 1) == *input)
		return (count_repchar(input - 1, i + 1));

	return (i);
}
