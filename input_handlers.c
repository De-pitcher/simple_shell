#include "main.h"

int scan_vars(var_t **h, char *input, char *status, cmd_t *cmd);
char *replace_input(var_t **head, char *input, char *new_input, int nlen);
void find_env(var_t **head, char *input, cmd_t *cmd);

/**
 * handle_input - converts variables into strings
 * @input: input.
 * @cmd: shell variable
 *
 * Return: converted string.
 */

char *handle_input(char *input, cmd_t *cmd)
{
	var_t *head, *tmp;
	char *status, *n_input;
	int o_len = 0, n_len = 0;

	status = _itoa(cmd->status);
	head = NULL;

	o_len = scan_vars(&head, input, status, cmd);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	tmp = head;
	n_len = 0;

	while (tmp != NULL)
	{
		n_len += (tmp->val_len - tmp->var_len);
		tmp = tmp->next;
	}

	n_len += o_len;

	n_input = malloc(sizeof(char) * (n_len + 1));
	n_input[n_len] = '\0';

	n_input = replace_input(&head, input, n_input, n_len);

	free(input);
	free(status);
	free_var(&head);

	return (n_input);
}

/**
 * scan_vars - checks if the inputted variable is $$ or $
 *
 * @h: represents the head of the linked list
 * @input: inputted string
 * @status: represents the last status of the Shell
 * @cmd: structure of data
 * Return: does not return
 */

int scan_vars(var_t **h, char *input, char *status, cmd_t *cmd)
{
	int i, j, stlen, pid_len;

	stlen = _strlen(status);
	pid_len = _strlen(cmd->pid);

	for (i = 0, j = 1; input[i]; i++, j++)
	{
		if (input[i] == '$')
		{
			switch (input[j])
			{
				case '?':
					add_tail_node(h, 2, status, stlen), i++;
					break;
				case '$':
					add_tail_node(h, 2, cmd->pid, pid_len), i++;
					break;
				case ' ':
				case '\n':
				case '\0':
				case ';':
				case '\t':
					add_tail_node(h, 0, NULL, 0);
					break;
				default:
					find_env(h, input + i, cmd);
					break;
			}
		}
	}

	return (i);
}

/**
 * replace_input - function that replaces string into variable
 *
 * @head: represents the head of the linked list
 * @input: inputted string
 * @new_input: the replaced new input string
 * @nlen: new length of string
 * Return: replaced string
 */

char *replace_input(var_t **head, char *input, char *new_input, int nlen)
{
	var_t *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->var_len) && !(indx->val_len))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->var_len && !(indx->val_len))
			{
				for (k = 0; k < indx->var_len; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->val_len; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->var_len);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * find_env - searches for variable in environ
 *
 * @head: represents head of linked list
 * @input: inputted string
 * @cmd: struct variable
 * Return: does not return
 */

void find_env(var_t **head, char *input, cmd_t *cmd)
{
	int i, j, k, lval;
	char **_envr;

	_envr = cmd->envar;

	for (i = 0; _envr[i]; i++)
	{
		for (k = 1, j = 0; _envr[i][j]; j++)
		{
			if (_envr[i][j] == '=')
			{
				lval = _strlen(_envr[i] + j + 1);
				add_tail_node(head, k, _envr[i] + j + 1, lval);
				return;
			}

			if (input[k] == _envr[i][j])
				k++;
			else
				break;
		}
	}

	for (k = 0; input[k]; k++)
	{
		if (input[k] == ' ' || input[k] == '\t' ||
		input[k] == ';' || input[k] == '\n')
			break;
	}

	add_tail_node(head, k, NULL, 0);
}
