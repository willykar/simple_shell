#include "main.h"
/**
 * cd_dt - changes the parent directory
 * @datas: data
 */
void cd_dt(data_s *datas)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_sp_pwd;

	/* get the current working dir */
	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_environment("OLDPWD", cp_pwd, datas);
	dir = datas->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_environment("PWD", cp_pwd, datas);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_sp_pwd = cp_pwd;
	rev_string(cp_sp_pwd);
	cp_sp_pwd = _strtok(cp_sp_pwd, "/");
	if (cp_sp_pwd != NULL)
	{
		cp_sp_pwd = _strtok(NULL, "\0");

		if (cp_sp_pwd != NULL)
			rev_string(cp_sp_pwd);
	}
	if (cp_sp_pwd != NULL)
	{
		chdir(cp_sp_pwd);
		set_environment("PWD", cp_sp_pwd, datas);
	}
	else
	{
		chdir("/");
		set_environment("PWD", "/", datas);
	}
	datas->status = 0;
	free(cp_pwd);
}

/**
 * cd_change - A function that changes to a particular the directory provided
 * @datas: data
 */
void cd_change(data_s *datas)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datas->args[1];
	if (chdir(dir) == -1)
	{
		get_error(datas, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_environment("OLDPWD", cp_pwd, datas);

	cp_dir = _strdup(dir);
	set_environment("PWD", cp_dir, datas);

	free(cp_pwd);
	free(cp_dir);

	datas->status = 0;

	chdir(dir);
}

/**
 * cd_dir_previous - a function to move to the previous directory
 * @datas: data
 */
void cd_dir_previous(data_s *datas)
{
	char pwd[PATH_MAX];
	char *cur_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", datas->_environment);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_environment("OLDPWD", cp_pwd, datas);

	if (chdir(cp_oldpwd) == -1)
		set_environment("PWD", cp_pwd, datas);
	else
		set_environment("PWD", cp_oldpwd, datas);

	cur_pwd = _getenv("PWD", datas->_environment);

	write(STDOUT_FILENO, cur_pwd, _strlength(cur_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datas->status = 0;

	chdir(cur_pwd);
}

/** 
 * cd_to_home - a function that changes dir to  home directory
 * @datas: data
 */
void cd_to_home(data_s *datas)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", datas->_environment);

	if (home == NULL)
	{
		set_environment("OLDPWD", p_pwd, datas);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datas, 2);
		free(p_pwd);
		return;
	}

	set_environment("OLDPWD", p_pwd, datas);
	set_environment("PWD", home, datas);
	free(p_pwd);
	datas->status = 0;
}
