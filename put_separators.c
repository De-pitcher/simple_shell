#include "main.h"

void add_nodes(sep_t **head_s, line_t **head_l, char *input);
void go_next(sep_t **list_s, line_t **list_l, cmd_t *cmd);
char *swap_char(char *input, int bool);

/**
 * put_seperators - splits command lines and executes
 * the separators ;, | and &
 *
 * @cmd: structure of the data
 * @input: inputted string
 * Return: 0 to exit, 1 to continue
 */

int put_seperators(cmd_t *cmd, char *input)
{

	sep_t *head_s = NULL, *list_s = NULL;
	line_t *head_l = NULL, *list_l = NULL;
	int ready;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		cmd->input = list_l->line;
		cmd->args = gettoks(cmd->input, DELIM);
		ready = _exec(cmd);
		free(cmd->args);

		if (ready == 0)
		{
			cmd->ready = 0;
			break;
		}

		go_next(&list_s, &list_l, cmd);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (ready == 0)
		return (0);
	return (1);
}

/**
 * add_nodes - add separators and command lines
 *
 * @head_s: represents the head of the separator list
 * @head_l: represents the head of the command lines list
 * @input: inputted string
 * Return: Nothing
 */
void add_nodes(sep_t **head_s, line_t **head_l, char *input)
{
	int i;
	char *line;

	input = swap_char(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_end_node(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_end_node(head_s, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - goes to the next stored command line
 *
 * @list_s: represents the separator list
 * @list_l: represents the command line list
 * @cmd: structure of the data
 * Return: does not return
 */

void go_next(sep_t **list_s, line_t **list_l, cmd_t *cmd)
{
	int loop_sep;
	sep_t *ls_s;
	line_t *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (cmd->status == 0)
		{
			if (ls_s->sep == '&' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->sep == '|' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * swap_char - swaps '|' and "&" for non-printed chars
 *
 * @input: the inputted string
 * @bool: boolean that shows the type of swap
 * Return: swapped string is returned
 */

char *swap_char(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}
