#include "main.h"
/**
 * cmp_env_name - compares environment variables names
 * with the names that were passed
 * @nenv: environment variable
 * @name: the name that was passed
 * Return: 0 if not equal or different value if they are
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
 * @name: name of the variable
 * @_environ: variable
 * Return: value of the variable or NULL
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

/**
 * _env - A function that prints env variables
 * @datas: data 
 * Return: 1 on success.
 */
int _env(data_s *datas)
{
	int a, b;

	for (a = 0; datas->_environment[a]; a++)
	{

		for (b = 0; datas->_environment[a][b]; b++)
			;

		write(STDOUT_FILENO, datas->_environment[a], b);
		write(STDOUT_FILENO, "\n", 1);
	}
	datas->status = 0;

	return (1);
}
