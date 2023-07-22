#include "main.h"

/**
 * c_dir - changes the current working directory
 *
 * @cmd: relevant to data
 * Return: 1 upon success
 */

int c_dir(cmd_t *cmd)
{
	char *args = cmd->args[1];

	if (!args || !_strcmp(args, "~") || !_strcmp(args, "$HOME")
	|| !_strcmp(args, "--"))
		return (cd_home(cmd));
	else if (!_strcmp(args, "-"))
		return (cd_back(cmd));
	else if (!_strcmp(args, "."))
		return (cd_curr(cmd));
	else if (!_strcmp(args, ".."))
		return (cd_parent(cmd));
	else
		return (cd_path(args, cmd));
}

/**
 * set_env - a function that sets an environment variable
 *
 * @name: environment variable name
 * @value: environment variable name
 * @cmd: environ data structure
 * Return: does not return
 */

void set_env(char *name, char *value, cmd_t *cmd)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; cmd->envar[i]; i++)
	{
		var_env = _strdup(cmd->envar[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(cmd->envar[i]);
			cmd->envar[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	cmd->envar = _reallocdp(cmd->envar, i, sizeof(char *) * (i + 2));
	cmd->envar[i] = copy_info(name, value);
	cmd->envar[i + 1] = NULL;
}

/**
 * _setenv - compares environment variable names
 * as they are passed
 * @cmd: data relevant environment name and value
 *
 * Return: 1 upon success
 */

int _setenv(cmd_t *cmd)
{

	if (cmd->args[1] == NULL || cmd->args[2] == NULL)
	{
		return (1);
	}

	set_env(cmd->args[1], cmd->args[2], cmd);

	return (1);
}

/**
 * _unsetenv - deletes an environment variable
 *
 * @cmd: data relevant environment name
 *
 * Return: 1 upon success.
 */

int _unsetenv(cmd_t *cmd)
{
	char **realloc_envar;
	char *var_env, *name_env;
	int i, j, k;

	if (cmd->args[1] == NULL)
	{
		return (1);
	}
	k = -1;
	for (i = 0; cmd->envar[i]; i++)
	{
		var_env = _strdup(cmd->envar[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, cmd->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		return (1);
	}
	realloc_envar = malloc(sizeof(char *) * (i));
	for (i = j = 0; cmd->envar[i]; i++)
	{
		if (i != k)
		{
			realloc_envar[j] = cmd->envar[i];
			j++;
		}
	}
	realloc_envar[j] = NULL;
	free(cmd->envar[k]);
	free(cmd->envar);
	cmd->envar = realloc_envar;
	return (1);
}
