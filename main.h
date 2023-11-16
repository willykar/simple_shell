#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFFSIZE 1024
#define TOK_BUFFSIZE 128
#define TOK_DELIM " \t\r\n\a"

void handle_command(char *buffer);
int find_executable_in_path(const char *command,
		char *full_path, size_t max_length);

int bfree(void **);

extern char **environ;

/**
 * struct data - struct that contain data
 * @argv: argument vector containing the list of arguments
 * @input: command line
 * @args: arguments
 * @status: status of shell
 * @counter: the line counter
 * @_environ: the environment variable
 * @pid: process ID of the current running shell
 */
typedef struct data
{
	char **argv;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_s;

/**
 * struct sep_list_s - linked list
 * @separator: separators used ; | &
 * @next: the next node in the list
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - a single linked list
 * @line: line
 * @next: the next node
 * Description: stores command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - a single linked list
 * @length_var: the length of the variable
 * @val: value of the variable
 * @length_val: length of value
 * @next: the next node
 */
typedef struct r_var_list
{
	int length_var;
	char *val;
	int length_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command arguments
 * @name: Name of the command builtin
 * @f: pointer function
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_s *datas);
} builtin_t;

sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line(line_list **head);

r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

char *_strdup(const char *s);
int _strlength(const char *s);
int comp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

void rev_string(char *s);

int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data_s *datas, char *input, int i, int bool);
int check_syntax_error(data_s *datas, char *input);

char *without_comment(char *in);
void shell_loop(data_s *datas);

char *read_line(int *i_eof);

char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_s *datas);
int split_commands(data_s *datas, char *input);
char **split_line(char *input);

void check_env(r_var **h, char *in, data_s *data);
int check_vars(r_var **h, char *in, char *st, data_s *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_s *datas);

void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

int execute_line(data_s *datas);

int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environment);
int is_executable(data_s *datas);
int check_error_cmd(char *dir, data_s *datas);
int cmd_execute(data_s *datas);

char *_getenv(const char *name, char **_environment);
int _env(data_s *datas);

char *copy_info(char *name, char *value);
void set_environment(char *name, char *value, data_s *datas);
int _setenv(data_s *datas);
int _unsetenv(data_s *datas);

void cd_dt(data_s *datas);
void cd_change(data_s *datas);
void cd_dir_previous(data_s *datas);
void cd_to_home(data_s *datas);

int cd_shell(data_s *datas);

int (*get_builtin(char *cmd))(data_s *datas);

int exit_shell(data_s *datas);

int get_length(int n);
char *aux_itoa(int n);
int _atoi(char *s);

char *strcat_cd(data_s *, char *, char *, char *);
char *error_get_cd(data_s *datas);
char *error_not_found(data_s *datas);
char *error_exit_shell(data_s *datas);

char *error_get_alias(char **args);
char *error_env(data_s *datas);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_p(data_s *datas);

int get_error(data_s *datas, int eval);

void get_sigint(int signal);

void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

int get_help(data_s *datas);

#endif
