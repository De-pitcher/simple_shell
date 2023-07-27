#include "main.h"

alias alias_l[MAXARGS];
int alias_size = 0;

void print_aliases(char *name);
void write_alias(char *name, char *value);
void init_def_aliases(void);

/**
 * init_def_aliases - intializes the alias variable with the
 * default vlaue.
 * Return: Nothing.
 */
void init_def_aliases(void)
{
	add_alias("egrep", "egrep --color=auto", 1);
	add_alias("fgrep", "fgrep --color=auto", 1);
	add_alias("grep", "grep --color=auto", 1);
	add_alias("l", "ls -CF", 1);
	add_alias("la", "ls -A", 1);
	add_alias("ll", "-alF", 1);
	add_alias("ls", "ls --color=auto", 1);
}

/**
 * add_alias - adds an alias to the alias global varible
 * @name: aliase name.
 * @value: alias value.
 * @is_init: checks to see if it is for the initial addition 
 * of the default alias or not.
 *
 * Return: Nothing.
 */

void add_alias(char *name, char *value, int is_init)
{
	int i;

	for (i = 0; i < alias_size; i++)
		if (_strcmp(alias_l[i].name, name) == 0)
			return;

	if (alias_size == 1024)
		return;
	alias_l[alias_size].name = _strdup(name);
	alias_l[alias_size].value = _strdup(value);

	alias_size++;
	if (is_init == 0)
		write_alias(name, value);
}

/**
 * get_alias_value - gets the alias value.
 * @name: alias name.
 *
 * Return: alias value if found else NULL.
 */

char *get_alias_value(char *name)
{
	int i;

	if (name == NULL)
		return (NULL);

	for (i = 0; i < alias_size; i++)
		if (_strcmp(alias_l[i].name, name) == 0)
			return (alias_l[i].value);
	return (NULL);
}

/**
 * write_alias - writes the value of an alias to the stdout.
 * @name: name of the alias.
 * @value: value of the alis.
 *
 * Return: Nothing.
 */

void write_alias(char *name, char *value)
{
	if (name == NULL || value ==NULL)
		return;

	/*write(STDERR_FILENO, "alias ", 7);*/
	write(STDOUT_FILENO, name, _strlen(name));
	write(STDOUT_FILENO, "=", 1);
	write(STDOUT_FILENO, "\'", 1);
	write(STDOUT_FILENO, value, _strlen(value));
	write(1, "\'\n", 2);
}

/**
 * print_aliases - handles the printing of alias operation to the stdout.
 * @name: alias name.
 *
 * Return: Nothing
 */

void print_aliases(char *name)
{
	int i, size = 0, val_size = 0;
	char *alias_name, *alias_value;


	if (name == NULL)
	{
		for (i = 0; i < alias_size; i++)
		{
			size += _strlen(alias_l[i].name);
			val_size += _strlen(alias_l[i].value);
			alias_name = malloc(sizeof(char *) + size + 1);
			alias_value = malloc(sizeof(char *) + val_size + 1);
			_strcpy(alias_name, alias_l[i].name);
			_strcpy(alias_value, alias_l[i].value);
			write_alias(alias_name, alias_value);
			size = 0;
			val_size = 0;
			free(alias_name);
			free(alias_value);
		}
	}
	else
	{
		for (i = 0; i < alias_size; i++)
		{
			size += _strlen(alias_l[i].name);
			val_size += _strlen(alias_l[i].value);

			if (_strcmp(alias_l[i].name, name) == 0)
			{
				write_alias(alias_l[i].name, alias_l[i].value);
				return;
			}
		}
		write(STDERR_FILENO, "Alias ", 7);
		write(STDERR_FILENO, name, _strlen(name));
		write(STDERR_FILENO, ": not found.\n", 13);
	}
}

/**
 * handle_alias - handles the alias operations or commands.
 * @cmd: shell variable.
 *
 * Return: command extracted from the alias, or NULL.
 */
char *handle_alias(cmd_t *cmd)
{
	char *alias_value, *alias_name, *command;

	init_def_aliases();
	if (cmd->args[0] != NULL && cmd->args[1] != NULL)
	{
		/*printf("1\n");
		printf("args: %s\n", cmd->args[1]);*/
		alias_name = _strtok(cmd->args[1], "=");
		alias_value = _strtok(NULL, "=");
		command = _strtok(NULL, " ");
		printf("command: %s\n", command);
		if (alias_value == NULL && alias_name != NULL)
			print_aliases(alias_name);
		else if(alias_value == NULL && alias_name == NULL)
		{
			printf("2\n");
			alias_name = _strdup(cmd->args[1]);
			alias_value = get_alias_value(alias_name);
			if (alias_value != NULL)
				write_alias(alias_name, alias_value);
		}
		else
		{
			/*printf("3\n");
			printf("alias_name: %s, alias_value: %s\n",
					alias_name, alias_value);*/
			add_alias(alias_name, alias_value, 1);
			/*write_alias(alias_name, alias_value);*/
		}
	}
	print_aliases(alias_name);

	return (alias_name);
}
