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
/**
 * _env - A function that prints environment variables
 * @datas: data
 * Return: (1) on success
 */
int _env(data_s *datas)
{
	int a, b;

	for (a = 0; datas->_environ[a]; a++)
	{

		for (b = 0; datas->_environ[a][b]; b++)
			;

		write(STDOUT_FILENO, datas->_environ[a], b);
		write(STDOUT_FILENO, "\n", 1);
	}
	datas->status = 0;

	return (1);
}

/**
 * copy_info - A function that copies information to create a new environment
 * @name: name
 * @value: value
 * Return: (a new environment)
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int length_name, length_value, length;

	length_name = _strlength(name);
	length_value = _strlength(value);
	length = length_name + length_value + 2;
	new = malloc(sizeof(char) * (length));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_environment - A function that sets an environment variable
 * @name: name of the env variable
 * @value: value of the env
 * @datas: dta structure
 */
void set_environment(char *name, char *value, data_s *datas)
{
	int a;
	char *var_envi, *name_envi;

	for (a = 0; datas->_environ[a]; a++)
	{
		var_envi = _strdup(datas->_environ[a]);
		name_envi = _strtok(var_envi, "=");
		if (_strcmp(name_envi, name) == 0)
		{
			free(datas->_environ[a]);
			datas->_environ[a] = copy_info(name_envi, value);
			free(var_envi);
			return;
		}
		free(var_envi);
	}

	datas->_environ = _reallocdp(datas->_environ, a, sizeof(char *) * (a + 2));
	datas->_environ[a] = copy_info(name, value);
	datas->_environ[a + 1] = NULL;
}

/**
 * _setenv - compares variable names(environment)
 * with the passed name
 * @datas: data
 * Return: 1 if successful
 */
int _setenv(data_s *datas)
{

	if (datas->args[1] == NULL || datas->args[2] == NULL)
	{
		get_error(datas, -1);
		return (1);
	}

	set_environment(datas->args[1], datas->args[2], datas);

	return (1);
}

/**
 * _unsetenv - a function that deletes environment variables
 * @datash: data
 * Return: (1) if success
 */
int _unsetenv(data_s *datas)
{
	char **realloc_environment;
	char *var_envi, *name_envi;
	int a, b, c;

	if (datas->args[1] == NULL)
	{
		get_error(datas, -1);
		return (1);
	}
	c = -1;
	for (a = 0; datas->_environ[a]; a++)
	{
		var_envi = _strdup(datas->_environ[a]);
		name_envi = _strtok(var_envi, "=");
		if (_strcmp(name_envi, datas->args[1]) == 0)
		{
			c = a;
		}
		free(var_envi);
	}
	if (c == -1)
	{
		get_error(datas, -1);
		return (1);
	}
	realloc_environment = malloc(sizeof(char *) * (a));
	for (a = b = 0; datas->_environ[a]; a++)
	{
		if (a != c)
		{
			realloc_environment[b] = datas->_environ[a];
			b++;
		}
	}
	realloc_environment[b] = NULL;
	free(datas->_environ[c]);
	free(datas->_environ);
	datas->_environ = realloc_environment;
	return (1);
}
