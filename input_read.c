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
