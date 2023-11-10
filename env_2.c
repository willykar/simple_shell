#include "main.h"
/**
 * copy_info - copies information to create a new environment
 * @name: name
 * @value: value
 * Return: a new environments
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
 * set_env - A function that sets an environment variable
 * @name: name of the env variable
 * @value: value of the env
 * @datas: dta structure
 */
void set_environment(char *name, char *value, data_s *datas)
{
	int a;
	char *var_envi, *name_envi;

	for (a = 0; datas->_environment[a]; a++)
	{
		var_envi = _strdup(datas->_environment[a]);
		name_envi = _strtok(var_envi, "=");
		if (_strcmp(name_envi, name) == 0)
		{
			free(datas->_environment[a]);
			datas->_environment[a] = copy_info(name_envi, value);
			free(var_envi);
			return;
		}
		free(var_envi);
	}

	datas->_environment = _reallocdp(datas->_environment, a, sizeof(char *) * (a + 2));
	datas->_environment[a] = copy_info(name, value);
	datas->_environment[a + 1] = NULL;
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
 * _unsetenv - a function that deletes env variables
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
	for (a = 0; datas->_environment[a]; a++)
	{
		var_envi = _strdup(datas->_environment[a]);
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
	for (a = b = 0; datas->_environment[a]; a++)
	{
		if (a != c)
		{
			realloc_environment[b] = datas->_environment[a];
			b++;
		}
	}
	realloc_environment[b] = NULL;
	free(datas->_environment[c]);
	free(datas->_environment);
	datas->_environment = realloc_environment;
	return (1);
}
