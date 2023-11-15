#include "main.h"

/**
 * get_help - A function that retrieves help messages according to builtin
 * @datas: data structure to be used
 * Return: 1.
*/
int get_help(data_s *datas)
{

	if (datas->args[1] == 0)
		aux_help_general();
	else if (_strcmp(datas->args[1], "setenv") == 0)
		aux_help_setenv();
	else if (_strcmp(datas->args[1], "env") == 0)
		aux_help_env();
	else if (_strcmp(datas->args[1], "unsetenv") == 0)
		aux_help_unsetenv();
	else if (_strcmp(datas->args[1], "help") == 0)
		aux_help();
	else if (_strcmp(datas->args[1], "exit") == 0)
		aux_help_exit();
	else if (_strcmp(datas->args[1], "cd") == 0)
		aux_help_cd();
	else if (_strcmp(datas->args[1], "alias") == 0)
		aux_help_alias();
	else
		write(STDERR_FILENO, datas->args[0],
		      _strlength(datas->args[0]));

	datas->status = 0;
	return (1);
}
