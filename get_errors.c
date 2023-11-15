#include "main.h"
/**
 * get_error - A function that calls errors
 * @datas: data structure which has arguments
 * @eval: the error value
 * Return: (error)
 */
int get_error(data_s *datas, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env(datas);
		break;
	case 126:
		error = error_path_p(datas);
		break;
	case 127:
		error = error_not_found(datas);
		break;
	case 2:
		if (_strcmp("exit", datas->args[0]) == 0)
			error = error_exit_shell(datas);
		else if (_strcmp("cd", datas->args[0]) == 0)
			error = error_get_cd(datas);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlength(error));
		free(error);
	}

	datas->status = eval;
	return (eval);
}
