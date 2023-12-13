#ifndef SIMPLE_SHELL_HEADER
#define SIMPLE_SHELL_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>

/*buffer reading sizes */
#define MAX_BUFFER_READ_SIZE 1024
#define MAX_BUFFER_WRITE_SIZE 1024
#define BUFFER_FLUSH_STATUS -1

/*chaing utilities */
#define CHAIN_NORM 0
#define CHAIN_OR 1
#define CHAIN_AND 2
#define CHAIN_CMD 3

/*used for numerical */
#define LOWERCASE_CONVERSION_FLAG 1
#define UNSIGNED_INT_CONVERSION_FLAG 2

/*used for stroke line utility */
#define FIND_STROKE_LINE 0
#define FIND_STROKE_TOK 0
#define HISTORY_FILE ".simple_shell_history"
#define MAX_HISTORY_COUNT 4096

extern char **environ;

/**
 *struct stringlst - a linked list of strings
 *@num: the length of linked list
 *@str: the string data
 *@next: pointer to the next node
 */
typedef struct stringlst
{
	int num;
	char *str;
	struct stringlst *next;
}

list_type;

/**
 *struct info_struct - allows custom info to be passed to the cmd
 *@arg: the arguments passed
 *@argv: the argument vector
 *@path: the path to the current command as a string
 *@argc: the number of arguments passed
 *@line_number: the number of errors
 *@error_number: the error status
 *@linenumber_tag: counts the number of inputs
 *@file_name: the name of the program file
 *@env: local environment
 *@environ: modified copy of the environment variable
 *@history: pointer to the history node
 *@alias: pointer to the alias node
 *@environment_change: indicator for environment change
 *@status: the exit status of last command
 *@cmd_buffer: pointer to cmd buffer address
 *@cmd_buffer_type: type of cmd
 *@readfiledata: the file to read input data from
 *@history_count: the history line number count
 */
typedef struct info_struct
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_number;
	int error_number;
	int linenumber_tag;
	char *file_name;
	list_type *env;
	list_type *history;
	list_type *alias;
	char **environ;
	int environment_change;
	int status;

	char **cmd_buffer;
	int cmd_buffer_type;
	int readfiledata;
	int history_count;
}

info_type;

#define INIT_INFO {\
	NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0\
}

/**
 *struct builtin - reference to builtin functions
 *@type: flag for builtin
 *@func: the function to call for builtin
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_type *);
}

table_builtin;

int hash_function(info_type *, char **);
int retrieve_builtin(info_type *);
void retrieve_cmd(info_type *);
void command_fork(info_type *);

int verify_cmd(info_type *, char *);
char *replicate_chars(char *, int, int);
char *compute_path(info_type *, char *, char *);

int check_loop(char **);

void print_input(char *);
int print_standard_error(char);
int _print_file_char(char c, int fd);
int _print_standard_string(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **str_tokenize(char *, char *);
char **str_token(char *, char);

char *_memset(char *, char, unsigned int);
void free_strings(char **);
void *_realloc_block(void *, unsigned int, unsigned int);

int _free_pointers(void **);

int check_interactive(info_type *);
int check_delimiter(char, char *);
int check_alpha(int);
int _integer_convert(char *);

int _string_to_int(char *);
void error_printer(info_type *, char *);
int _print_decimal(int, int);
char *number_converter(long int, int, int);
void clear_comment(char *);

int _exit_shell(info_type *);
int _mycd(info_type *);
int _change_directory(info_type *);

int _tranverse_history(info_type *);
int _custom_alias(info_type *);

ssize_t _extract_inputs(info_type *);
int _get_line(info_type *, char **, size_t *);
void block_ctrc(int);

void initialize_info_type(info_type *);
void set_info_type(info_type *, char **);
void free_info_type(info_type *, int);

char *_get_env(info_type *, const char *);
int print_my_env(info_type *);
int initialize_my_env(info_type *);
int _clear_environment(info_type *);
int populate_environment(info_type *);

char **get_environment_variables(info_type *);
int _remove_set_env(info_type *, char *);
int _add_new_env(info_type *, char *, char *);

char *find_history_file(info_type *info);
int add_to_history_file(info_type *info);
int read_history_file(info_type *info);
int create_history_list(info_type *info, char *buf, int linecount);
int reorder_history(info_type *info);

list_type *add_node(list_type **, const char *, int);
list_type *append_node(list_type **, const char *, int);
size_t print_string_elements(const list_type *);
int remove_node_at_index(list_type **, unsigned int);
void clear_list(list_type **);

size_t calculate_list_length(const list_type *);
char **print_list_string(list_type *);
size_t print_list(const list_type *);
list_type *node_start_prefix(list_type *, char *, char);
ssize_t find_node_at_index(list_type *, list_type *);

int check_chain_delimeter(info_type *, char *, size_t *);
void check_chain(info_type *, char *, size_t *, size_t, size_t);
int substitute_alias(info_type *);
int substitute_vars(info_type *);
int substitute_string(char **, char *);
#endif
