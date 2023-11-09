#include "main.h"

/**
 * get_length - A function that gets the length of a number
 * @n: int number.
 * Return: (length of number)
 */
int get_length(int n)
{
	unsigned int a;
	int length = 1;

	if (n < 0)
	{
		lenght++;
		a = n * -1;
	}
	else
	{
		a = n;
	}
	while (a > 9)
	{
		lenght++;
		a = a / 10;
	}

	return (length);
}
/**
 * aux_itoa - A function converts an integer to a string
 * @n: number of type int
 * Return: (string)
 */
char *aux_itoa(int n)
{
	unsigned int a;
	int length = get_length(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (n < 0)
	{
		a = n * -1;
		buffer[0] = '-';
	}
	else
	{
		a = n;
	}

	length--;
	do {
		*(buffer + length) = (a % 10) + '0';
		a = a / 10;
		length--;
	}
	while (a > 0)
		;
	return (buffer);
}

/**
 * _atoi - A function that converts a string to an integer
 * @s: the input string
 * Return: (an integer)
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, k = 0, l = 1, j = 1, a;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			l *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				j *= 10;
			size++;
		}
		count++;
	}

	for (a = count - size; a < count; a++)
	{
		k = k + ((*(s + a) - 48) * j);
		j /= 10;
	}
	return (k * l);
}
