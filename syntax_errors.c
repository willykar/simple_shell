#include "main.h"

/**
 * repeated_char - A function that counts the repetitions of a character
 * @input: The input string
 * @i: index
 * Return: (the repetitions)
 */
int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	return (i);
}

/**
 * error_sep_op - A function that finds syntax errors
 * @input: the input string
 * @i: index
 * @last: character read
 * Return: (0) if no errors or index of errors
 */
int error_sep_op(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (error_sep_op(input + 1, i + 1, *input));
}

/**
 * first_char - A function that finds the index of the first character
 *
 * @input: The input string
 * @i: index
 * Return: (0) if there is no error or (1) otherwise
 */
int first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - A function that prints when a syntax error is found
 * @datas: data structure to be used
 * @input: the input string
 * @i: index of the error
 * @bool: to control message error
 */
void print_syntax_error(data_s *datas, char *input, int i, int bool)
{
	char *msg1, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg1 = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg1 = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg1 = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg1 = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(datas->counter);
	length = _strlength(datas->av[0]) + _strlength(counter);
	length += _strlength(msg1) + _strlength(msg2) + _strlength(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datas->argv[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg1);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_syntax_error - A function that
 * finds and prints syntax errors
 * @datas: data structure
 * @input: The input string
 * Return: (0) or (1) if there is an error
 */
int check_syntax_error(data_s *datas, char *input)
{
	int begin = 0;
	int f_char = 0;
	int a = 0;

	f_char = first_char(input, &begin);
	if (f_char == -1)
	{
		print_syntax_error(datas, input, begin, 0);
		return (1);
	}

	a = error_sep_op(input + begin, 0, *(input + begin));
	if (a != 0)
	{
		print_syntax_error(datas, input, begin + a, 1);
		return (1);
	}

	return (0);
}
