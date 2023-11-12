#include "main.h"

/**
 * bring_line - A function that assigns the line variable for get_line
 * @lineptr: The Buffer that stores the input string
 * @buffer: A str that is been called to the line
 * @n: size of the line
 * @j: size of the buffer
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFFSIZE)
			*n = j;

		else
			*n = BUFFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFFSIZE)
			*n = j;
		else
			*n = BUFFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - A function that reads input from a stream
 * @lineptr: A buffer that stores the input
 * @n: size of the line pointer
 * @stream: The stream to read from
 * Return: (number of bytes)
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int a;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		a = read(STDIN_FILENO, &t, 1);
		if (a == -1 || (a == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (a == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (a != 0)
		input = 0;
	return (retval);
}
