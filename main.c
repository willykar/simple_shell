#include "main.h"
/**
 * free_datastruct - a function that frees the data structure
 * @datash: data structure
 * Return: nothing
 */
void free_datastruct(data_s *datas)
{
	unsigned int a;

	for (a = 0; datas->_environment[a]; a++)
	{
		free(datas->_environment[a]);
	}

	free(datas->_environment);
	free(datas->pid);
}

/**
 * set_data - A function that initialize a data structure
 * @datash: data structure
 * @arg: argument vector
 */
void set_data(data_s *datas, char **argv)
{
	unsigned int a;

	datas->argv = argv;
	datas->input = NULL;
	datas->args = NULL;
	datas->status = 0;
	datas->counter = 1;

	for (a = 0; environment[a]; a++)
		;

	datas->_environment = malloc(sizeof(char *) * (a + 1));

	for (a = 0; environment[a]; a++)
	{
		datas->_environment[a] = _strdup(environment[a]);
	}

	datas->_environment[a] = NULL;
	datas->pid = aux_itoa(getpid());
}

/**
 * main - The entry point function
 * @argc: argument count of arguments
 * @argv: argument vector containing the arguments
 * Return: 0 if success
 */
int main(int argc, char **argv)
{
	data_s datas;
	(void) argc;

	signal(SIGINT, get_sigint);
	set_data(&datas, argv);
	shell_loop(&datas);
	free_datastruct(&datas);
	if (datas.status < 0)
		return (255);
	return (datas.status);
}
