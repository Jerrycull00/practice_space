#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define _READ_BUF_SIZE_ 1024
#define _WRITE_BUF_SIZE_ 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct _passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct _passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define _INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct _builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct _builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int _hsh_(info_t *, char **);
int _find_builtin_(info_t *);
void _find_cmd_(info_t *);
void _fork_cmd_(info_t *);

/* toem_parser.c */
int _is_cmd_(info_t *, char *);
char *_dup_chars_(char *, int, int);
char *_find_path_(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void __eputs_(char *);
int __eputchar_(char);
int __putfd_(char c, int fd);
int __putsfd_(char *str, int fd);

/* toem_string.c */
int _strlen_(char *);
int _strcmp_(char *, char *);
char *starts_with_(const char *, const char *);
char *_strcat_(char *, char *);

/* toem_string1.c */
char *_strcpy_(char *, char *);
char *_strdup_(const char *);
void _puts_(char *);
int _putchar_(char);

/* toem_exits.c */
char *_strncpy_(char *, char *, int);
char *_strncat_(char *, char *, int);
char *_strchr_(char *, char);

/* toem_tokenizer.c */
char **strtow_(char *, char *);
char **strtow2_(char *, char);

/* toem_realloc.c */
char *_memset_(char *, char, unsigned int);
void ffree_(char **);
void *_realloc_(void *, unsigned int, unsigned int);

/* toem_memory.c */
int _bfree_(void **);

/* toem_atoi.c */
int _interactive_(info_t *);
int _is_delim_(char, char *);
int _isalpha_(int);
int _atoi_(char *);

/* toem_errors1.c */
int _erratoi_(char *);
void print_error_(info_t *, char *);
int print_d_(int, int);
char *convert_number_(long int, int, int);
void remove_comments_(char *);

/* toem_builtin.c */
int _exit_(info_t *);
int _cd_(info_t *);
int _help_(info_t *);

/* toem_builtin1.c */
int _history_(info_t *);
int _alias_(info_t *);
int _unset_alias_(info_t *info, char *str);
int _set_alias_(info_t *info, char *str);
int _print_alias_(list_t *node);

/*toem_getline.c */
ssize_t _get_input_(info_t *);
int _getline_(info_t *, char **, size_t *);
void _sigint_Handler_(int);
ssize_t _input_buf_(info_t *info, char **buf, size_t *len);
ssize_t _read_buf_(info_t *info, char *buf, size_t *i);

/* toem_getinfo.c */
void _clear_info_(info_t *);
void _set_info_(info_t *, char **);
void _free_info_(info_t *, int);

/* toem_environ.c */
char *_getenv_(info_t *, const char *);
int _myenv_(info_t *);
int _mysetenv_(info_t *);
int _myunsetenv_(info_t *);
int populate_env_list_(info_t *);

/* toem_getenv.c */
char **get_environ_(info_t *);
int _unsetenv_(info_t *, char *);
int _setenv_(info_t *, char *, char *);

/* toem_history.c */
char *_get_history_file_(info_t *info);
int _write_history_(info_t *info);
int _read_history_(info_t *info);
int _build_history_list_(info_t *info, char *buf, int linecount);
int _renumber_history_(info_t *info);

/* toem_lists.c */
list_t *_add_node_(list_t **, const char *, int);
list_t *_add_node_end_(list_t **, const char *, int);
size_t _print_list_str_(const list_t *);
int _delete_node_at_index_(list_t **, unsigned int);
void _free_list_(list_t **);

/* toem_lists1.c */
size_t _list_len_(const list_t *);
char **_list_to_strings_(list_t *);
size_t _print_list_(const list_t *);
list_t *_node_starts_with_(list_t *, char *, char);
ssize_t _get_node_index_(list_t *, list_t *);

/* toem_vars.c */
int is_chain_(info_t *, char *, size_t *);
void check_chain_(info_t *, char *, size_t *, size_t, size_t);
int replace_alias_(info_t *);
int replace_vars_(info_t *);
int replace_string_(char **, char *);

#endif
