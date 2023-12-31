#include "main.h"

/**
 * init_var - initialized the shell variables
 * @cmd: struc with shell variables.
 * @argv: argument vector.
 * @arg_len: length of the argv argument in the main function
 *
 * Return: Nothong.
 */

void init_var(cmd_t *cmd, char **argv, int arg_len)
{
	int i = 0;

	cmd->mode = EXEC;
	cmd->ready = 1;
	cmd->status = 0;
	cmd->count = 1;
	cmd->arg_len = arg_len;
	cmd->input = NULL;
	cmd->pid = _itoa(getpid());
	cmd->args = NULL;
	cmd->argv = argv;

	for (i = 0; environ[i]; i++)
		;

	cmd->envar = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
		cmd->envar[i] = _strdup(environ[i]);

	cmd->envar[i] = NULL;
}
