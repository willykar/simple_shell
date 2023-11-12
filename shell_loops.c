#include "main.h"

/**
 * without_comment - A function that deletes comments from the input
 * @in: The input string
 * Return: (the input without comments)
 */
char *without_comment(char *in)
{
	int a, up_to;

	up_to = 0;
	for (a = 0; in[a]; a++)
	{
		if (in[a] == '#')
		{
			if (a  == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[a - 1] == ' ' || in[a - 1] == '\t' || in[a - 1] == ';')
				up_to = a;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, a, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - This function is the loop of the shell
 * @datas: data structure to use
 */
void shell_loop(data_s *datas)
{
	int l, i_eof;
	char *input;

	l = 1;
	while (l == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datas, input) == 1)
			{
				datas->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datas);
			l = split_commands(datas, input);
			datas->counter += 1;
			free(input);
		}
		else
		{
			l = 0;
			free(input);
		}
	}
}
