#include "main.h"
/**
 * strcat_cd - A function that concatenates the message for cd related errors
 *
 * @datas: data
 * @msg: the message to be printed
 * @error: the output message
 * @ver_str: the line counters
 * Return: (error message)
 */
char *strcat_cd(data_s *datas, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_strcpy(error, datas->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datas->args[0]);
	_strcat(error, msg);
	if (datas->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datas->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, datas->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - An error message for change_directory
 * @datas: data
 * Return: (An error message)
 */
char *error_get_cd(data_s *datas)
{
	int length, length_id;
	char *error, *ver_str, *msg;

	ver_str = aux_itoa(datas->counter);
	if (datas->args[1][0] == '-')
	{
		msg = ": This is an illegal option ";
		length_id = 2;
	}
	else
	{
		msg = ": can't cd into ";
		length_id = _strlen(datas->args[1]);
	}

	length = _strlen(datas->argv[0]) + _strlen(datas->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + length_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd(datash, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found - A function that generates a generic error message for commands that are not found
 * @datas: data
 * Return: (Error message)
 */
char *error_not_found(data_s *datas)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datas->counter);
	length = _strlen(datas->argv[0]) + _strlen(ver_str);
	length += _strlen(datas->args[0]) + 16;
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
	_strcat(error, ": command not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * error_exit_shell - A function that generates a generic error message
for exiting
 * @datas: data
 * Return: (An error message)
 */
char *error_exit_shell(data_s *datas)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datas->counter);
	length = _strlen(datas->argv[0]) + _strlen(ver_str);
	length += _strlen(datas->args[0]) + _strlen(datas->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datas->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datas->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, datas->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}