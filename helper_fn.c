#include "main.h"

/**
 * open_console - a function that opens a custom console
 *
 * Return: Nothing
 */

void open_console(void)
{
	int c_fd;

	while ((c_fd = open("/dev/console", O_RDWR)) >= 0)
	{
		if (c_fd >= 3)
		{
			close(c_fd);
			break;
		}
	}
}

/**
 * handle_sigint - handles sigint signal
 * @sig: signal parametr.
 *
 * Return: Nothing.
 */

void handle_sigint(int sig)
{
	/*exit(sig);*/
	(void)sig;
	write(STDOUT_FILENO, "<saMosC/> SIGINT\n", 18);
}

/**
 * _prompt - writes to the stdin if the process is interactive.
 * @status: flag that checks if the shell is interactive.
 *
 * Return: Nothing.
 */

void _prompt(int status)
{
	if (status)
		write(STDIN_FILENO, "#cisfun$ ", 9);
}

/**
 * error_h - a function that handles error
 *
 * @s: the error message
 * Return: Nothing.
 */

void error_h(char *s)
{
	write(STDERR_FILENO, s, _strlen(s));
}
