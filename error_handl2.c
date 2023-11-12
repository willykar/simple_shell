#include "main.h"
/**
 * error_env - A function that gets an error message for env
 * @datas: data
 * Return: (An error message)
 */
char *error_env(data_s *datas)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = aux_itoa(datas->counter);
	msg = ": Not able to add or remove from the environment\n";
	length = _strlength(datas->argv[0]) + _strlength(ver_str);
	length += _strlength(datas->args[0]) + _strlength(msg) + 4;
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
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * error_path_126 - A function that gives an error message
for the path and failure
 * @datas: data
 * Return: (error string)
 */
char *error_path_126(data_s *datas)
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
