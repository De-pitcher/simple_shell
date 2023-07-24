#ifndef STRUCT_H
#define STRUCT_H

#include "main.h"

/**
 * struct cmd_t - is the shell variable
 * @mode: it shows if the shell is in interactive mode or not
 * @ready: shows if the shell is ready
 * @status: represent the status of the command
 * @count: it counts the variable
 * @input: it is the actual command parsed by the user
 * @pid: represents the process that runs the command
 * @args: the agrument passed by the main function
 * @argv: the vector argument
 * @envar: environment variable
 */
typedef struct cmd_t
{
	int mode;
	int ready;
	int status;
	int count;
	char *input;
	char *pid;
	char **args;
	char **argv;
	char **envar;
} cmd_t;

/**
 * struct var_l - represent the variable list
 * @var_len: it shows the length of the variable
 * @val_len: it shows the length of the value
 * @val: it shows the actual value
 * @next: contains the pointer to the next node
 */
typedef struct var_l
{
	int var_len;
	int val_len;
	char *val;
	struct var_l *next;
} var_t;

/**
 * struct sep_l - represents a separation list
 * @sep: the variable for the separation list
 * @next: contains the pointer to the next node
 */
typedef struct sep_l
{
	char sep;
	struct sep_l *next;
} sep_t;

/**
 * struct line_s - represents the line list
 * @line: line variable
 * @next: pointer to the next node
 */
typedef struct line_s
{
	char *line;
	struct line_s *next;
} line_t;

/**
 * struct builtins - represnt the builtin functions
 * @name: contains the name of the builtin function
 * @f: functions that execute the builtin command
 */
typedef struct builtins
{
	char *name;
	int (*f)(cmd_t *cmd);
} built_t;

/****** Linked list helpers ******/
var_t *add_tail_node(var_t **head, int var_len, char *val, int val_len);
sep_t *add_end_node(sep_t **head, char sep);
line_t *add_line(line_t **head, char *line);

/***** Free Memory ******/
void free_var(var_t **head);
void free_envar(cmd_t *cmd);
void free_sep_list(sep_t **head);
void free_line_list(line_t **head);

#endif
