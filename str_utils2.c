#include "main.h"
/**
 * _strdup - A function that duplicates a str in the memory
 * @s: Pointer to a string
 * Return: (The duplicated str)
 */
char *_strdup(const char *s)
{
	char *new;
	size_t length;

	length = _strlength(s);
	new = malloc(sizeof(char) * (length + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, length + 1);
	return (new);
}

/**
 * _strlen - A function that returns the length of a string
 * @s: pointer of type char
 * Return: (0)
 */
int _strlength(const char *s)
{
	int length;

	for (length = 0; s[length] != 0; length++)
	{
	}
	return (length);
}

/**
 * cmp_chars - A function that compares chars of strings
 * @str: string
 * @delim: delimiter
 * Return: (1) if chars are equal or 0 if they are not
 */
int comp_chars(char str[], const char *delim)
{
	unsigned int a, b, c;

	for (a = 0, c = 0; str[a]; a++)
	{
		for (b = 0; delim[b]; b++)
		{
			if (str[a] == delim[b])
			{
				c++;
				break;
			}
		}
	}
	if (a == c)
		return (1);
	return (0);
}

/**
 * _strtok - A function that splits a string by some delimiter
 * @str: the input string
 * @delim: delimiter
 * Return: (the split string)
 */
char *_strtok(char str[], const char *delim)
{
	static char *split, *str_end;
	char *str_start;
	unsigned int a, b;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		split = str;
		i = _strlength(str);
		str_end = &str[a];
	}
	str_start = split;
	if (str_start == str_end)
		return (NULL);

	for (b = 0; *split; split++)
	{
		if (split != str_start)
			if (*split && *(split - 1) == '\0')
				break;
		for (a = 0; delim[a]; a++)
		{
			if (*split == delim[a])
			{
				*split = '\0';
				if (split == str_start)
					str_start++;
				break;
			}
		}
		if (b == 0 && *split)
			b = 1;
	}
	if (b == 0)
		return (NULL);
	return (str_start);
}

/**
 * _isdigit -  A function that defines if a string passed is a number
 *
 * @s: The input string
 * Return: (1) if the string is a number or (0) otherwise
 */
int _isdigit(const char *s)
{
	unsigned int a;

	for (a = 0; s[a]; a++)
	{
		if (s[a] < 48 || s[a] > 57)
			return (0);
	}
	return (1);
}
