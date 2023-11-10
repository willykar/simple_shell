#include "main.h"
/**
 * execute_line - A function that finds
 * builtins and commands
 * @datas: data
 * Return: (1) if success
 */
int execute_line(data_s *datas)
{
	int (*builtin)(data_s *datas);

	if (datas->args[0] == NULL)
		return (1);

	builtin = get_builtin(datas->args[0]);

	if (builtin != NULL)
		return (builtin(datas));

	return (cmd_execute(datas));
}
