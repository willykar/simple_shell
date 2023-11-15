#include "main.h"

/**
 * aux_help_env - A function that provides helpful information for the builtin env
 */ 
void aux_help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _strlength(help));
	help = "Print the enviroment of the current shell.\n";
	write(STDOUT_FILENO, help, _strlength(help));

}
/**
 * aux_help_setenv - A function that provides helpful information for the setenv
 */
void aux_help_setenv(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, _strlength(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _strlength(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _strlength(help));
}
/**
 * aux_help_unsetenv - A function that provides helpful information
 */
void aux_help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, _strlength(help));
	help = "Remove an item completely from the environment\n";
	write(STDOUT_FILENO, help, _strlength(help));
}


/**
 * aux_help_general - help information
 */
void aux_help_general(void)
{
	char *help = "^-^ bash, version 1.00-release\n";

	write(STDOUT_FILENO, help, _strlength(help));
	help = "These commands are defined internally.Type 'help' to see the full list";
	write(STDOUT_FILENO, help, _strlength(help));
	help = "Type 'help' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, _strlength(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, _strlength(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, _strlength(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, _strlength(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, _strlength(help));
}
/**
 * aux_help_exit - A function that provides help information for exit
 */
void aux_help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, _strlength(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, _strlength(help));
	help = "status is that of the last command executed\n";
	write(STDOUT_FILENO, help, _strlength(help));
}
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
