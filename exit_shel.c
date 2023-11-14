#include "main.h"

/**
 * exit_shell - A function that exits the shell
 * @datas: data
 * Return: (0) success
 */
int exit_shell(data_s *datas)
{
	unsigned int ustatus;
	int is_digit;
	int str_length;
	int big_number;

	if (datas->args[1] != NULL)
	{
		ustatus = _atoi(datas->args[1]);
		is_digit = _isdigit(datas->args[1]);
		str_length = _strlength(datas->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_length > 10 || big_number)
		{
			get_error(datas, 2);
			datas->status = 2;
			return (1);
		}
		datas->status = (ustatus % 256);
	}
	return (0);
}
