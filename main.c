#include "main.h"
/**
 * free_data - A function that frees the data structure used
 * @datas: data to be used
 */
void free_data(data_s *datas)
{
	unsigned int a;

	for (a = 0; datas->_environ[a]; a++)
	{
		free(datas->_environ[a]);
	}

	free(datas->_environ);
	free(datas->pid);
}

/**
 * set_data - A function that initialize the data structure used
 * @datas: The data to be used
 * @argv: The argument vector containing the list of arguments
 */
void set_data(data_s *datas, char **argv)
{
	unsigned int a;

	datas->argv = argv;
	datas->input = NULL;
	datas->args = NULL;
	datas->status = 0;
	datas->counter = 1;

	for (a = 0; environ[a]; a++)
		;

	datas->_environ = malloc(sizeof(char *) * (a + 1));

	for (a = 0; environ[a]; a++)
	{
		datas->_environ[a] = _strdup(environ[a]);
	}

	datas->_environ[a] = NULL;
	datas->pid = aux_itoa(getpid());
}

/**
 * main - The function's entry point
 * @argc: The argument count(number of arguments)
 * @argv: The argument vector(contains the list of arguments)
 * Return: (0) if successful
 */
int main(int argc, char **argv)
{
	data_s datas;
	(void) argc;

	signal(SIGINT, get_sigint);
	set_data(&datas, argv);
	shell_loop(&datas);
	free_data(&datas);
	if (datas.status < 0)
		return (255);
	return (datas.status);
}
