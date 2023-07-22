#include "main.h"

/**
 * main - Entry pointer
 * @argc: Number of argument
 * @argv: Argument vector.
 *
 * Return: int value, according to the status of the program.
 */

int main(int argc, char **argv)
{
	cmd_t cmd;
	(void) argc;

	signal(SIGINT, handle_sigint);
	open_console();
	init_var(&cmd, argv);
	shell_session(&cmd);
	free_envar(&cmd);

	return (cmd.status);
}

/**
 * shell_session - creates a session of reading, evaluating and
 * shell commands in a loop.
 * @cmd: shell commands.
 *
 * Return: Nothing.
 */

void shell_session(cmd_t *cmd)
{
	int loop = 1, eof;
	char *input;


	while (loop == 1)
	{
		input = read_input(1, &eof);
		if (eof != -1)
		{
			input = extract_string(input);
			if (input == NULL)
				continue;

			if (check_synterr(cmd, input) == 1)
			{
				cmd->status = 2;
				free(input);
				continue;
			}

			input = handle_input(input, cmd);
			loop = put_seperators(cmd, input);
			cmd->count += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
