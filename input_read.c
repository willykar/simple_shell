#include "main.h"
/**
 * read_line - A function that reads the input string
 * from the standard input
 * @i_eof: This is the return value of the getline function
 * Return: (input string)
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t buffsize = 0;

	*i_eof = getline(&input, &buffsize, stdin);

	return (input);
}
/**
 * free_rvar_list - A function that frees a list
 * @head: The head of a list
 */
void free_rvar_list(r_var **head)
{
	r_var *temp;
	r_var *curr;

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
 * error_path_p - A function that gives an error message
 * for the path and permission denied failure
 * @datas: data
 * Return: (error string)
 */
char *error_path_p(data_s *datas)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = aux_itoa(datas->counter);
	length = _strlength(datas->argv[0]) + _strlength(ver_str);
	length += _strlength(datas->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datas->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datas->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * rev_string - A function that reverses a string passed
 * @s: The input string
 */
void rev_string(char *s)
{
	int count = 0, a, b;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (a = 0; a < (count - 1); a++)
	{
		for (b = a + 1; b > 0; b--)
		{
			temp = *(str + b);
			*(str + b) = *(str + (b - 1));
			*(str + (b - 1)) = temp;
		}
	}
}
