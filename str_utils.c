#include "main.h"

/**
 * _strcat - A function that concatenates two strings
 * @dest: A character pointer to the destination string
 * @src: A constant character pointer the source string
 * Return: the dest
 */
char *_strcat(char *dest, const char *src)
{
	int a;
	int b;

	for (a = 0; dest[a] != '\0'; a++)
		;

	for (b = 0; src[b] != '\0'; b++)
	{
		dest[a] = src[b];
		a++;
	}

	dest[a] = '\0';
	return (dest);
}
/**
 * *_strcpy - A function that copies the string pointed by src
 * @dest: Destination string
 * @src: Source string
 * Return: (dest)
 */
char *_strcpy(char *dest, char *src)
{

	size_t i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return (dest);
}
/**
 * _strcmp - A function that compares two strings s1 and s2
 * @s1: First str to be compared
 * @s2: Second string to be compared
 * Return: 0
 */
int _strcmp(char *s1, char *s2)
{
	int a;

	for (a = 0; s1[a] == s2[a] && s1[a]; a++)
		;

	if (s1[a] > s2[a])
		return (1);
	if (s1[a] < s2[a])
		return (-1);
	return (0);
}
/**
 * _strchr - A function that locates a char in a string
 * @s: string
 * @c: The character to locate
 * Return: (A pointer to the first occurrence of the character c)
 */
char *_strchr(char *s, char c)
{
	unsigned int a = 0;

	for (; *(s + a) != '\0'; a++)
		if (*(s + a) == c)
			return (s + a);
	if (*(s + a) == c)
		return (s + a);
	return ('\0');
}
/**
 * _strspn - A function that gets the length of a prefix substring.
 * @s: The initial segment
 * @accept: accepted bytes
 * Return: (number of accepted bytes)
 */
int _strspn(char *s, char *accept)
{
	int a, b, c;

	for (a = 0; *(s + a) != '\0'; a++)
	{
		c = 1;
		for (b = 0; *(accept + b) != '\0'; b++)
		{
			if (*(s + a) == *(accept + b))
			{
				c = 0;
				break;
			}
		}
		if (c == 1)
			break;
	}
	return (a);
}
