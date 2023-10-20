#ifndef MAIN_H
#define MAIN_H
#define MAX_CMD_LEN 1024
#define BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <stdbool.h>


extern char **environ;
int _putchar(char c);

/**
 * struct commands - Structure to represent a command
 * @env: The environment variables.
 * @new_env: An array to store new environment variables.
 * @new_env_count: The number of new environment variables.
 * @argv: An array of command arguments.
 * @path_found: Flag indicating whether the command path is found.
 * @setenv: Flag indicating whether a setenv command is present.
 * @eof: Checks if EOF encountered
 * @arg_count: The number of command arguments.
 */
typedef struct commands
{
	char **env;
	char *new_env[MAX_CMD_LEN];
	int new_env_count;
	char **argv;
	bool path_found;
	bool eof;
	bool setenv;
	int arg_count;
} cmd_t;

/* PrintF Function */
void handle_char(va_list args, int *count);
void handle_string(va_list args, int *count);
void handle_percent(int *count);
void handle_int(va_list args, int *count);
void print_negative(int *n);
void print_digit(int n);
void print_int(int n);
int _printf(const char *format, ...);

/* Function prototypes */
char *my_strdup(const char *str);
int my_strlen(const char *s);
void my_strcpy(char *dest, const char *src);
int my_strcmp(const char *s1, const char *s2);
int my_atoi(const char *str);
char *my_strcat(char *dest, const char *src);
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);
char *my_realloc(char *line, size_t *buffer_size);

/* Function prototypes */
void print_env(void);
char *command_exists(char *cmd);
void execute_command(char *cmd, char **argv);
bool specials(cmd_t *cmds);
void copy_environ(cmd_t *cmds);
int my_setenv(cmd_t *cmds);
int my_unsetenv(cmd_t *cmds);
int my_strncmp(const char *s1, const char *s2, int n);

/* Shell */
char *read_line();
void tokenize_line(char *line, cmd_t *cmds);
void process_commands(cmd_t *cmds);
void free_cmdt(cmd_t *cmds);
void init_cmdt(cmd_t *cmds);
void free_args(cmd_t *cmd);
char *my_getenv(const char *name);
char *rmv_space(char *cmd);
char *get_cmd(char *str);
int count_slash(char *str);
char *my_strchr(const char *str, int character);
char *my_strtok(char *str, const char *delim);
/*char *my_strtok(char *str, const char *delim)*/

#endif
