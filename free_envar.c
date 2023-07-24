#include "main.h"

/**
 * free_envar - frees the envar variable in the cmd_t
 * @cmd: cmd struct
 *
 * Return:Nothing.
 */

void free_envar(cmd_t *cmd)
{
	int i;

	for (i = 0; cmd->envar[i]; i++)
		free(cmd->envar[i]);

	free(cmd->envar);
	free(cmd->pid);
}

