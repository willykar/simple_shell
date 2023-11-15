#include "main.h"

/**
 * cmp_env_name - A function that compares environment variables names
 * with the names that were passed
 * @nenvi: The environment variable
 * @name: The name that was passed
 * Return: (0) if not equal or another value if they are
 */
int cmp_env_name(const char *nenvi, const char *name)
{
	int a;

	for (a = 0; nenvi[a] != '='; a++)
	{
		if (nenvi[a] != name[a])
		{
			return (0);
		}
	}

	return (a + 1);
}
/**
 * _getenv - A function that gets an environment variable
 * @name: The name of the variable
 * @_environment: The variable environ
 * Return: (value of the variable or NULL)
 */
char *_getenv(const char *name, char **_environment)
{
	char *ptr_env;
	int a, move;

	ptr_env = NULL;
	move = 0;

	for (a = 0; _environment[a]; a++)
	{
		move = cmp_env_name(_environment[a], name);
		if (move)
		{
			ptr_env = _environment[a];
			break;
		}
	}

	return (ptr_env + move);
}
