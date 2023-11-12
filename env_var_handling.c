#include "main.h"

/**
 * check_env -  A function that checks if the typed variable is an environment variable
 * @h: The head of the linked list
 * @in: The input string
 * @data: data
 */
void check_env(r_var **h, char *in, data_s *data)
{
	int row, chr, a, lval;
	char **_env;

	_env = data->_environment;
	for (row = 0; _env[row]; row++)
	{
		for (a = 1, chr = 0; _env[row][chr]; chr++)
		{
			if (_env[row][chr] == '=')
			{
				lval = _strlength(_env[row] + chr + 1);
				add_rvar_node(h, a, _env[row] + chr + 1, lval);
				return;
			}

			if (in[a] == _env[row][chr])
				a++;
			else
				break;
		}
	}

	for (a = 0; in[a]; a++)
	{
		if (in[a] == ' ' || in[a] == '\t' || in[a] == ';' || in[a] == '\n')
			break;
	}

	add_rvar_node(h, a, NULL, 0);
}

/**
 * check_vars - A function checks if the typed variable is $$ or $?
 * @h: The head of the linked list
 * @in: The input string
 * @st: This is the last status of the Shell
 * @data: data structure of the shell
 */
int check_vars(r_var **h, char *in, char *st, data_s *data)
{
	int a, lst, lpd;

	lst = _strlength(st);
	lpd = _strlength(data->pid);

	for (a = 0; in[a]; a++)
	{
		if (in[a] == '$')
		{
			if (in[a + 1] == '?')
				add_rvar_node(h, 2, st, lst), a++;
			else if (in[a + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), a++;
			else if (in[a + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[a + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[a + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[a + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[a + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + a, data);
		}
	}

	return (a);
}

/**
 * replaced_input - A function that replaces strings into variables
 * @head: The head of the linked list
 * @input: The input string
 * @new_input: The new input string
 * @nlen: length
 * Return: (The replaced string)
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int a, b, c;

	indx = *head;
	for (b = a = 0; a < nlen; a++)
	{
		if (input[b] == '$')
		{
			if (!(indx->length_var) && !(indx->length_val))
			{
				new_input[a] = input[b];
				b++;
			}
			else if (indx->length_var && !(indx->length_val))
			{
				for (c = 0; c < indx->length_var; c++)
					b++;
				a--;
			}
			else
			{
				for (c = 0; c < indx->length_val; c++)
				{
					new_input[a] = indx->val[c];
					a++;
				}
				b += (indx->length_var);
				a--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[a] = input[b];
			b++;
		}
	}

	return (new_input);
}

/**
 * rep_var - A function that calls functions to replace a string into vars
 * @input: The input string
 * @datash: data structure to be used
 * Return: (the replaced string)
 */
char *rep_var(char *input, data_s *datas)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlength;

	status = aux_itoa(datas->status);
	head = NULL;

	olen = check_vars(&head, input, status, datas);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlength = 0;

	while (indx != NULL)
	{
		nlength += (indx->length_val - indx->length_var);
		indx = indx->next;
	}

	nlength += olen;

	new_input = malloc(sizeof(char) * (nlength + 1));
	new_input[nlength] = '\0';

	new_input = replaced_input(&head, input, new_input, nlength);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
