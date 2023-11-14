#include "main.h"
/**
 * is_cdir - A function that checks if ":" is in
 * the current directory
 * @path: A char pointer
 * @i: integer pointer
 * Return: (1) if the path is searchable
 * in the directory or (0) otherwise
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - A function that locates a command
 * @cmd: Name of the command
 * @_environment: An environment variable
 * Return: (The location of the command)
 */
char *_which(char *cmd, char **_environment)
{
	char *path, *ptr_path, *token_path, *dir;
	int length_dir, len_cmd, a;
	struct stat st;

	path = _getenv("PATH", _environment);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlength(cmd);
		token_path = _strtok(ptr_path, ":");
		a = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &a))
				if (stat(cmd, &st) == 0)
					return (cmd);
			length_dir = _strlength(token_path);
			dir = malloc(length_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - A function that
 * determines an executable
 * @datas: data structure to be used
 * Return: (0) if is not an executable
 * or other number if it is
 */
int is_executable(data_s *datas)
{
	struct stat st;
	int a;
	char *input;

	input = datas->args[0];
	for (a = 0; input[a]; a++)
	{
		if (input[a] == '.')
		{
			if (input[a + 1] == '.')
				return (0);
			if (input[a + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[a] == '/' && a != 0)
		{
			if (input[a + 1] == '.')
				continue;
			a++;
			break;
		}
		else
			break;
	}
	if (a == 0)
		return (0);

	if (stat(input + a, &st) == 0)
	{
		return (a);
	}
	get_error(datas, 127);
	return (-1);
}

/**
 * check_error_cmd - A function that
 * verifies if user has permissions for access
 * @dir: The destination directory
 * @datas: The data structure to be used
 * Return: (0) if successful or (1) if there is an error
 */
int check_error_cmd(char *dir, data_s *datas)
{
	if (dir == NULL)
	{
		get_error(datas, 127);
		return (1);
	}

	if (_strcmp(datas->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datas, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datas->args[0], X_OK) == -1)
		{
			get_error(datas, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - A function that executes the command lines
 * @datas: data
 * Return: (1) on success
 */
int cmd_execute(data_s *datas)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_executable(datas);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(datas->args[0], datas->_environ);
		if (check_error_cmd(dir, datas) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(datas->args[0], datas->_environ);
		else
			dir = datas->args[0];
		execve(dir + exec, datas->args, datas->_environ);
	}
	else if (pd < 0)
	{
		perror(datas->argv[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datas->status = state / 256;
	return (1);
}
