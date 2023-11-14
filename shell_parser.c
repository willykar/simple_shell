#include "main.h"

/**
 * swap_char - A function that swaps | and & for non-printed characters
 * @input: The input string
 * @bool: The type of the swap
 * Return: (Swapped string)
 */
char *swap_char(char *input, int bool)
{
	int a;

	if (bool == 0)
	{
		for (a = 0; input[a]; a++)
		{
			if (input[a] == '|')
			{
				if (input[a + 1] != '|')
					input[a] = 16;
				else
					a++;
			}

			if (input[a] == '&')
			{
				if (input[a + 1] != '&')
					input[a] = 12;
				else
					a++;
			}
		}
	}
	else
	{
		for (a = 0; input[a]; a++)
		{
			input[a] = (input[a] == 16 ? '|' : input[a]);
			input[a] = (input[a] == 12 ? '&' : input[a]);
		}
	}
	return (input);
}

/**
 * add_nodes - A function that adds separators and command lines in the list
 * @head_s: The head of the separator list
 * @head_l: The head of the command line list
 * @input: The input string
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int a;
	char *line;

	input = swap_char(input, 0);

	for (a = 0; input[a]; a++)
	{
		if (input[a] == ';')
			add_sep_node_end(head_s, input[a]);

		if (input[a] == '|' || input[a] == '&')
		{
			add_sep_node_end(head_s, input[a]);
			a++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - A function that goes to the next command line
 * @list_s: The separator list
 * @list_l: The command line list
 * @datas: data being used
 */
void go_next(sep_list **list_s, line_list **list_l, data_s *datas)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datas->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - A function that splits command lines according to
 * the separators ;, | and &, and executes them
 * @datas: a data structure that will be used
 * @input: The input string
 * Return: (0) to exit or (1) to continue
 */
int split_commands(data_s *datas, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datas->input = list_l->line;
		datas->args = split_line(datas->input);
		loop = execute_line(datas);
		free(datas->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, datas);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep(&head_s);
	free_line(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - A function that tokenizes the input string
 * @input: The input string
 * Return: (split string)
 */
char **split_line(char *input)
{
	size_t b_size;
	size_t a;
	char **tokens;
	char *token;

	b_size = TOK_BUFFSIZE;
	tokens = malloc(sizeof(char *) * (b_size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (a = 1; token != NULL; a++)
	{
		if (a == b_size)
		{
			b_size += TOK_BUFFSIZE;
			tokens = _reallocdp(tokens, a, sizeof(char *) * b_size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[a] = token;
	}

	return (tokens);
}
