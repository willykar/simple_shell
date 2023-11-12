#include "main.h"

/**
 * aux_help - A function that will provide helpful information for the built-in help
 */
void aux_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlength(help));
	help = "\tDisplay information about built-in commands.\n ";
	write(STDOUT_FILENO, help, _strlength(help));
	help = "Displays a brief summary of the built-in commands.\n";
	write(STDOUT_FILENO, help, _strlength(help));
}
/**
 * aux_help_alias - A function that provides help info for the alias
 */
void aux_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlength(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlength(help));
}
/**
 * aux_help_cd - Help information for the built-in alias
 */
void aux_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlength(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlength(help));
}
