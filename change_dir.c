#include "main.h"

/**
 * cd_shell - A function that changes the current directory
 * @datas: data
 * Return: (1) if success
 */
int cd_shell(data_s *datas)
{
	char *dir;
	int dir_ishome, dir_ishome2, isd;

	dir = datas->args[1];

	if (dir != NULL)
	{
		dir_ishome = _strcmp("$HOME", dir);
		dir_ishome2 = _strcmp("~", dir);
		isd = _strcmp("--", dir);
	}

	if (dir == NULL || !dir_ishome || !dir_ishome2 || !isd)
	{
		cd_to_home(datas);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_dir_previous(datas);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dt(datas);
		return (1);
	}

	cd_to_home(datas);

	return (1);
}
