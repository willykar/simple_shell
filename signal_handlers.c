#include "main.h"

/**
 * get_sigint - A function that handles the
 * crtl + c call in the prompt
 * @signal: Signal handler
 */
void get_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
