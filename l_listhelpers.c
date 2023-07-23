#include "main.h"

/**
 * add_tail_node - a function that adds a node to end list
 * @head: represents the head of the linked list
 * @var_len: represents the length of the variable
 * @val: represents the value of the variable
 * @val_len: represents the length of the value
 * Return: address of the head is returned
 */

var_t *add_tail_node(var_t **head, int var_len, char *val, int val_len)
{
	var_t *new, *temp;

	new = malloc(sizeof(var_t));
	if (new == NULL)
	{
		free(new);
		return (NULL);
	}

	new->var_len = var_len;
	new->val = val;
	new->val_len = val_len;

	new->next = NULL;

	if (!(*head))
		*head = new;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_var - function that frees a list_t list
 * @head: represents the head of the linked list
 * Return: does not return
 */

void free_var(var_t **head)
{
	var_t *temp, *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * free_sep_list - a function that frees a separation list
 * @head: represents the head of the linked list
 */

void free_sep_list(sep_t **head)
{
	sep_t *temp;
	sep_t *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * free_line_list - function that frees a line_list
 * @head: represents the head of the linked list
 * Return: does not return
 */

void free_line_list(line_t **head)
{
	line_t *temp;
	line_t *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
